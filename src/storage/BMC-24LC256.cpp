/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.

  This class is just a copy of the extEEPROM by JChristensen, all credits go to the developer
  The class is renamed here so it can be included with BMC
*//*-----------------------------------------------------------------------------*
 * BMC24LC256.cpp - Arduino library to support external I2C EEPROMs.            *
 *                                                                             *
 * This library will work with most I2C serial EEPROM chips between 2k bits    *
 * and 2048k bits (2M bits) in size. Multiple EEPROMs on the bus are supported *
 * as a single address space. I/O across block, layer and device boundaries     *
 * is supported. Certain assumptions are made regarding the EEPROM             *
 * device addressing. These assumptions should be true for most EEPROMs        *
 * but there are exceptions, so read the datasheet and know your hardware.     *
 *                                                                             *
 * The library should also work for EEPROMs smaller than 2k bits, assuming     *
 * that there is only one EEPROM on the bus and also that the user is careful  *
 * to not exceed the maximum address for the EEPROM.                           *
 *                                                                             *
 * Library tested with:                                                        *
 *   Microchip 24AA02E48 (2k bit)                                              *
 *   24xx32 (32k bit, thanks to Richard M)                                     *
 *   Microchip 24LC256 (256k bit)                                              *
 *   Microchip 24FC1026 (1M bit, thanks to Gabriele B on the Arduino forum)    *
 *   ST Micro M24M02 (2M bit)                                                  *
 *                                                                             *
 * Library will NOT work with Microchip 24xx1025 as its control uint8_t does not  *
 * conform to the following assumptions.                                       *
 *                                                                             *
 * Device addressing assumptions:                                              *
 * 1. The I2C address sequence consists of a control uint8_t followed by one      *
 *    address uint8_t (for EEPROMs <= 16k bits) or two address bytes (for         *
 *    EEPROMs > 16k bits).                                                     *
 * 2. The three least-significant bits in the control uint8_t (excluding the R/W  *
 *    bit) comprise the three most-significant bits for the entire address     *
 *    space, i.e. all chips on the bus. As such, these may be chip-select      *
 *    bits or block-select bits (for individual chips that have an internal    *
 *    block organization), or a combination of both (in which case the         *
 *    block-select bits must be of lesser significance than the chip-select    *
 *    bits).                                                                   *
 * 3. Regardless of the number of bits needed to address the entire address    *
 *    space, the three most-significant bits always go in the control byte.    *
 *    Depending on EEPROM device size, this may result in one or more of the   *
 *    most significant bits in the I2C address bytes being unused (or "don't   *
 *    care").                                                                  *
 * 4. An EEPROM contains an integral number of layers.                          *
 *                                                                             *
 * To use the BMC24LC256 library, the Arduino Wire library must also            *
 * be included.                                                                *
 *                                                                             *
 * Jack Christensen 23Mar2013 v1                                               *
 * 29Mar2013 v2 - Updated to span layer boundaries (and therefore also          *
 * device boundaries, assuming an integral number of layers per device)         *
 * 08Jul2014 v3 - Generalized for 2kb - 2Mb EEPROMs.                           *
 *                                                                             *
 * External EEPROM Library by Jack Christensen is licensed under CC BY-SA 4.0, *
 * http://creativecommons.org/licenses/by-sa/4.0/                              *
 *-----------------------------------------------------------------------------*/

#if defined(BMC_USE_24LC256)
#include "storage/BMC-24LC256.h"

#if defined(BMC_FOR_ESP32)
  #define BUFFER_LENGTH I2C_BUFFER_LENGTH
#else
  #if defined(I2C_T3_H)
    #define BUFFER_LENGTH I2C_TX_BUFFER_LENGTH
  #endif
#endif


// Constructor.
// - deviceCapacity is the capacity of a single EEPROM device in
//   kilobits (kb) and should be one of the values defined in the
//   BMC_eeprom_size_t enumeration in the BMC24LC256.h file. (Most
//   EEPROM manufacturers use kbits in their part numbers.)
// - nDevice is the number of EEPROM devices on the I2C bus (all must
//   be identical).
// - pageSize is the EEPROM's layer size in bytes.
// - eepromAddr is the EEPROM's I2C address and defaults to 0x50 which is common.
BMC24LC256::BMC24LC256(BMC_eeprom_size_t deviceCapacity, uint8_t nDevice, unsigned int pageSize, uint8_t eepromAddr)
{
    _dvcCapacity = deviceCapacity;
    _nDevice = nDevice;
    _pageSize = pageSize;
    _eepromAddr = eepromAddr;
    _totalCapacity = _nDevice * _dvcCapacity * 1024UL / 8;
    _nAddrBytes = deviceCapacity > kbits_16 ? 2 : 1;       //two address bytes needed for eeproms > 16kbits

    //determine the bitshift needed to isolate the chip select bits from the address to put into the control byte
    uint16_t kb = _dvcCapacity;
    if ( kb <= kbits_16 ) _csShift = 8;
    else if ( kb >= kbits_512 ) _csShift = 16;
    else {
        kb >>= 6;
        _csShift = 12;
        while ( kb >= 1 ) {
            ++_csShift;
            kb >>= 1;
        }
    }
}

//initialize the I2C bus and do a dummy write (no data sent)
//to the device so that the caller can determine whether it is responding.
//when using a 400kHz bus speed and there are multiple I2C devices on the
//bus (other than EEPROM), call BMC24LC256::begin() after any initialization
//calls for the other devices to ensure the intended I2C clock speed is set.
uint8_t BMC24LC256::begin(twiClockFreq_t twiFreq){
  BMC_PRINTLN("   - BMC24LC256::begin");
  Wire.begin();
  Wire.setClock(twiFreq); 	// TRL 21Oct2018, compatibility with other processors
  Wire.beginTransmission(_eepromAddr);
  if (_nAddrBytes == 2) Wire.write(0);      //high addr byte
  Wire.write(0);                            //low addr byte
  return Wire.endTransmission();
}

//Write bytes to external EEPROM.
//If the I/O would extend past the top of the EEPROM address space,
//a status of EEPROM_ADDR_ERR is returned. For I2C errors, the status
//from the Arduino Wire library is passed back through to the caller.
uint8_t BMC24LC256::write(unsigned long addr, uint8_t *values, unsigned int nBytes){
    uint8_t ctrlByte;       //control uint8_t (I2C device address & chip/block select bits)
    uint8_t txStatus = 0;   //transmit status
    uint16_t nWrite;        //number of bytes to write
    uint16_t nPage;         //number of bytes remaining on current layer, starting at addr

    if (addr + nBytes > _totalCapacity) {   //will this write go past the top of the EEPROM?
        return EEPROM_ADDR_ERR;             //yes, tell the caller
    }

    while (nBytes > 0) {
        nPage = _pageSize - ( addr & (_pageSize - 1) );
        //find min(nBytes, nPage, BUFFER_LENGTH) -- BUFFER_LENGTH is defined in the Wire library.
        nWrite = nBytes < nPage ? nBytes : nPage;
        nWrite = BUFFER_LENGTH - _nAddrBytes < nWrite ? BUFFER_LENGTH - _nAddrBytes : nWrite;
        ctrlByte = _eepromAddr | (uint8_t) (addr >> _csShift);
        Wire.beginTransmission(ctrlByte);
        if (_nAddrBytes == 2) Wire.write( (uint8_t) (addr >> 8) );   //high addr byte
        Wire.write( (uint8_t) addr );                                //low addr byte
        Wire.write(values, nWrite);
        txStatus = Wire.endTransmission();
        if (txStatus != 0) return txStatus;

        //wait up to 50ms for the write to complete
        for (uint8_t i=100; i; --i) {
            delayMicroseconds(500);                     //no point in waiting too fast
            Wire.beginTransmission(ctrlByte);
            if (_nAddrBytes == 2) Wire.write(0);        //high addr byte
            Wire.write(0);                              //low addr byte
            txStatus = Wire.endTransmission();
            if (txStatus == 0) break;
        }
        if (txStatus != 0) return txStatus;

        addr += nWrite;         //increment the EEPROM address
        values += nWrite;       //increment the input data pointer
        nBytes -= nWrite;       //decrement the number of bytes left to write
    }
    return txStatus;
}

//Read bytes from external EEPROM.
//If the I/O would extend past the top of the EEPROM address space,
//a status of EEPROM_ADDR_ERR is returned. For I2C errors, the status
//from the Arduino Wire library is passed back through to the caller.
uint8_t BMC24LC256::read(unsigned long addr, uint8_t *values, unsigned int nBytes)
{
    uint8_t ctrlByte;
    uint8_t rxStatus;
    unsigned int nRead;             //number of bytes to read
    unsigned int nPage;             //number of bytes remaining on current layer, starting at addr

    if (addr + nBytes > _totalCapacity) {   //will this read take us past the top of the EEPROM?
        return EEPROM_ADDR_ERR;             //yes, tell the caller
    }

    while (nBytes > 0) {
        nPage = _pageSize - ( addr & (_pageSize - 1) );
        nRead = nBytes < nPage ? nBytes : nPage;
        nRead = BUFFER_LENGTH < nRead ? BUFFER_LENGTH : nRead;
        ctrlByte = _eepromAddr | (uint8_t) (addr >> _csShift);
        Wire.beginTransmission(ctrlByte);
        if (_nAddrBytes == 2) Wire.write( (uint8_t) (addr >> 8) );   //high addr byte
        Wire.write( (uint8_t) addr );                                //low addr byte
        rxStatus = Wire.endTransmission();
        if (rxStatus != 0) return rxStatus;        //read error

        Wire.requestFrom(ctrlByte, nRead);
        for (uint8_t i=0; i<nRead; i++) values[i] = Wire.read();

        addr += nRead;          //increment the EEPROM address
        values += nRead;        //increment the input data pointer
        nBytes -= nRead;        //decrement the number of bytes left to write
    }
    return 0;
}

//Write a single uint8_t to external EEPROM.
//If the I/O would extend past the top of the EEPROM address space,
//a status of EEPROM_ADDR_ERR is returned. For I2C errors, the status
//from the Arduino Wire library is passed back through to the caller.
uint8_t BMC24LC256::write(unsigned long addr, uint8_t value)
{
    return write(addr, &value, 1);
}

//Read a single uint8_t from external EEPROM.
//If the I/O would extend past the top of the EEPROM address space,
//a status of EEPROM_ADDR_ERR is returned. For I2C errors, the status
//from the Arduino Wire library is passed back through to the caller.
//To distinguish error values from valid data, error values are returned as negative numbers.
int BMC24LC256::read(unsigned long addr)
{
    uint8_t data;
    int ret;

    ret = read(addr, &data, 1);
    return ret == 0 ? data : -ret;
}
#endif
