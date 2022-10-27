/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  This class is just a copy of the extEEPROM by JChristensen, all credits go to the developer
  The class is renamed here so it can be included with BMC
*/
/*-----------------------------------------------------------------------------*
 * extEEPROM.h - Arduino library to support external I2C EEPROMs.              *
 *                                                                             *
 * This library will work with most I2C serial EEPROM chips between 2k bits    *
 * and 2048k bits (2M bits) in size. Multiple EEPROMs on the bus are supported *
 * as a single address space. I/O across block, page and device boundaries     *
 * is supported. Certain assumptions are made regarding the EEPROM             *
 * device addressing. These assumptions should be true for most EEPROMs        *
 * but there are exceptions, so read the datasheet and know your hardware.     *
 *                                                                             *
 * The library should also work for EEPROMs smaller than 2k bits, assuming     *
 * that there is only one EEPROM on the bus and also that the user is careful  *
 * to not exceed the maximum address for the EEPROM.                           *
 *                                                                             *
 * Library tested with:                                                        *
 *   Microchip 24LC256 (256k bit)                                              *
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
 * 4. An EEPROM contains an integral number of pages.                          *
 *                                                                             *
 * To use the BMC24LC256 library, the Arduino Wire library must also            *
 * be included.                                                                *
 *                                                                             *
 * Jack Christensen 23Mar2013 v1                                               *
 * 29Mar2013 v2 - Updated to span page boundaries (and therefore also          *
 * device boundaries, assuming an integral number of pages per device)         *
 * 08Jul2014 v3 - Generalized for 2kb - 2Mb EEPROMs.                           *
 *                                                                             *
 * External EEPROM Library by Jack Christensen is licensed under CC BY-SA 4.0, *
 * http://creativecommons.org/licenses/by-sa/4.0/                              *
 *-----------------------------------------------------------------------------*/

#ifndef BMC_24LC256_H
#define BMC_24LC256_H

#if defined(BMC_USE_24LC256)

#include "utility/BMC-Def.h"

// if using the Audio library we have to use Wire.h not i2c_t3.h
#include <Wire.h>

//EEPROM size in kilobits. EEPROM part numbers are usually designated in k-bits.
enum BMC_eeprom_size_t {
    kbits_2 = 2,
    kbits_4 = 4,
    kbits_8 = 8,
    kbits_16 = 16,
    kbits_32 = 32,
    kbits_64 = 64,
    kbits_128 = 128,
    kbits_256 = 256,
    kbits_512 = 512,
    kbits_1024 = 1024,
    kbits_2048 = 2048
};

//EEPROM addressing error, returned by write() or read() if upper address bound is exceeded
const uint8_t EEPROM_ADDR_ERR = 9;

class BMC24LC256
{
    public:
        //I2C clock frequencies
        enum twiClockFreq_t { twiClock100kHz = 100000, twiClock400kHz = 400000 };
        BMC24LC256(BMC_eeprom_size_t deviceCapacity, uint8_t nDevice, unsigned int pageSize, uint8_t eepromAddr = 0x50);
        uint8_t begin(twiClockFreq_t twiFreq = twiClock100kHz);
        uint8_t write(unsigned long addr, uint8_t *values, unsigned int nBytes);
        uint8_t write(unsigned long addr, uint8_t value);
        uint8_t read(unsigned long addr, uint8_t *values, unsigned int nBytes);
        int read(unsigned long addr);
        uint8_t update(unsigned long addr, uint8_t value){
          if(read(addr) != value){
            write(addr, &value, 1);
            return 1;
          }
          return 0;
          //return read(addr) == value ? 0 : write(addr, &value, 1);
        }
        template <typename T> uint8_t put(uint16_t start, const T& value){
          const uint8_t * p = (const uint8_t*) &value;
          unsigned long i = start;
          unsigned long n = sizeof(value)+start;
          unsigned long updatedBytes = 0;
#ifdef BMC_DEBUG
          BMC_PRINTNS("24LC256 UPDATE");
          writeTime = 0;
#endif
          for(i=start;i<n;i++){
            updatedBytes += update(i,*p++);
#ifdef BMC_DEBUG
            if(writeTime>=250){
              BMC_PRINTNS(".");
              writeTime = 0;
            }
#endif
          }
#ifdef BMC_DEBUG
          BMC_PRINTLN(". Updated", updatedBytes, "Bytes");
#endif
          return updatedBytes;
        }
        template <typename T> uint8_t get(uint16_t start, const T& value){
          uint8_t * p = (uint8_t*) &value;
          unsigned long i = start;
          unsigned long n = sizeof(value)+start;
#ifdef BMC_DEBUG
          BMC_PRINTNS("24LC256 READING");
          writeTime = 0;
#endif
          for (i=start;i<n;i++){
            *p++ = (uint8_t) read(i);
#ifdef BMC_DEBUG
            if(writeTime>=250){
              BMC_PRINTNS(".");
              writeTime = 0;
            }
#endif
          }
#ifdef BMC_DEBUG
          BMC_PRINTLN(".");
#endif
          return i;
        }
        void clear(){
#ifdef BMC_DEBUG
          uint32_t msStart = millis();
#endif
          BMC_PRINTLN("");
          BMC_PRINTLN("******************************");
          BMC_PRINTLN("******************************");
          BMC_PRINTLN("24LC256 Erase");
          BMC_PRINTLN("This may take a few seconds");
          uint8_t chunk = 64;
          uint8_t data[chunk];
          memset(data,0,chunk);
          for(uint32_t a = 0; a <= _totalCapacity; a += chunk){
            write(a, data, chunk);
#ifdef BMC_DEBUG
            if(writeTime>=250){
              BMC_PRINTNS(".");
              writeTime = 0;
            }
#endif
          }
          BMC_PRINTLN("");
          BMC_PRINTLN("24LC256 Erase took ",(float) (millis() - msStart)/1000," seconds");
          BMC_PRINTLN("******************************");
          BMC_PRINTLN("******************************");
          BMC_PRINTLN("");
        }
        uint16_t length(){
          /*
          #if BMC_TEENSY_RAM_SIZE >= 262144
            #if defined(BMC_STORAGE_PARTITION_SIZE_32K)
              // 32K
              return 32000;
            #else
              // 16K
              return 16000;
            #endif
          #else
            // 8K
            return 8000;
          #endif
          */
          return _totalCapacity;
        }

    private:
        uint8_t _eepromAddr;            //eeprom i2c address
        uint16_t _dvcCapacity;          //capacity of one EEPROM device, in kbits
        uint8_t _nDevice;               //number of devices on the bus
        uint16_t _pageSize;             //page size in bytes
        uint8_t _csShift;               //number of bits to shift address for chip select bits in control byte
        uint16_t _nAddrBytes;           //number of address bytes (1 or 2)
        unsigned long _totalCapacity;   //capacity of all EEPROM devices on the bus, in bytes
        #ifdef BMC_DEBUG
        elapsedMillis writeTime = 0;
        #endif
};

#endif

#endif
