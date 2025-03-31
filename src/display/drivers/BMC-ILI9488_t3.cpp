// https://github.com/PaulStoffregen/BMC_ILI9488_t3
// http://forum.pjrc.com/threads/26305-Highly-optimized-ILI9488-(320x240-TFT-color-display)-library

/***************************************************
  This is our library for the Adafruit ILI9488 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

// <SoftEgg>

//Additional graphics routines by Tim Trzepacz, SoftEgg LLC added December 2015
//(And then accidentally deleted and rewritten March 2016. Oops!)
//Gradient support
//----------------
//		fillRectVGradient	- fills area with vertical gradient
//		fillRectHGradient	- fills area with horizontal gradient
//		fillScreenVGradient - fills screen with vertical gradient
// 	fillScreenHGradient - fills screen with horizontal gradient

//Additional Color Support
//------------------------
//		color565toRGB		- converts 565 format 16 bit color to RGB
//		color565toRGB14		- converts 16 bit 565 format color to 14 bit RGB (2 bits clear for math and sign)
//		RGB14tocolor565		- converts 14 bit RGB back to 16 bit 565 format color

//Low Memory Bitmap Support
//-------------------------
// 		writeRect8BPP - 	write 8 bit per pixel paletted bitmap
// 		writeRect4BPP - 	write 4 bit per pixel paletted bitmap
// 		writeRect2BPP - 	write 2 bit per pixel paletted bitmap
// 		writeRect1BPP - 	write 1 bit per pixel paletted bitmap

//TODO: transparent bitmap writing routines for sprites

//String Pixel Length support 
//---------------------------
//		strPixelLen			- gets pixel length of given ASCII string

// <\SoftEgg>

#include "utility/BMC-Def.h"

#if defined(BMC_FOR_TEENSY) && BMC_MAX_ILI9341_BLOCKS > 0

#include "display/drivers/BMC-ILI9488_t3.h"
#include <SPI.h>

// Teensy 3.1 can only generate 30 MHz SPI when running at 120 MHz (overclock)
// At all other speeds, spi_port->beginTransaction() will use the fastest available clock

// #define WIDTH  ILI9488_TFTWIDTH
// #define HEIGHT ILI9488_TFTHEIGHT

#ifdef ENABLE_ILI9488_FRAMEBUFFER
#define CBALLOC (ILI9488_TFTHEIGHT * ILI9488_TFTWIDTH * sizeof(RAFB))
#define	COUNT_WORDS_WRITE  ((ILI9488_TFTHEIGHT*ILI9488_TFTWIDTH)/SCREEN_DMA_NUM_SETTINGS) // Note I know the divide will give whole number
#endif

//#define DEBUG_ASYNC_UPDATE
#if defined(__MK66FX1M0__) 
DMASetting 	BMC_ILI9488_t3::_dmasettings[3];
DMAChannel 	BMC_ILI9488_t3::_dmatx;
#elif defined(__MK64FX512__)
DMAChannel  BMC_ILI9488_t3::_dmatx;
//DMAChannel  BMC_ILI9488_t3::_dmarx;
//uint16_t 	BMC_ILI9488_t3::_dma_count_remaining;
//uint16_t	BMC_ILI9488_t3::_dma_write_size_words;
//volatile short _dma_dummy_rx;
#elif defined(__IMXRT1052__) || defined(__IMXRT1062__)  // Teensy 4.x
//#define DEBUG_ASYNC_LEDS	// Enable to use digitalWrites to Debug
#ifdef DEBUG_ASYNC_LEDS
#define DEBUG_PIN_1 2
#define DEBUG_PIN_2 3
#define DEBUG_PIN_3 4
#endif


//DMASetting 	BMC_ILI9488_t3::_dmasettings[2];
//DMAChannel 	BMC_ILI9488_t3::_dmatx;
#else
#endif	

#ifdef ENABLE_ILI9488_FRAMEBUFFER
#if defined(__IMXRT1052__) || defined(__IMXRT1062__)  // Teensy 4.x
BMC_ILI9488_t3 *BMC_ILI9488_t3::_dmaActiveDisplay[3] = {0, 0, 0};
#else
BMC_ILI9488_t3 *BMC_ILI9488_t3::_dmaActiveDisplay = 0;

#endif
volatile uint32_t 	BMC_ILI9488_t3::_dma_pixel_index = 0;

#endif

// Constructor when using hardware SPI.  Faster, but must use SPI pins
// specific to each board type (e.g. 11,13 for Uno, 51,52 for Mega, etc.)
BMC_ILI9488_t3::BMC_ILI9488_t3(uint8_t cs, uint8_t dc, uint8_t rst, uint8_t mosi, uint8_t sclk, uint8_t miso)
{
	spi_port = nullptr;

	_cs   = cs;
	_dc   = dc;
	_rst  = rst;
	_mosi = mosi;
	_sclk = sclk;
	_miso = miso;
	_width    = ILI9488_TFTWIDTH;
	_height   = ILI9488_TFTHEIGHT;
	rotation  = 0;
	cursor_y  = cursor_x    = 0;
	cursor_y  = cursor_x    = 0;
	textsize  = 1;
	textcolor = textbgcolor = 0xFFFF;
	wrap      = true;
	font      = NULL;
	// Added to see how much impact actually using non hardware CS pin might be
    _cspinmask = 0;
    _csport = NULL;
	
#ifdef ENABLE_ILI9488_FRAMEBUFFER
	_use_fbtft = false;
	_pfbtft = nullptr;
#ifdef ILI9488_USES_PALLET
	_pallet = NULL ;	// 

	// Probably should check that it did not fail... 
	_pallet_size = 0;					// How big is the pallet
	_pallet_count = 0;					// how many items are in it...
#endif
#endif
	setClipRect();
	setOrigin();
	setTextSize(textsize);
}

BMC_ILI9488_t3::BMC_ILI9488_t3(SPIClass *SPIWire, uint8_t cs, uint8_t dc, uint8_t rst, uint8_t mosi, uint8_t sclk, uint8_t miso)
{
	spi_port = SPIWire;

	_cs   = cs;
	_dc   = dc;
	_rst  = rst;
	_mosi = mosi;
	_sclk = sclk;
	_miso = miso;
	_width    = ILI9488_TFTWIDTH;
	_height   = ILI9488_TFTHEIGHT;
	rotation  = 0;
	cursor_y  = cursor_x    = 0;
	cursor_y  = cursor_x    = 0;
	textsize  = 1;
	textcolor = textbgcolor = 0xFFFF;
	wrap      = true;
	font      = NULL;
	// Added to see how much impact actually using non hardware CS pin might be
    _cspinmask = 0;
    _csport = NULL;
	
#ifdef ENABLE_ILI9488_FRAMEBUFFER
	_use_fbtft = false;
	_pfbtft = nullptr;
#ifdef ILI9488_USES_PALLET
	_pallet = NULL ;	// 

	// Probably should check that it did not fail... 
	_pallet_size = 0;					// How big is the pallet
	_pallet_count = 0;					// how many items are in it...
#endif
#endif
	setClipRect();
	setOrigin();
	setTextSize(textsize);
}

//=======================================================================
// Add optional support for using frame buffer to speed up complex outputs
//=======================================================================
	
	// Support for user to set Pallet. 
void BMC_ILI9488_t3::setPallet(uint16_t *pal, uint16_t count) {
#ifdef ILI9488_USES_PALLET
	if (_pallet && _pallet_size) free(_pallet);

	_pallet = pal;
	_pallet_count = count;
	_pallet_size = 0;	// assume we can not set this internally 
#endif
}

#ifdef ILI9488_USES_PALLET
uint8_t BMC_ILI9488_t3::doActualConvertColorToIndex(uint16_t color) {
	if (_pallet == nullptr) {
		// Need to allocate it... 
		_pallet = (uint16_t *)malloc(256*sizeof(uint16_t));	// 
		// Probably should check that it did not fail... 
    	_pallet_size = 256;					// How big is the pallet
    	_pallet_count = 0;					// how many items are in it...
	}
	
	if (_colors_are_index) return (uint8_t)color;

	for (uint8_t i = 0; i < _pallet_count; i++) {
		if (_pallet[i] == color) return i;
	}
	if (_pallet_count >=  _pallet_size) return 0;
	_pallet[_pallet_count] = color;
	return _pallet_count++;
}
	
#endif


void BMC_ILI9488_t3::setFrameBuffer(RAFB *frame_buffer) 
{
	#ifdef ENABLE_ILI9488_FRAMEBUFFER
	_pfbtft = frame_buffer;
	if (_pfbtft != NULL) {
		// Frame buffer is color index only here...
		memset(_pfbtft, 0, ILI9488_TFTHEIGHT*ILI9488_TFTWIDTH);
	}

	#endif	
}

#ifdef ENABLE_ILI9488_FRAMEBUFFER
void BMC_ILI9488_t3::setFrameCompleteCB(void (*pcb)(), bool fCallAlsoHalfDone)
{
	_frame_complete_callback = pcb;
	_frame_callback_on_HalfDone = pcb ? fCallAlsoHalfDone : false;

	noInterrupts();
	_dma_state &= ~ILI9488_DMA_INIT; // Lets setup  the call backs on next call out
	interrupts();
}
	#endif	

uint8_t BMC_ILI9488_t3::useFrameBuffer(boolean b)		// use the frame buffer?  First call will allocate
{
	#ifdef ENABLE_ILI9488_FRAMEBUFFER

	if (b) {
		// First see if we need to allocate buffer
		if (_pfbtft == NULL) {
			// Hack to start frame buffer on 32 byte boundary
			_we_allocated_buffer = (uint8_t *)malloc(CBALLOC+32);
			if (_we_allocated_buffer == NULL)
				return 0;	// failed 
			_pfbtft = (RAFB*) (((uintptr_t)_we_allocated_buffer + 32) & ~ ((uintptr_t) (31)));
			memset(_pfbtft, 0, CBALLOC);	
		}
		_use_fbtft = 1;
	} else 
		_use_fbtft = 0;

	return _use_fbtft;	
	#else
	return 0;
	#endif
}

void BMC_ILI9488_t3::freeFrameBuffer(void)						// explicit call to release the buffer
{
	#ifdef ENABLE_ILI9488_FRAMEBUFFER
	if (_we_allocated_buffer) {
		free(_we_allocated_buffer);
		_pfbtft = NULL;
		_use_fbtft = 0;	// make sure the use is turned off
		_we_allocated_buffer = NULL;
	}
	#endif
}
void BMC_ILI9488_t3::updateScreen(void)					// call to say update the screen now.
{
	// Not sure if better here to check flag or check existence of buffer.
	// Will go by buffer as maybe can do interesting things?
	#ifdef ENABLE_ILI9488_FRAMEBUFFER
	if (_use_fbtft) {
		beginSPITransaction();
		if (_standard) {
			//Serial.printf("Update Screen Standard %x(%x)\n", *_pfbtft, _pallet[*_pfbtft]);
			// Doing full window. 
			setAddr(0, 0, _width-1, _height-1);
			writecommand_cont(ILI9488_RAMWR);

			// BUGBUG doing as one shot.  Not sure if should or not or do like
			// main code and break up into transactions...
			RAFB *pfbtft_end = &_pfbtft[(ILI9488_TFTWIDTH*ILI9488_TFTHEIGHT)-1];	// setup 
			RAFB *pftbft = _pfbtft;

			// Quick write out the data;
			#ifdef ILI9488_USES_PALLET
			while (pftbft < pfbtft_end) {
				write16BitColor(_pallet[*pftbft++]);
			}
			write16BitColor(_pallet[*pftbft], true);
			#elif defined(ENABLE_EXT_DMA_UPDATES)
			maybeUpdateTCR(_tcr_dc_not_assert | LPSPI_TCR_FRAMESZ(23) | LPSPI_TCR_CONT);
			while (pftbft < pfbtft_end) {
				_pimxrt_spi->TDR = *pftbft++;
				_pending_rx_count++;	//
				waitFifoNotFull();
			}
			maybeUpdateTCR(_tcr_dc_not_assert | LPSPI_TCR_FRAMESZ(23));
			_pimxrt_spi->TDR = *pftbft;
			_pending_rx_count++;	//
			waitTransmitComplete();

			#else
			while (pftbft < pfbtft_end) {
				write16BitColor(*pftbft++);
			}
			write16BitColor(*pftbft, true);
			#endif
		} else {
			// setup just to output the clip rectangle area. 
			setAddr(_displayclipx1, _displayclipy1, _displayclipx2-1, _displayclipy2-1);
			writecommand_cont(ILI9488_RAMWR);

			// BUGBUG doing as one shot.  Not sure if should or not or do like
			// main code and break up into transactions...
			RAFB * pfbPixel_row = &_pfbtft[ _displayclipy1*_width + _displayclipx1];
			#ifdef ILI9488_USES_PALLET
			for (uint16_t y = _displayclipy1; y < _displayclipy2; y++) {
				RAFB * pfbPixel = pfbPixel_row;
				for (uint16_t x = _displayclipx1; x < (_displayclipx2-1); x++) {
					write16BitColor(_pallet[*pfbPixel++]);
				}
				if (y < (_displayclipy2-1))
					write16BitColor(_pallet[*pfbPixel]);
				else	
					write16BitColor(_pallet[*pfbPixel], true);
				pfbPixel_row += _width;	// setup for the next row. 
			}
			#elif defined(ENABLE_EXT_DMA_UPDATES)

			maybeUpdateTCR(_tcr_dc_not_assert | LPSPI_TCR_FRAMESZ(23) | LPSPI_TCR_CONT);
			for (uint16_t y = _displayclipy1; y < _displayclipy2; y++) {
				RAFB * pfbPixel = pfbPixel_row;
				for (uint16_t x = _displayclipx1; x < (_displayclipx2-1); x++) {
					_pimxrt_spi->TDR = *pfbPixel++;
					_pending_rx_count++;	//
					waitFifoNotFull();
				}
				if (y < (_displayclipy2-1)) {
					_pimxrt_spi->TDR = *pfbPixel;
					_pending_rx_count++;	//
					waitFifoNotFull();
				} else {
					maybeUpdateTCR(_tcr_dc_not_assert | LPSPI_TCR_FRAMESZ(23));
					_pimxrt_spi->TDR = *pfbPixel;
					_pending_rx_count++;	//
					waitTransmitComplete();

				}	
				pfbPixel_row += _width;	// setup for the next row. 
			}

			#else
			for (uint16_t y = _displayclipy1; y < _displayclipy2; y++) {
				RAFB * pfbPixel = pfbPixel_row;
				for (uint16_t x = _displayclipx1; x < (_displayclipx2-1); x++) {
					write16BitColor(*pfbPixel++);
				}
				if (y < (_displayclipy2-1))
					write16BitColor(*pfbPixel);
				else	
					write16BitColor(*pfbPixel, true);
				pfbPixel_row += _width;	// setup for the next row. 
			}
			#endif
		}
		endSPITransaction();
	}
	#endif
}			 




void BMC_ILI9488_t3::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	beginSPITransaction();
	setAddr(x0, y0, x1, y1);
	writecommand_last(ILI9488_RAMWR); // write to RAM
	endSPITransaction();
}

void BMC_ILI9488_t3::write16BitColor(uint16_t color, bool last_pixel){
  // #if (__STM32F1__)
  //     uint8_t buff[4] = {
  //       (((color & 0xF800) >> 11)* 255) / 31,
  //       (((color & 0x07E0) >> 5) * 255) / 63,
  //       ((color & 0x001F)* 255) / 31
  //     };
  //     spi_port->dmaSend(buff, 3);
  // #else
#if defined(__IMXRT1052__) || defined(__IMXRT1062__)  // Teensy 4.x
  uint8_t r = (color & 0xF800) >> 11;
  uint8_t g = (color & 0x07E0) >> 5;
  uint8_t b = color & 0x001F;

  r = (r * 255) / 31;
  g = (g * 255) / 63;
  b = (b * 255) / 31;
  uint32_t color24 = ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
  if (last_pixel)  {
	maybeUpdateTCR(_tcr_dc_not_assert | LPSPI_TCR_FRAMESZ(23));
	_pimxrt_spi->TDR = color24;
	_pending_rx_count++;	//
	waitTransmitComplete();
  } else {
	maybeUpdateTCR(_tcr_dc_not_assert | LPSPI_TCR_FRAMESZ(23) | LPSPI_TCR_CONT);
	_pimxrt_spi->TDR = color24;
	_pending_rx_count++;	//
	waitFifoNotFull();
  }

#elif defined(KINETISK)
  uint8_t r = (color & 0xF800) >> 11;
  r = (r * 255) / 31;
  writedata8_cont(r);

  uint8_t g = (color & 0x07E0) >> 5;
  g = (g * 255) / 63;
  writedata8_cont(g);

  uint8_t b = color & 0x001F;
  b = (b * 255) / 31;
  if (last_pixel)  {
  	writedata8_last(b);
  } else {
  	writedata8_cont(b);
  }
#elif defined(KINETISL)
  uint8_t r = (color & 0xF800) >> 11;

  r = (r * 255) / 31;
  setDataMode();
  outputToSPI(r);
  uint8_t g = (color & 0x07E0) >> 5;
  g = (g * 255) / 63;
  outputToSPIAlready8Bits(g);
  uint8_t b = color & 0x001F;
  b = (b * 255) / 31;
  outputToSPIAlready8Bits(b);
  if (last_pixel) {
	waitTransmitComplete();
  } 

#endif
  // #endif
}


void BMC_ILI9488_t3::write16BitColor(uint16_t color, uint16_t count, bool last_pixel){
#if defined(__IMXRT1052__) || defined(__IMXRT1062__)  // Teensy 4.x
  uint8_t r = (color & 0xF800) >> 11;
  uint8_t g = (color & 0x07E0) >> 5;
  uint8_t b = color & 0x001F;

  r = (r * 255) / 31;
  g = (g * 255) / 63;
  b = (b * 255) / 31;
  uint32_t color24 = ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
  while (count > 1) {
	maybeUpdateTCR(_tcr_dc_not_assert | LPSPI_TCR_FRAMESZ(23) | LPSPI_TCR_CONT);
	_pimxrt_spi->TDR = color24;
	_pending_rx_count++;	//
	waitFifoNotFull();
	count--;  	
  }

  if (last_pixel)  {
	maybeUpdateTCR(_tcr_dc_not_assert | LPSPI_TCR_FRAMESZ(23));
	_pimxrt_spi->TDR = color24;
	_pending_rx_count++;	//
	waitTransmitComplete();
  } else {
	maybeUpdateTCR(_tcr_dc_not_assert | LPSPI_TCR_FRAMESZ(23) | LPSPI_TCR_CONT);
	_pimxrt_spi->TDR = color24;
	_pending_rx_count++;	//
	waitFifoNotFull();
  }

#elif defined(KINETISK)
  if (count < 2) {
  	write16BitColor(color, last_pixel);
  	return;
  }
  uint8_t r = (color & 0xF800) >> 11;
  r = (r * 255) / 31;
  writedata8_cont(r);

  uint8_t g = (color & 0x07E0) >> 5;
  g = (g * 255) / 63;
  writedata8_cont(g);

  uint8_t b = color & 0x001F;
  b = (b * 255) / 31;

  writedata8_cont(b);
 
  while (--count) {
	  writedata8_cont(r);
	  writedata8_cont(g);

	  if ((count == 1) && last_pixel)  {
	  	writedata8_last(b);
	  } else {
	  	writedata8_cont(b);
	  }
  }
#elif defined(KINETISL)
  uint8_t r = (color & 0xF800) >> 11;

  r = (r * 255) / 31;
  setDataMode();
  outputToSPI(r);
  uint8_t g = (color & 0x07E0) >> 5;
  g = (g * 255) / 63;
  outputToSPIAlready8Bits(g);
  uint8_t b = color & 0x001F;
  b = (b * 255) / 31;
  outputToSPIAlready8Bits(b);
  while (--count) {
	  outputToSPIAlready8Bits(r);
	  outputToSPIAlready8Bits(g);
	  outputToSPIAlready8Bits(b);
  }

  if (last_pixel) {
		waitTransmitComplete();
  } 

#endif
}



void BMC_ILI9488_t3::pushColor(uint16_t color)
{
	beginSPITransaction();
	//write16BitColor(color);
	write16BitColor(color, true);
	endSPITransaction();
}

void BMC_ILI9488_t3::drawPixel(int16_t x, int16_t y, uint16_t color) {
	x += _originx;
	y += _originy;
	if((x < _displayclipx1) ||(x >= _displayclipx2) || (y < _displayclipy1) || (y >= _displayclipy2)) return;

	#ifdef ENABLE_ILI9488_FRAMEBUFFER
	if (_use_fbtft) {
		_pfbtft[y*_width + x] = mapColorToPalletIndex(color);

	} else 
	#endif
	{
		beginSPITransaction();
		setAddr(x, y, x, y);
		writecommand_cont(ILI9488_RAMWR);
		write16BitColor(color, true);
		endSPITransaction();
	}
}

void BMC_ILI9488_t3::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
	x+=_originx;
	y+=_originy;
	// Rectangular clipping
	if((x < _displayclipx1) || (x >= _displayclipx2) || (y >= _displayclipy2)) return;
	if(y < _displayclipy1) { h = h - (_displayclipy1 - y); y = _displayclipy1;}
	if((y+h-1) >= _displayclipy2) h = _displayclipy2-y;
	if(h<1) return;

	#ifdef ENABLE_ILI9488_FRAMEBUFFER
	if (_use_fbtft) {
		RAFB * pfbPixel = &_pfbtft[ y*_width + x];
		RAFB color_index = mapColorToPalletIndex(color);
		while (h--) {
			*pfbPixel = color_index;
			pfbPixel += _width;
		}
	} else 
	#endif
	{
		beginSPITransaction();
		setAddr(x, y, x, y+h-1);
		writecommand_cont(ILI9488_RAMWR);
		write16BitColor(color,h, true);
		endSPITransaction();
	}
}

void BMC_ILI9488_t3::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
	x+=_originx;
	y+=_originy;

	// Rectangular clipping
	if((y < _displayclipy1) || (x >= _displayclipx2) || (y >= _displayclipy2)) return;
	if(x<_displayclipx1) { w = w - (_displayclipx1 - x); x = _displayclipx1; }
	if((x+w-1) >= _displayclipx2)  w = _displayclipx2-x;
	if (w<1) return;

	#ifdef ENABLE_ILI9488_FRAMEBUFFER
	if (_use_fbtft) {
		RAFB color_index = mapColorToPalletIndex(color);
		RAFB * pfbPixel = &_pfbtft[ y*_width + x];
		while (w--) {
			*pfbPixel++ = color_index;
		}
	} else 
	#endif
	{
		beginSPITransaction();
		setAddr(x, y, x+w-1, y);
		writecommand_cont(ILI9488_RAMWR);
		write16BitColor(color, w, true);
		endSPITransaction();
	}
}

void BMC_ILI9488_t3::fillScreen(uint16_t color)
{
	fillRect(0, 0, _width, _height, color);
}

// fill a rectangle
void BMC_ILI9488_t3::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
	x+=_originx;
	y+=_originy;

	// Rectangular clipping (drawChar w/big text requires this)
	if((x >= _displayclipx2) || (y >= _displayclipy2)) return;
	if (((x+w) <= _displayclipx1) || ((y+h) <= _displayclipy1)) return;
	if(x < _displayclipx1) {	w -= (_displayclipx1-x); x = _displayclipx1; 	}
	if(y < _displayclipy1) {	h -= (_displayclipy1 - y); y = _displayclipy1; 	}
	if((x + w - 1) >= _displayclipx2)  w = _displayclipx2  - x;
	if((y + h - 1) >= _displayclipy2) h = _displayclipy2 - y;

	#ifdef ENABLE_ILI9488_FRAMEBUFFER
	if (_use_fbtft) {
		RAFB color_index = mapColorToPalletIndex(color);
		//if (x==0 && y == 0) Serial.printf("fillrect %x %x %x\n", color, color_index, _pallet[color_index]);
		//if (1 || (x&3) || (w&3)) {
			RAFB * pfbPixel_row = &_pfbtft[ y*_width + x];
			for (;h>0; h--) {
				RAFB * pfbPixel = pfbPixel_row;
				for (int i = 0 ;i < w; i++) {
					*pfbPixel++ = color_index;
				}
				pfbPixel_row += _width;
			}
		/*} else {  // never used as if(1 above...)
			// Horizontal is even number so try 32 bit writes instead
			uint32_t color32 = ((uint32_t)color_index << 24) | ((uint32_t)color_index << 16) | ((uint32_t)color_index << 8) | color_index;
			uint32_t * pfbPixel_row = (uint32_t *)((RAFB*)&_pfbtft[ y*_width + x]);
			w = w/4;	// only iterate quarter the times
			for (;h>0; h--) {
				uint32_t * pfbPixel = pfbPixel_row;
				for (int i = 0 ;i < w; i++) {
					*pfbPixel++ = color32;
				}
				pfbPixel_row += (_width/4);
			}
		} */
	} else 
	#endif
	{

		// TODO: this can result in a very long transaction time
		// should break this into multiple transactions, even though
		// it'll cost more overhead, so we don't stall other SPI libs
		beginSPITransaction();
		setAddr(x, y, x+w-1, y+h-1);
		writecommand_cont(ILI9488_RAMWR);
		for(y=h; y>0; y--) {
			write16BitColor(color, w, true);
#if 0
			if (y > 1 && (y & 1)) {
				endSPITransaction();
				beginSPITransaction();
			}
#endif			
		}
		endSPITransaction();
	}
}

// fillRectVGradient	- fills area with vertical gradient
void BMC_ILI9488_t3::fillRectVGradient(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color1, uint16_t color2)
{
	x+=_originx;
	y+=_originy;

	// Rectangular clipping 
	if((x >= _displayclipx2) || (y >= _displayclipy2)) return;
	if(x < _displayclipx1) {	w -= (_displayclipx1-x); x = _displayclipx1; 	}
	if(y < _displayclipy1) {	h -= (_displayclipy1 - y); y = _displayclipy1; 	}
	if((x + w - 1) >= _displayclipx2)  w = _displayclipx2  - x;
	if((y + h - 1) >= _displayclipy2) h = _displayclipy2 - y;
	
	int16_t r1, g1, b1, r2, g2, b2, dr, dg, db, r, g, b;
	color565toRGB14(color1,r1,g1,b1);
	color565toRGB14(color2,r2,g2,b2);
	dr=(r2-r1)/h; dg=(g2-g1)/h; db=(b2-b1)/h;
	r=r1;g=g1;b=b1;	

	#ifdef ENABLE_ILI9488_FRAMEBUFFER
	if (_use_fbtft) {
		RAFB * pfbPixel_row = &_pfbtft[ y*_width + x];
		for (;h>0; h--) {
			uint16_t color = RGB14tocolor565(r,g,b);
			RAFB * pfbPixel = pfbPixel_row;
			for (int i = 0 ;i < w; i++) {
				*pfbPixel++ = mapColorToPalletIndex(color);
			}
			r+=dr;g+=dg; b+=db;
			pfbPixel_row += _width;
		}
	} else 
	#endif
	{		
		beginSPITransaction();
		setAddr(x, y, x+w-1, y+h-1);
		writecommand_cont(ILI9488_RAMWR);
		for(y=h; y>0; y--) {
			uint16_t color = RGB14tocolor565(r,g,b);

			for(x=w; x>1; x--) {
				write16BitColor(color);
			}
			write16BitColor(color, true);
			if (y > 1 && (y & 1)) {
				endSPITransaction();
				beginSPITransaction();
			}
			r+=dr;g+=dg; b+=db;
		}
		endSPITransaction();
	}
}

// fillRectHGradient	- fills area with horizontal gradient
void BMC_ILI9488_t3::fillRectHGradient(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color1, uint16_t color2)
{
	x+=_originx;
	y+=_originy;

	// Rectangular clipping 
	if((x >= _displayclipx2) || (y >= _displayclipy2)) return;
	if(x < _displayclipx1) {	w -= (_displayclipx1-x); x = _displayclipx1; 	}
	if(y < _displayclipy1) {	h -= (_displayclipy1 - y); y = _displayclipy1; 	}
	if((x + w - 1) >= _displayclipx2)  w = _displayclipx2  - x;
	if((y + h - 1) >= _displayclipy2) h = _displayclipy2 - y;
	
	int16_t r1, g1, b1, r2, g2, b2, dr, dg, db, r, g, b;
	uint16_t color;
	color565toRGB14(color1,r1,g1,b1);
	color565toRGB14(color2,r2,g2,b2);
	dr=(r2-r1)/w; dg=(g2-g1)/w; db=(b2-b1)/w;
	r=r1;g=g1;b=b1;	
	#ifdef ENABLE_ILI9488_FRAMEBUFFER
	if (_use_fbtft) {
		RAFB * pfbPixel_row = &_pfbtft[ y*_width + x];
		for (;h>0; h--) {
			RAFB * pfbPixel = pfbPixel_row;
			for (int i = 0 ;i < w; i++) {
				*pfbPixel++ = mapColorToPalletIndex(RGB14tocolor565(r,g,b));
				r+=dr;g+=dg; b+=db;
			}
			pfbPixel_row += _width;
			r=r1;g=g1;b=b1;
		}
	} else 
	#endif
	{
		beginSPITransaction();
		setAddr(x, y, x+w-1, y+h-1);
		writecommand_cont(ILI9488_RAMWR);
		for(y=h; y>0; y--) {
			for(x=w; x>1; x--) {
				color = RGB14tocolor565(r,g,b);
				write16BitColor(color);
				r+=dr;g+=dg; b+=db;
			}
			color = RGB14tocolor565(r,g,b);
			write16BitColor(color, true);
			if (y > 1 && (y & 1)) {
				endSPITransaction();
				beginSPITransaction();
			}
			r=r1;g=g1;b=b1;
		}
		endSPITransaction();
	}
}

// fillScreenVGradient - fills screen with vertical gradient
void BMC_ILI9488_t3::fillScreenVGradient(uint16_t color1, uint16_t color2)
{
	fillRectVGradient(0,0,_width,_height,color1,color2);
}

// fillScreenHGradient - fills screen with horizontal gradient
void BMC_ILI9488_t3::fillScreenHGradient(uint16_t color1, uint16_t color2)
{
	fillRectHGradient(0,0,_width,_height,color1,color2);
}


#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH  0x04

void BMC_ILI9488_t3::setRotation(uint8_t m)
{
	rotation = m % 4; // can't be higher than 3
	beginSPITransaction();
	writecommand_cont(ILI9488_MADCTL);
	switch (rotation) {
	case 0:
		writedata8_last(MADCTL_MX | MADCTL_BGR);
		_width  = ILI9488_TFTWIDTH;
		_height = ILI9488_TFTHEIGHT;
		break;
	case 1:
		writedata8_last(MADCTL_MV | MADCTL_BGR);
		_width  = ILI9488_TFTHEIGHT;
		_height = ILI9488_TFTWIDTH;
		break;
	case 2:
		writedata8_last(MADCTL_MY | MADCTL_BGR);
		_width  = ILI9488_TFTWIDTH;
		_height = ILI9488_TFTHEIGHT;
		break;
	case 3:
		writedata8_last(MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
		_width  = ILI9488_TFTHEIGHT;
		_height = ILI9488_TFTWIDTH;
		break;
	}
	endSPITransaction();
	setClipRect();
	setOrigin();
	
	cursor_x = 0;
	cursor_y = 0;
}

void BMC_ILI9488_t3::setScroll(uint16_t offset)
{
	beginSPITransaction();
	writecommand_cont(ILI9488_VSCRSADD);
	writedata16_last(offset);
	endSPITransaction();
}

void BMC_ILI9488_t3::invertDisplay(boolean i)
{
	beginSPITransaction();
	writecommand_last(i ? ILI9488_INVON : ILI9488_INVOFF);
	endSPITransaction();
}










/*
uint8_t BMC_ILI9488_t3::readdata(void)
{
  uint8_t r;
       // Try to work directly with SPI registers...
       // First wait until output queue is empty
        uint16_t wTimeout = 0xffff;
        while (((_pkinetisk_spi->SR) & (15 << 12)) && (--wTimeout)) ; // wait until empty
        
//       	_pkinetisk_spi->MCR |= SPI_MCR_CLR_RXF; // discard any received data
//		_pkinetisk_spi->SR = SPI_SR_TCF;
        
        // Transfer a 0 out... 
        writedata8_cont(0);   
        
        // Now wait until completed. 
        wTimeout = 0xffff;
        while (((_pkinetisk_spi->SR) & (15 << 12)) && (--wTimeout)) ; // wait until empty
        r = _pkinetisk_spi->POPR;  // get the received byte... should check for it first...
    return r;
}
 */


uint8_t BMC_ILI9488_t3::readcommand8(uint8_t c, uint8_t index)
{
    // Bail if not valid miso
    if (_miso == 0xff) return 0;

 #ifdef KINETISK
    uint16_t wTimeout = 0xffff;
    uint8_t r=0;

    beginSPITransaction();

    while (((_pkinetisk_spi->SR) & (15 << 12)) && (--wTimeout)) ; // wait until empty

    // Make sure the last frame has been sent...
    _pkinetisk_spi->SR = SPI_SR_TCF;   // dlear it out;
    wTimeout = 0xffff;
    while (!((_pkinetisk_spi->SR) & SPI_SR_TCF) && (--wTimeout)) ; // wait until it says the last frame completed

    // clear out any current received bytes
    wTimeout = 0x10;    // should not go more than 4...
    while ((((_pkinetisk_spi->SR) >> 4) & 0xf) && (--wTimeout))  {
        r = _pkinetisk_spi->POPR;
    }

    //writecommand(0xD9); // sekret command
	_pkinetisk_spi->PUSHR = 0xD9 | (pcs_command << 16) | SPI_PUSHR_CTAS(0) | SPI_PUSHR_CONT;
//	while (((_pkinetisk_spi->SR) & (15 << 12)) > (3 << 12)) ; // wait if FIFO full

    // writedata(0x10 + index);
	_pkinetisk_spi->PUSHR = (0x10 + index) | (pcs_data << 16) | SPI_PUSHR_CTAS(0);
//	while (((_pkinetisk_spi->SR) & (15 << 12)) > (3 << 12)) ; // wait if FIFO full

    // writecommand(c);
   	_pkinetisk_spi->PUSHR = c | (pcs_command << 16) | SPI_PUSHR_CTAS(0) | SPI_PUSHR_CONT;
//	while (((_pkinetisk_spi->SR) & (15 << 12)) > (3 << 12)) ; // wait if FIFO full

    // readdata
	_pkinetisk_spi->PUSHR = 0 | (pcs_data << 16) | SPI_PUSHR_CTAS(0);
//	while (((_pkinetisk_spi->SR) & (15 << 12)) > (3 << 12)) ; // wait if FIFO full

    // Now wait until completed.
    wTimeout = 0xffff;
    while (((_pkinetisk_spi->SR) & (15 << 12)) && (--wTimeout)) ; // wait until empty

    // Make sure the last frame has been sent...
    _pkinetisk_spi->SR = SPI_SR_TCF;   // dlear it out;
    wTimeout = 0xffff;
    while (!((_pkinetisk_spi->SR) & SPI_SR_TCF) && (--wTimeout)) ; // wait until it says the last frame completed

    wTimeout = 0x10;    // should not go more than 4...
    // lets get all of the values on the FIFO
    while ((((_pkinetisk_spi->SR) >> 4) & 0xf) && (--wTimeout))  {
        r = _pkinetisk_spi->POPR;
    }
    endSPITransaction();
    return r;  // get the received byte... should check for it first...
#elif defined(__IMXRT1052__) || defined(__IMXRT1062__)  // Teensy 4.x 
    uint16_t wTimeout = 0xffff;
    uint8_t r=0;

    beginSPITransaction(ILI9488_SPICLOCK_READ);
    // Lets assume that queues are empty as we just started transaction.
	_pimxrt_spi->CR = LPSPI_CR_MEN | LPSPI_CR_RRF /*| LPSPI_CR_RTF */;   // actually clear both...
    //writecommand(0xD9); // sekret command
    maybeUpdateTCR(_tcr_dc_assert | LPSPI_TCR_FRAMESZ(7) | LPSPI_TCR_CONT);
	_pimxrt_spi->TDR = 0xD9;

    // writedata(0x10 + index);
	maybeUpdateTCR(_tcr_dc_not_assert | LPSPI_TCR_FRAMESZ(7) | LPSPI_TCR_CONT);
	_pimxrt_spi->TDR = 0x10 + index;

    // writecommand(c);
    maybeUpdateTCR(_tcr_dc_assert | LPSPI_TCR_FRAMESZ(7) | LPSPI_TCR_CONT);
	_pimxrt_spi->TDR = c;

    // readdata
	maybeUpdateTCR(_tcr_dc_not_assert | LPSPI_TCR_FRAMESZ(7));
	_pimxrt_spi->TDR = 0;

    // Now wait until completed.
    wTimeout = 0xffff;
    uint8_t rx_count = 4;
    while (rx_count && wTimeout) {
        if ((_pimxrt_spi->RSR & LPSPI_RSR_RXEMPTY) == 0)  {
            r =_pimxrt_spi->RDR;  // Read any pending RX bytes in
            rx_count--; //decrement count of bytes still levt
        }
    }
    endSPITransaction();
    return r;  // get the received byte... should check for it first...
#else
	beginSPITransaction();
	writecommand_cont(0xD9);
	writedata8_cont(0x10 + index);

	writecommand_cont(c);
	writedata8_cont(0);
	uint8_t r = 0; //waitTransmitCompleteReturnLast();
	endSPITransaction();
	return r;

#endif   
}



// Read Pixel at x,y and get back 16-bit packed color
#define READ_PIXEL_PUSH_BYTE 0x3f
uint16_t BMC_ILI9488_t3::readPixel(int16_t x, int16_t y)
{
#ifdef KINETISK	
	//BUGBUG:: Should add some validation of X and Y
	// Now if we are in buffer mode can return real fast
	#ifdef ENABLE_ILI9488_FRAMEBUFFER
	if (_use_fbtft) {
		x+=_originx;
		y+=_originy;

		uint8_t color_index =  _pfbtft[y*_width + x];
		return _colors_are_index ? color_index : _pallet[color_index];
	}
	#endif	

   if (_miso == 0xff) return 0xffff;	// bail if not valid miso

	// First pass for other SPI busses use readRect to handle the read... 
	//if (SPIClass::hardware().queue_size < 4) {
	//	uint16_t colors;
	//	readRect(x, y, 1, 1, &colors);
	//	return colors;
	//}

	uint8_t dummy __attribute__((unused));
	uint8_t r,g,b;

	beginSPITransaction(ILI9488_SPICLOCK_READ);

	// Update our origin. 
	x+=_originx;
	y+=_originy;

	setAddr(x, y, x, y);
	writecommand_cont(ILI9488_RAMRD); // read from RAM
	waitTransmitComplete();

	// Push 4 bytes over SPI
	_pkinetisk_spi->PUSHR = 0 | (pcs_data << 16) | SPI_PUSHR_CTAS(0)| SPI_PUSHR_CONT;
	waitFifoEmpty();    // wait for both queues to be empty.

	_pkinetisk_spi->PUSHR = 0 | (pcs_data << 16) | SPI_PUSHR_CTAS(0)| SPI_PUSHR_CONT;
	_pkinetisk_spi->PUSHR = 0 | (pcs_data << 16) | SPI_PUSHR_CTAS(0)| SPI_PUSHR_CONT;
	_pkinetisk_spi->PUSHR = 0 | (pcs_data << 16) | SPI_PUSHR_CTAS(0)| SPI_PUSHR_EOQ;

	// Wait for End of Queue
	while ((_pkinetisk_spi->SR & SPI_SR_EOQF) == 0) ;
	_pkinetisk_spi->SR = SPI_SR_EOQF;  // make sure it is clear

	// Read Pixel Data
	dummy = _pkinetisk_spi->POPR;	// Read a DUMMY byte of GRAM
	r = _pkinetisk_spi->POPR;		// Read a RED byte of GRAM
	g = _pkinetisk_spi->POPR;		// Read a GREEN byte of GRAM
	b = _pkinetisk_spi->POPR;		// Read a BLUE byte of GRAM

	endSPITransaction();
	return color565(r,g,b);
#else
	// Kinetisk
	uint16_t colors = 0;
	readRect(x, y, 1, 1, &colors);
	return colors;
#endif	
}

// Now lets see if we can read in multiple pixels
#ifdef KINETISK
void BMC_ILI9488_t3::readRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t *pcolors)
{
	// Use our Origin. 
	x+=_originx;
	y+=_originy;
	//BUGBUG:: Should add some validation of X and Y

	#ifdef ENABLE_ILI9488_FRAMEBUFFER
	if (_use_fbtft) {
		RAFB * pfbPixel_row = &_pfbtft[ y*_width + x];
		for (;h>0; h--) {
			RAFB * pfbPixel = pfbPixel_row;
			for (int i = 0 ;i < w; i++) {
#ifdef ILI9488_USES_PALLET
				uint8_t color_index = *pfbPixel++;
				*pcolors++ = _colors_are_index? color_index : _pallet[color_index];
#elif defined(ENABLE_EXT_DMA_UPDATES)
#else
				*pcolors++ = *pfbPixel++;
#endif				
			}
			pfbPixel_row += _width;
		}
		return;	
	}
	#endif	

   if (_miso == 0xff) return;		// bail if not valid miso

	uint8_t rgb[3];               // RGB bytes received from the display
	uint8_t rgbIdx = 0;
	uint32_t txCount = w * h * 3; // number of bytes we will transmit to the display
	uint32_t rxCount = txCount;   // number of bytes we will receive back from the display

	beginSPITransaction(ILI9488_SPICLOCK_READ);

	setAddr(x, y, x+w-1, y+h-1);
	writecommand_cont(ILI9488_RAMRD); // read from RAM

	// transmit a DUMMY byte before the color bytes
	_pkinetisk_spi->PUSHR = 0 | (pcs_data << 16) | SPI_PUSHR_CTAS(0)| SPI_PUSHR_CONT;

	// skip values returned by the queued up transfers and the current in-flight transfer
	uint32_t sr = _pkinetisk_spi->SR;
	uint8_t skipCount = ((sr >> 4) & 0xF) + ((sr >> 12) & 0xF) + 1;

	while (txCount || rxCount) {
		// transmit another byte if possible
		//if (txCount && ((_pkinetisk_spi->SR & 0xF000) >> 12) < SPIClass::hardware().queue_size()) {
		if (txCount && ((_pkinetisk_spi->SR & 0xF000) >> 12) < _fifo_size) {
			txCount--;
			if (txCount) {
				_pkinetisk_spi->PUSHR = READ_PIXEL_PUSH_BYTE | (pcs_data << 16) | SPI_PUSHR_CTAS(0)| SPI_PUSHR_CONT;
			} else {
				_pkinetisk_spi->PUSHR = READ_PIXEL_PUSH_BYTE | (pcs_data << 16) | SPI_PUSHR_CTAS(0)| SPI_PUSHR_EOQ;
			}
		}

		// receive another byte if possible, and either skip it or store the color
		if (rxCount && (_pkinetisk_spi->SR & 0xF0)) {
			rgb[rgbIdx] = _pkinetisk_spi->POPR;

			if (skipCount) {
				skipCount--;
			} else {
				rxCount--;
				rgbIdx++;
				if (rgbIdx == 3) {
					rgbIdx = 0;
					*pcolors++ = color565(rgb[0], rgb[1], rgb[2]);
				}
			}
		}
	}

	// wait for End of Queue
	while ((_pkinetisk_spi->SR & SPI_SR_EOQF) == 0) ;
	_pkinetisk_spi->SR = SPI_SR_EOQF;  // make sure it is clear
	endSPITransaction();

}
#elif defined(__IMXRT1052__) || defined(__IMXRT1062__)  // Teensy 4.x 
void BMC_ILI9488_t3::readRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t *pcolors)
{
	// Use our Origin. 
	x+=_originx;
	y+=_originy;
	//BUGBUG:: Should add some validation of X and Y

	#ifdef ENABLE_ILI9488_FRAMEBUFFER
	if (_use_fbtft) {
		RAFB * pfbPixel_row = &_pfbtft[ y*_width + x];
		for (;h>0; h--) {
			RAFB * pfbPixel = pfbPixel_row;
			for (int i = 0 ;i < w; i++) {
#ifdef ILI9488_USES_PALLET
				uint16_t color_index = *pfbPixel++;
				*pcolors++ = _colors_are_index? color_index : _pallet[color_index];
#elif defined(ENABLE_EXT_DMA_UPDATES)
				// convert 666 to 565 Note: it is actually stored as 3 bytes with 6 pixels of color per byte
				uint16_t color = (*pfbPixel >> 1) & 0x001f;	// gets the 5b
				color |= ((*pfbPixel >> 3) 		  & 0x07e0); 		// Should get us the 6G 
				color |= ((*pfbPixel >> 6) 		  & 0xf800);		   // should add on the 5R to top
				*pcolors++ = color;
				#if 0
				static uint8_t debug_output_count = 0;
				static uint32_t color_converted[10];
				if (debug_output_count < 10) {
					// See if this color has been converted again.
					uint8_t i;
					for (i= 0; i < debug_output_count; i++) {
						if (color_converted[i] == *pfbPixel) break;
					}
					if (i == debug_output_count) {
						Serial.printf("\n>>>Convert 666(%x) to 565(%x)\n", *pfbPixel, color);
						color_converted[debug_output_count] = *pfbPixel;
						debug_output_count++;
					}
				}
				#endif
				pfbPixel++;

#else
				*pcolors++ = *pfbPixel++;
#endif				
			}
			pfbPixel_row += _width;
		}
		return;	
	}
	#endif	

   if (_miso == 0xff) return;		// bail if not valid miso

	uint8_t rgb[3];               // RGB bytes received from the display
	uint8_t rgbIdx = 0;
	uint32_t txCount = w * h * 3; // number of bytes we will transmit to the display
	uint32_t rxCount = txCount;   // number of bytes we will receive back from the display

	beginSPITransaction(ILI9488_SPICLOCK_READ);

	setAddr(x, y, x+w-1, y+h-1);
	writecommand_cont(ILI9488_RAMRD); // read from RAM


	// transmit a DUMMY byte before the color bytes
	writedata8_last(0);		// BUGBUG:: maybe fix this as this will wait until the byte fully transfers through.

	while (txCount || rxCount) {
		// transmit another byte if possible
		if (txCount && (_pimxrt_spi->SR & LPSPI_SR_TDF)) {
			txCount--;
			if (txCount) {
				_pimxrt_spi->TDR = 0;
			} else {
				maybeUpdateTCR(_tcr_dc_not_assert | LPSPI_TCR_FRAMESZ(7)); // remove the CONTINUE...
				while ((_pimxrt_spi->SR & LPSPI_SR_TDF) == 0) ;		// wait if queue was full
				_pimxrt_spi->TDR = 0;
			}
		}

		// receive another byte if possible, and either skip it or store the color
		if (rxCount && !(_pimxrt_spi->RSR & LPSPI_RSR_RXEMPTY)) {
			rgb[rgbIdx] = _pimxrt_spi->RDR;

			rxCount--;
			rgbIdx++;
			if (rgbIdx == 3) {
				rgbIdx = 0;
				*pcolors++ = color565(rgb[0], rgb[1], rgb[2]);
			}
		}
	}

	// We should have received everything so should be done
	endSPITransaction();
}

#else

// Teensy LC version
void BMC_ILI9488_t3::readRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t *pcolors)
{
	// Use our Origin. 
	x+=_originx;
	y+=_originy;
	//BUGBUG:: Should add some validation of X and Y

   if (_miso == 0xff) return;		// bail if not valid miso

	uint8_t rgb[3];               // RGB bytes received from the display
	uint8_t rgbIdx = 0;
	uint32_t txCount = w * h * 3; // number of bytes we will transmit to the display
	uint32_t rxCount = txCount;   // number of bytes we will receive back from the display

	beginSPITransaction(ILI9488_SPICLOCK_READ);

	setAddr(x, y, x+w-1, y+h-1);
	writecommand_cont(ILI9488_RAMRD); // read from RAM

	// transmit a DUMMY byte before the color bytes
	writedata8_cont(0);

	// Wait until that one returns, Could do a little better and double buffer but this is easer for now.
	waitTransmitComplete();

	// Since double buffer setup lets try keeping read/write in sync
#define RRECT_TIMEOUT 0xffff	
#undef 	READ_PIXEL_PUSH_BYTE
#define READ_PIXEL_PUSH_BYTE 0 // try with zero to see... 	
	uint16_t timeout_countdown = RRECT_TIMEOUT;
	uint16_t dl_in;
	// Write out first byte:

	while (!(KINETISL_SPI0.S & SPI_S_SPTEF)) ; // Not worried that this can completely hang?
	KINETISL_SPI0.DL = READ_PIXEL_PUSH_BYTE;

	while (rxCount && timeout_countdown) {
		// Now wait until we can output something
		dl_in = 0xffff;
		if (rxCount > 1) {
			while (!(KINETISL_SPI0.S & SPI_S_SPTEF)) ; // Not worried that this can completely hang?
			if (KINETISL_SPI0.S & SPI_S_SPRF)
				dl_in = KINETISL_SPI0.DL;  
			KINETISL_SPI0.DL = READ_PIXEL_PUSH_BYTE;
		}

		// Now wait until there is a byte available to receive
		while ((dl_in != 0xffff) && !(KINETISL_SPI0.S & SPI_S_SPRF) && --timeout_countdown) ;
		if (timeout_countdown) {   // Make sure we did not get here because of timeout 
			rxCount--;
			rgb[rgbIdx] = (dl_in != 0xffff)? dl_in : KINETISL_SPI0.DL;
			rgbIdx++;
			if (rgbIdx == 3) {
				rgbIdx = 0;
				*pcolors++ = color565(rgb[0], rgb[1], rgb[2]);
			}
			timeout_countdown = timeout_countdown;
		}
	}

	// Debug code. 
/*	if (timeout_countdown == 0) {
		Serial.print("RRect Timeout ");
		Serial.println(rxCount, DEC);
	} */
	endSPITransaction();
}
#endif		

// Now lets see if we can writemultiple pixels
void BMC_ILI9488_t3::writeRect(int16_t x, int16_t y, int16_t w, int16_t h, const uint16_t *pcolors)
{
	if (x == CENTER) x = (_width - w) / 2;
	if (y == CENTER) y = (_height - h) / 2;
	x+=_originx;
	y+=_originy;
	uint16_t x_clip_left = 0;  // How many entries at start of colors to skip at start of row
	uint16_t x_clip_right = 0;    // how many color entries to skip at end of row for clipping
	// Rectangular clipping 

	// See if the whole thing out of bounds...
	if((x >= _displayclipx2) || (y >= _displayclipy2)) return;
	if (((x+w) <= _displayclipx1) || ((y+h) <= _displayclipy1)) return;

	// In these cases you can not do simple clipping, as we need to synchronize the colors array with the
	// We can clip the height as when we get to the last visible we don't have to go any farther. 
	// also maybe starting y as we will advance the color array. 
 	if(y < _displayclipy1) {
 		int dy = (_displayclipy1 - y);
 		h -= dy; 
 		pcolors += (dy*w); // Advance color array to 
 		y = _displayclipy1; 	
 	}

	if((y + h - 1) >= _displayclipy2) h = _displayclipy2 - y;

	// For X see how many items in color array to skip at start of row and likewise end of row 
	if(x < _displayclipx1) {
		x_clip_left = _displayclipx1-x; 
		w -= x_clip_left; 
		x = _displayclipx1; 	
	}
	if((x + w - 1) >= _displayclipx2) {
		x_clip_right = w;
		w = _displayclipx2  - x;
		x_clip_right -= w; 
	} 

	#ifdef ENABLE_ILI9488_FRAMEBUFFER
	if (_use_fbtft) {
		RAFB * pfbPixel_row = &_pfbtft[ y*_width + x];
		for (;h>0; h--) {
			RAFB * pfbPixel = pfbPixel_row;
			pcolors += x_clip_left;
			for (int i = 0 ;i < w; i++) {
				*pfbPixel++ = mapColorToPalletIndex(*pcolors++);
			}
			pfbPixel_row += _width;
			pcolors += x_clip_right;

		}
		return;	
	}
	#endif

   	beginSPITransaction();
	setAddr(x, y, x+w-1, y+h-1);
	writecommand_cont(ILI9488_RAMWR);
	for(y=h; y>0; y--) {
		pcolors += x_clip_left;
		for(x=w; x>1; x--) {
			write16BitColor(*pcolors++);
		}
		write16BitColor(*pcolors++,true);
		pcolors += x_clip_right;
	}
	endSPITransaction();
}

// writeRect8BPP - 	write 8 bit per pixel paletted bitmap
//					bitmap data in array at pixels, one byte per pixel
//					color palette data in array at palette
void BMC_ILI9488_t3::writeRect8BPP(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t *pixels, const uint16_t * palette )
{
	//Serial.printf("\nWR8: %d %d %d %d %x\n", x, y, w, h, (uint32_t)pixels);
	x+=_originx;
	y+=_originy;

	uint16_t x_clip_left = 0;  // How many entries at start of colors to skip at start of row
	uint16_t x_clip_right = 0;    // how many color entries to skip at end of row for clipping
	// Rectangular clipping 

	// See if the whole thing out of bounds...
	if((x >= _displayclipx2) || (y >= _displayclipy2)) return;
	if (((x+w) <= _displayclipx1) || ((y+h) <= _displayclipy1)) return;

	// In these cases you can not do simple clipping, as we need to synchronize the colors array with the
	// We can clip the height as when we get to the last visible we don't have to go any farther. 
	// also maybe starting y as we will advance the color array. 
 	if(y < _displayclipy1) {
 		int dy = (_displayclipy1 - y);
 		h -= dy; 
 		pixels += (dy*w); // Advance color array to 
 		y = _displayclipy1; 	
 	}

	if((y + h - 1) >= _displayclipy2) h = _displayclipy2 - y;

	// For X see how many items in color array to skip at start of row and likewise end of row 
	if(x < _displayclipx1) {
		x_clip_left = _displayclipx1-x; 
		w -= x_clip_left; 
		x = _displayclipx1; 	
	}
	if((x + w - 1) >= _displayclipx2) {
		x_clip_right = w;
		w = _displayclipx2  - x;
		x_clip_right -= w; 
	} 
	//Serial.printf("WR8C: %d %d %d %d %x- %d %d\n", x, y, w, h, (uint32_t)pixels, x_clip_right, x_clip_left);
	#ifdef ENABLE_ILI9488_FRAMEBUFFER
	if (_use_fbtft) {
		RAFB * pfbPixel_row = &_pfbtft[ y*_width + x];
		for (;h>0; h--) {
			pixels += x_clip_left;
			RAFB * pfbPixel = pfbPixel_row;
			for (int i = 0 ;i < w; i++) {
				*pfbPixel++ = mapColorToPalletIndex(palette[*pixels++]);
			}
			pixels += x_clip_right;
			pfbPixel_row += _width;
		}
		return;	
	}
	#endif

	beginSPITransaction();
	setAddr(x, y, x+w-1, y+h-1);
	writecommand_cont(ILI9488_RAMWR);
	for(y=h; y>0; y--) {
		pixels += x_clip_left;
		//Serial.printf("%x: ", (uint32_t)pixels);
		for(x=w; x>1; x--) {
			//Serial.print(*pixels, DEC);
			write16BitColor(palette[*pixels++]);
		}
		//Serial.println(*pixels, DEC);
		write16BitColor(palette[*pixels++], true);
		pixels += x_clip_right;
	}
	endSPITransaction();
}

// writeRect4BPP - 	write 4 bit per pixel paletted bitmap
//					bitmap data in array at pixels, 4 bits per pixel
//					color palette data in array at palette
//					width must be at least 2 pixels
void BMC_ILI9488_t3::writeRect4BPP(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t *pixels, const uint16_t * palette )
{
	#ifdef ENABLE_ILI9488_FRAMEBUFFER
	if (_use_fbtft) {
		writeRectNBPP(x, y, w, h, 4, pixels, palette); 
		return;
	}
	#endif
   	beginSPITransaction();
	setAddr(x, y, x+w-1, y+h-1);
	writecommand_cont(ILI9488_RAMWR);
	for(y=h; y>0; y--) {
		for(x=w; x>2; x-=2) {
			write16BitColor(palette[((*pixels)>>4)&0xF]);
			write16BitColor(palette[(*pixels++)&0xF]);
		}
		write16BitColor(palette[((*pixels)>>4)&0xF]);
		write16BitColor(palette[(*pixels++)&0xF], true);
	}
	endSPITransaction();
}

// writeRect2BPP - 	write 2 bit per pixel paletted bitmap
//					bitmap data in array at pixels, 4 bits per pixel
//					color palette data in array at palette
//					width must be at least 4 pixels
void BMC_ILI9488_t3::writeRect2BPP(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t *pixels, const uint16_t * palette )
{
	#ifdef ENABLE_ILI9488_FRAMEBUFFER
	if (_use_fbtft) {
		writeRectNBPP(x, y, w, h, 2, pixels, palette); 
		return;
	}
	#endif
   	beginSPITransaction();
	setAddr(x, y, x+w-1, y+h-1);
	writecommand_cont(ILI9488_RAMWR);
	for(y=h; y>0; y--) {
		for(x=w; x>4; x-=4) {
			//unrolled loop might be faster?
			write16BitColor(palette[((*pixels)>>6)&0x3]);
			write16BitColor(palette[((*pixels)>>4)&0x3]);
			write16BitColor(palette[((*pixels)>>2)&0x3]);
			write16BitColor(palette[(*pixels++)&0x3]);
		}
		write16BitColor(palette[((*pixels)>>6)&0x3]);
		write16BitColor(palette[((*pixels)>>4)&0x3]);
		write16BitColor(palette[((*pixels)>>2)&0x3]);
		write16BitColor(palette[(*pixels++)&0x3], true);
	}
	endSPITransaction();
}

// writeRect1BPP - 	write 1 bit per pixel paletted bitmap
//					bitmap data in array at pixels, 4 bits per pixel
//					color palette data in array at palette
//					width must be at least 8 pixels
void BMC_ILI9488_t3::writeRect1BPP(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t *pixels, const uint16_t * palette )
{
	#ifdef ENABLE_ILI9488_FRAMEBUFFER
	if (_use_fbtft) {
		writeRectNBPP(x, y, w, h, 1, pixels, palette); 
		return;
	}
	#endif
   	beginSPITransaction();
	setAddr(x, y, x+w-1, y+h-1);
	writecommand_cont(ILI9488_RAMWR);
	for(y=h; y>0; y--) {
		for(x=w; x>8; x-=8) {
			//unrolled loop might be faster?
			write16BitColor(palette[((*pixels)>>7)&0x1]);
			write16BitColor(palette[((*pixels)>>6)&0x1]);
			write16BitColor(palette[((*pixels)>>5)&0x1]);
			write16BitColor(palette[((*pixels)>>4)&0x1]);
			write16BitColor(palette[((*pixels)>>3)&0x1]);
			write16BitColor(palette[((*pixels)>>2)&0x1]);
			write16BitColor(palette[((*pixels)>>1)&0x1]);
			write16BitColor(palette[(*pixels++)&0x1]);
		}
		write16BitColor(palette[((*pixels)>>7)&0x1]);
		write16BitColor(palette[((*pixels)>>6)&0x1]);
		write16BitColor(palette[((*pixels)>>5)&0x1]);
		write16BitColor(palette[((*pixels)>>4)&0x1]);
		write16BitColor(palette[((*pixels)>>3)&0x1]);
		write16BitColor(palette[((*pixels)>>2)&0x1]);
		write16BitColor(palette[((*pixels)>>1)&0x1]);
		write16BitColor(palette[(*pixels++)&0x1], true);
	}
	endSPITransaction();
}

///============================================================================
// writeRectNBPP - 	write N(1, 2, 4, 8) bit per pixel paletted bitmap
//					bitmap data in array at pixels
//  Currently writeRect1BPP, writeRect2BPP, writeRect4BPP use this to do all of the work. 
void BMC_ILI9488_t3::writeRectNBPP(int16_t x, int16_t y, int16_t w, int16_t h,  uint8_t bits_per_pixel, 
		const uint8_t *pixels, const uint16_t * palette )
{
	//Serial.printf("\nWR8: %d %d %d %d %x\n", x, y, w, h, (uint32_t)pixels);
	x+=_originx;
	y+=_originy;
	uint8_t pixels_per_byte = 8/ bits_per_pixel;
	uint16_t count_of_bytes_per_row = (w + pixels_per_byte -1)/pixels_per_byte;		// Round up to handle non multiples
	uint8_t row_shift_init = 8 - bits_per_pixel;				// We shift down 6 bits by default 
	uint8_t pixel_bit_mask = (1 << bits_per_pixel) - 1; 		// get mask to use below
	// Rectangular clipping 

	// See if the whole thing out of bounds...
	if((x >= _displayclipx2) || (y >= _displayclipy2)) return;
	if (((x+w) <= _displayclipx1) || ((y+h) <= _displayclipy1)) return;

	// In these cases you can not do simple clipping, as we need to synchronize the colors array with the
	// We can clip the height as when we get to the last visible we don't have to go any farther. 
	// also maybe starting y as we will advance the color array. 
	// Again assume multiple of 8 for width
 	if(y < _displayclipy1) {
 		int dy = (_displayclipy1 - y);
 		h -= dy; 
 		pixels += dy * count_of_bytes_per_row;
 		y = _displayclipy1; 	
 	}

	if((y + h - 1) >= _displayclipy2) h = _displayclipy2 - y;

	// For X see how many items in color array to skip at start of row and likewise end of row 
	if(x < _displayclipx1) {
		uint16_t x_clip_left = _displayclipx1-x; 
		w -= x_clip_left; 
		x = _displayclipx1; 
		// Now lets update pixels to the rigth offset and mask
		uint8_t x_clip_left_bytes_incr = x_clip_left / pixels_per_byte;
		pixels += x_clip_left_bytes_incr;
		row_shift_init = 8 - (x_clip_left - (x_clip_left_bytes_incr * pixels_per_byte) + 1) * bits_per_pixel; 	
	}

	if((x + w - 1) >= _displayclipx2) {
		w = _displayclipx2  - x;
	} 

	const uint8_t * pixels_row_start = pixels;  // remember our starting position offset into row

	#ifdef ENABLE_ILI9488_FRAMEBUFFER
	if (_use_fbtft) {
		RAFB * pfbPixel_row = &_pfbtft[ y*_width + x];
		for (;h>0; h--) {
			RAFB * pfbPixel = pfbPixel_row;
			pixels = pixels_row_start;				// setup for this row
			uint8_t pixel_shift = row_shift_init;			// Setup mask

			for (int i = 0 ; i < w; i++) {
				*pfbPixel++ = mapColorToPalletIndex(palette[((*pixels)>>pixel_shift) & pixel_bit_mask]);
				if (!pixel_shift) {
					pixel_shift = 8 - bits_per_pixel;	//setup next mask
					pixels++;
				} else {
					pixel_shift -= bits_per_pixel;
				}
			}
			pfbPixel_row += _width;
			pixels_row_start += count_of_bytes_per_row;
		}
		return;	

	}
	#endif

	beginSPITransaction();
	setAddr(x, y, x+w-1, y+h-1);
	writecommand_cont(ILI9488_RAMWR);
	for (;h>0; h--) {
		pixels = pixels_row_start;				// setup for this row
		uint8_t pixel_shift = row_shift_init;			// Setup mask

		for (int i = 0 ;i < w; i++) {
			write16BitColor(palette[((*pixels)>>pixel_shift) & pixel_bit_mask]);
			if (!pixel_shift) {
				pixel_shift = 8 - bits_per_pixel;	//setup next mask
				pixels++;
			} else {
				pixel_shift -= bits_per_pixel;
			}
		}
		pixels_row_start += count_of_bytes_per_row;
	}
	writecommand_last(ILI9488_NOP);
	endSPITransaction();
}

static const uint8_t init_commands[] = {
	16, 0xE0, 0x00,0x03, 0x09, 0x08, 0x16, 0x0A, 0x3F, 0x78, 0x4C, 0x09, 0x0A, 0x08, 0x16, 0x1A, 0x0F,
	16, 0XE1, 0x00, 0x16, 0x19, 0x03, 0x0F, 0x05, 0x32, 0x45, 0x46, 0x04, 0x0E, 0x0D, 0x35, 0x37, 0x0F,
	3, 0XC0, 0x17, 0x15,
	2, 0xC1, 0x41,       //Power Control 2
	4, 0xC5, 0x00, 0x12, 0x80,        //Power Control 3
	2, 0x36, 0x48,      //Memory Access
	2, 0x3A, 0x66,      // Interface Pixel Format, 18bit
	2, 0xB0, 0x80,      // Interface Mode Control
	2, 0xB1, 0xA0,      //Frame rate, 60hz
	2, 0xB4, 0x02,      //Display Inversion Control
	1, 0XB6, 			//Display Function Control  RGB/MCU Interface Control
	2, 0x02, 0x02,		//MCU
	2, 0xE9, 0x00,      // Set Image Functio,Disable 24 bit data
	5, 0xF7, 0xA9, 0x51, 0x2C, 0x82,          // Adjust Control

	//4, 0xE8, 0x85, 0x00, 0x78,
	//6, 0xCB, 0x39, 0x2C, 0x00, 0x34, 0x02,
	//2, 0xF7, 0x20,
	//3, 0xEA, 0x00, 0x00,   //Power Control 1
	
	0
};


void BMC_ILI9488_t3::begin(uint32_t clock)
{
	//Serial.printf("BMC_ILI9488_t3::begin - start(%x %d %d %d)\n", (uint32_t)spi_port, _mosi, _miso, _sclk); Serial.flush();
	_clock = clock;	// remember the passed in clock...

    // verify SPI pins are valid;
	if ((_mosi != 255) || (_miso != 255) || (_sclk != 255)) {
    Serial.printf("BMC_ILI9488_t3::begin %x %d %d %d\n", (uint32_t)spi_port, _mosi, _miso, _sclk);  Serial.flush();
		if (!spi_port) {
			Serial.println("SPI Port not specified"); Serial.flush();
			if (SPI.pinIsMOSI(_mosi) && SPI.pinIsSCK(_sclk)) spi_port = &SPI;
			#if defined(__MKL26Z64__) || defined(__MK64FX512__) || defined(__MK66FX1M0__) || defined(__IMXRT1062__)
			else if (SPI1.pinIsMOSI(_mosi) && SPI1.pinIsSCK(_sclk)) spi_port = &SPI1;
			#if defined(__MK64FX512__) || defined(__MK66FX1M0__) || defined(__IMXRT1062__)
			else if (SPI2.pinIsMOSI(_mosi) && SPI2.pinIsSCK(_sclk)) spi_port = &SPI2;
			#endif
			#endif
			else spi_port = &SPI; 	// this will fail below but at least shows
		} 

		// Now validate the pins
		if (spi_port->pinIsMOSI(_mosi) && spi_port->pinIsSCK(_sclk)) {
			//spi_port= &SPI;
			if(!(spi_port->pinIsMISO(_miso))) {
				_miso = 0xff;	// set miso to 255 as flag it is bad
				Serial.println("BMC_ILI9488_t3n: Invalid MISO pin");
			}

		} else {
			if(!(spi_port->pinIsMOSI(_mosi)))  {
				Serial.print(" MOSI");
			}
			if (!spi_port->pinIsSCK(_sclk)) {
				Serial.print(" SCLK");
			}

			// Maybe allow us to limp with only MISO bad
			if(!(spi_port->pinIsMISO(_miso))) {
				Serial.print(" MISO");
				_miso = 0xff;	// set miso to 255 as flag it is bad
			}
			Serial.println();
			Serial.print("BMC_ILI9488_t3n: Error not valid SPI pins:");
			return; // not valid pins...
		}
		
		Serial.printf("MOSI:%d MISO:%d SCK:%d\n\r", _mosi, _miso, _sclk);			
        spi_port->setMOSI(_mosi);
        if (_miso != 0xff) spi_port->setMISO(_miso);
        spi_port->setSCK(_sclk);
    }

    // lets grab SPI data from the hardware object
	if (!spi_port) spi_port = &SPI;	// assume first one... 

#if defined(KINETISK)	
	uint32_t *pa = (uint32_t*)((void*)spi_port);
	_spi_hardware = (SPIClass::SPI_Hardware_t*)(void*)pa[1];
	_pkinetisk_spi = (KINETISK_SPI_t *)(void*)pa[0];
	_fifo_size = _spi_hardware->queue_size;		// remember the queue size
	spi_port->begin();
	if (spi_port->pinIsChipSelect(_cs, _dc)) {
		pcs_data = spi_port->setCS(_cs);
		pcs_command = pcs_data | spi_port->setCS(_dc);
	} else {
		// See if at least DC is on chipselect pin, if so try to limp along...
		if (spi_port->pinIsChipSelect(_dc)) {
			pcs_data = 0;
			pcs_command = pcs_data | spi_port->setCS(_dc);
			pinMode(_cs, OUTPUT);
			_csport    = portOutputRegister(digitalPinToPort(_cs));
			_cspinmask = digitalPinToBitMask(_cs);
		} else {
			pcs_data = 0;

		}
	}
	Serial.printf("SPIx: %x %x %x - %d %x %x\n", (uint32_t)spi_port, (uint32_t)_spi_hardware, (uint32_t)_pkinetisk_spi, _fifo_size, pcs_command, pcs_data); Serial.flush();
#elif defined(__IMXRT1062__)  // Teensy 4.x 
	uint32_t *pa = (uint32_t*)((void*)spi_port);
	_spi_hardware = (SPIClass::SPI_Hardware_t*)(void*)pa[1];
	_spi_num = (spi_port == &SPI)? 0 :  ((spi_port == &SPI1)? 1 : 2);
	_pimxrt_spi = (IMXRT_LPSPI_t *)(void*)pa[0];

	_pending_rx_count = 0;
	spi_port->begin();
	_csport = portOutputRegister(_cs);
	_cspinmask = digitalPinToBitMask(_cs);
	pinMode(_cs, OUTPUT);	
	DIRECT_WRITE_HIGH(_csport, _cspinmask);
	_spi_tcr_current = _pimxrt_spi->TCR; // get the current TCR value 

	// TODO:  Need to setup DC to actually work.
	if (spi_port->pinIsChipSelect(_dc)) {
	 	uint8_t dc_cs_index = spi_port->setCS(_dc);
	 	_dcport = 0;
	 	_dcpinmask = 0;
	 	dc_cs_index--;	// convert to 0 based
		_tcr_dc_assert = LPSPI_TCR_PCS(dc_cs_index);
    	_tcr_dc_not_assert = LPSPI_TCR_PCS(3);
	} else {
		//Serial.println("BMC_ILI9488_t3n: Error not DC is not valid hardware CS pin");
		_dcport = portOutputRegister(_dc);
		_dcpinmask = digitalPinToBitMask(_dc);
		pinMode(_dc, OUTPUT);	
		DIRECT_WRITE_HIGH(_dcport, _dcpinmask);
		_tcr_dc_assert = LPSPI_TCR_PCS(0);
    	_tcr_dc_not_assert = LPSPI_TCR_PCS(1);
	}
	maybeUpdateTCR(_tcr_dc_not_assert | LPSPI_TCR_FRAMESZ(7));
#elif defined(KINETISL)
	uint32_t *pa = (uint32_t*)((void*)spi_port);
	_spi_hardware = (SPIClass::SPI_Hardware_t*)(void*)pa[1];
	_pkinetisl_spi = (KINETISL_SPI_t *)(void*)pa[0];

	pcs_data = 0;
	pcs_command = 0;
	pinMode(_cs, OUTPUT);
	_csport    = portOutputRegister(digitalPinToPort(_cs));
	_cspinmask = digitalPinToBitMask(_cs);
	*_csport |= _cspinmask;
	pinMode(_dc, OUTPUT);
	_dcport    = portOutputRegister(digitalPinToPort(_dc));
	_dcpinmask = digitalPinToBitMask(_dc);
	*_dcport |= _dcpinmask;
	_dcpinAsserted = 0;

	spi_port->begin();
#endif
	// toggle RST low to reset
	if (_rst < 255) {
		pinMode(_rst, OUTPUT);
		digitalWrite(_rst, HIGH);
		delay(5);
		digitalWrite(_rst, LOW);
		delay(20);
		digitalWrite(_rst, HIGH);
		delay(150);
	}

	// REAL HACK TO GET SPI information!!!!
 	/*
	uint8_t x = readcommand8(ILI9488_RDMODE);
	Serial.print("\nDisplay Power Mode: 0x"); Serial.println(x, HEX);
	x = readcommand8(ILI9488_RDMADCTL);
	Serial.print("\nMADCTL Mode: 0x"); Serial.println(x, HEX);
	x = readcommand8(ILI9488_RDPIXFMT);
	Serial.print("\nPixel Format: 0x"); Serial.println(x, HEX);
	x = readcommand8(ILI9488_RDIMGFMT);
	Serial.print("\nImage Format: 0x"); Serial.println(x, HEX);
	x = readcommand8(ILI9488_RDSELFDIAG);
	Serial.print("\nSelf Diagnostic: 0x"); Serial.println(x, HEX);
	*/
	beginSPITransaction();
	const uint8_t *addr = init_commands;
	while (1) {
		uint8_t count = *addr++;
		if (count-- == 0) break;
		writecommand_cont(*addr++);
		while (count-- > 0) {
			writedata8_cont(*addr++);
		}
	}
	writecommand_last(ILI9488_SLPOUT);    // Exit Sleep
	endSPITransaction();

	delay(120); 		
	beginSPITransaction();
	writecommand_last(ILI9488_DISPON);    // Display on
	endSPITransaction();
	Serial.println("BMC_ILI9488_t3::begin Complete"); Serial.flush();
}





/*
This is the core graphics library for all our displays, providing a common
set of graphics primitives (points, lines, circles, etc.).  It needs to be
paired with a hardware-specific library for each display device we carry
(to handle the lower-level functions).

Adafruit invests time and resources providing this open source code, please
support Adafruit & open-source hardware by purchasing products from Adafruit!

Copyright (c) 2013 Adafruit Industries.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

// #include "display/BMC-glcdfont.c"
extern "C" const unsigned char BMCglcdfont[];

// Draw a circle outline
void BMC_ILI9488_t3::drawCircle(int16_t x0, int16_t y0, int16_t r,
    uint16_t color) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  drawPixel(x0  , y0+r, color);
  drawPixel(x0  , y0-r, color);
  drawPixel(x0+r, y0  , color);
  drawPixel(x0-r, y0  , color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    drawPixel(x0 + x, y0 + y, color);
    drawPixel(x0 - x, y0 + y, color);
    drawPixel(x0 + x, y0 - y, color);
    drawPixel(x0 - x, y0 - y, color);
    drawPixel(x0 + y, y0 + x, color);
    drawPixel(x0 - y, y0 + x, color);
    drawPixel(x0 + y, y0 - x, color);
    drawPixel(x0 - y, y0 - x, color);
  }
}

void BMC_ILI9488_t3::drawCircleHelper( int16_t x0, int16_t y0,
               int16_t r, uint8_t cornername, uint16_t color) {
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;
    if (cornername & 0x4) {
      drawPixel(x0 + x, y0 + y, color);
      drawPixel(x0 + y, y0 + x, color);
    }
    if (cornername & 0x2) {
      drawPixel(x0 + x, y0 - y, color);
      drawPixel(x0 + y, y0 - x, color);
    }
    if (cornername & 0x8) {
      drawPixel(x0 - y, y0 + x, color);
      drawPixel(x0 - x, y0 + y, color);
    }
    if (cornername & 0x1) {
      drawPixel(x0 - y, y0 - x, color);
      drawPixel(x0 - x, y0 - y, color);
    }
  }
}

void BMC_ILI9488_t3::fillCircle(int16_t x0, int16_t y0, int16_t r,
			      uint16_t color) {
  drawFastVLine(x0, y0-r, 2*r+1, color);
  fillCircleHelper(x0, y0, r, 3, 0, color);
}

// Used to do circles and roundrects
void BMC_ILI9488_t3::fillCircleHelper(int16_t x0, int16_t y0, int16_t r,
    uint8_t cornername, int16_t delta, uint16_t color) {

  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;

    if (cornername & 0x1) {
      drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
    }
    if (cornername & 0x2) {
      drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
    }
  }
}


// Bresenham's algorithm - thx wikpedia
void BMC_ILI9488_t3::drawLine(int16_t x0, int16_t y0,
	int16_t x1, int16_t y1, uint16_t color)
{
	if (y0 == y1) {
		if (x1 > x0) {
			drawFastHLine(x0, y0, x1 - x0 + 1, color);
		} else if (x1 < x0) {
			drawFastHLine(x1, y0, x0 - x1 + 1, color);
		} else {
			drawPixel(x0, y0, color);
		}
		return;
	} else if (x0 == x1) {
		if (y1 > y0) {
			drawFastVLine(x0, y0, y1 - y0 + 1, color);
		} else {
			drawFastVLine(x0, y1, y0 - y1 + 1, color);
		}
		return;
	}

	bool steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		ILI9488_swap(x0, y0);
		ILI9488_swap(x1, y1);
	}
	if (x0 > x1) {
		ILI9488_swap(x0, x1);
		ILI9488_swap(y0, y1);
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1) {
		ystep = 1;
	} else {
		ystep = -1;
	}

	#ifdef ENABLE_ILI9488_FRAMEBUFFER
  	if (!_use_fbtft) beginSPITransaction();
  	#else
	beginSPITransaction();
  	#endif
	int16_t xbegin = x0;
	if (steep) {
		for (; x0<=x1; x0++) {
			err -= dy;
			if (err < 0) {
				int16_t len = x0 - xbegin;
				if (len) {
					VLine(y0, xbegin, len + 1, color);
				} else {
					Pixel(y0, x0, color);
				}
				xbegin = x0 + 1;
				y0 += ystep;
				err += dx;
			}
		}
		if (x0 > xbegin + 1) {
			VLine(y0, xbegin, x0 - xbegin, color);
		}

	} else {
		for (; x0<=x1; x0++) {
			err -= dy;
			if (err < 0) {
				int16_t len = x0 - xbegin;
				if (len) {
					HLine(xbegin, y0, len + 1, color);
				} else {
					Pixel(x0, y0, color);
				}
				xbegin = x0 + 1;
				y0 += ystep;
				err += dx;
			}
		}
		if (x0 > xbegin + 1) {
			HLine(xbegin, y0, x0 - xbegin, color);
		}
	}
	#ifdef ENABLE_ILI9488_FRAMEBUFFER
  	if (!_use_fbtft)  {
		writecommand_last(ILI9488_NOP);
		endSPITransaction();
  	}
  	#else
	writecommand_last(ILI9488_NOP);
	endSPITransaction();
  	#endif
}

// Draw a rectangle
void BMC_ILI9488_t3::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
	#ifdef ENABLE_ILI9488_FRAMEBUFFER
	if (_use_fbtft) {
		drawFastHLine(x, y, w, color);
		drawFastHLine(x, y+h-1, w, color);
		drawFastVLine(x, y, h, color);
		drawFastVLine(x+w-1, y, h, color);
	} else 
	#endif
	{
		beginSPITransaction();
		HLine(x, y, w, color);
		HLine(x, y+h-1, w, color);
		VLine(x, y, h, color);
		VLine(x+w-1, y, h, color);
		writecommand_last(ILI9488_NOP);
		endSPITransaction();
	}
}

// Draw a rounded rectangle
void BMC_ILI9488_t3::drawRoundRect(int16_t x, int16_t y, int16_t w,
  int16_t h, int16_t r, uint16_t color) {
  // smarter version
  drawFastHLine(x+r  , y    , w-2*r, color); // Top
  drawFastHLine(x+r  , y+h-1, w-2*r, color); // Bottom
  drawFastVLine(x    , y+r  , h-2*r, color); // Left
  drawFastVLine(x+w-1, y+r  , h-2*r, color); // Right
  // draw four corners
  drawCircleHelper(x+r    , y+r    , r, 1, color);
  drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
  drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
  drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}

// Fill a rounded rectangle
void BMC_ILI9488_t3::fillRoundRect(int16_t x, int16_t y, int16_t w,
				 int16_t h, int16_t r, uint16_t color) {
  // smarter version
  fillRect(x+r, y, w-2*r, h, color);

  // draw four corners
  fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
  fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}

// Draw a triangle
void BMC_ILI9488_t3::drawTriangle(int16_t x0, int16_t y0,
				int16_t x1, int16_t y1,
				int16_t x2, int16_t y2, uint16_t color) {
  drawLine(x0, y0, x1, y1, color);
  drawLine(x1, y1, x2, y2, color);
  drawLine(x2, y2, x0, y0, color);
}

// Fill a triangle
void BMC_ILI9488_t3::fillTriangle ( int16_t x0, int16_t y0,
				  int16_t x1, int16_t y1,
				  int16_t x2, int16_t y2, uint16_t color) {

  int16_t a, b, y, last;

  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    ILI9488_swap(y0, y1); ILI9488_swap(x0, x1);
  }
  if (y1 > y2) {
    ILI9488_swap(y2, y1); ILI9488_swap(x2, x1);
  }
  if (y0 > y1) {
    ILI9488_swap(y0, y1); ILI9488_swap(x0, x1);
  }

  if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if(x1 < a)      a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
    drawFastHLine(a, y0, b-a+1, color);
    return;
  }

  int32_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1,
    sa   = 0,
    sb   = 0;

  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
  if(y1 == y2) last = y1;   // Include y1 scanline
  else         last = y1-1; // Skip it

  for(y=y0; y<=last; y++) {
    a   = x0 + sa / dy01;
    b   = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
    a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) ILI9488_swap(a,b);
    drawFastHLine(a, y, b-a+1, color);
  }

  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  for(; y<=y2; y++) {
    a   = x1 + sa / dy12;
    b   = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    /* longhand:
    a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) ILI9488_swap(a,b);
    drawFastHLine(a, y, b-a+1, color);
  }
}

void BMC_ILI9488_t3::drawBitmap(int16_t x, int16_t y,
			      const uint8_t *bitmap, int16_t w, int16_t h,
			      uint16_t color) {

  int16_t i, j, byteWidth = (w + 7) / 8;

  for(j=0; j<h; j++) {
    for(i=0; i<w; i++ ) {
      if(pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7))) {
	drawPixel(x+i, y+j, color);
      }
    }
  }
}

// overwrite functions from class Print:

size_t BMC_ILI9488_t3::write(uint8_t c) {
	return write(&c, 1);
}

size_t BMC_ILI9488_t3::write(const uint8_t *buffer, size_t size)
{
	// Lets try to handle some of the special font centering code that was done for default fonts.
	if (_center_x_text || _center_y_text ) {
		int16_t x, y;
	  	uint16_t strngWidth, strngHeight;
	  	getTextBounds(buffer, size, 0, 0, &x, &y, &strngWidth, &strngHeight);
	  	//Serial.printf("_fontwrite bounds: %d %d %u %u\n", x, y, strngWidth, strngHeight);
	  	// Note we may want to play with the x ane y returned if they offset some
		if (_center_x_text && strngWidth > 0){//Avoid operations for strngWidth = 0
      		cursor_x -= (x + strngWidth / 2);
		}
		if (_center_y_text && strngHeight > 0){//Avoid operations for strngWidth = 0
		    cursor_y -= (y + strngHeight / 2);
		}
		_center_x_text = false;
		_center_y_text = false;
	}
	
	size_t cb = size;
	while (cb) {
		uint8_t c = *buffer++;
		cb--;	
	
		if (font) {
			if (c == '\n') {
				cursor_y += font->line_space;
				if(scrollEnable && isWritingScrollArea){
					cursor_x  = scroll_x;
				}else{
					cursor_x  = 0;
				}
			} else {
				drawFontChar(c);
			}
		} else if (gfxFont)  {
			if (c == '\n') {
				cursor_y += (int16_t)textsize_y * gfxFont->yAdvance;
				if(scrollEnable && isWritingScrollArea){
					cursor_x  = scroll_x;
				}else{
					cursor_x  = 0;
				}
			} else {
				drawGFXFontChar(c);
			}
		} else {
			if (c == '\n') {
				cursor_y += textsize_y*8;
				if(scrollEnable && isWritingScrollArea){
					cursor_x  = scroll_x;
				}else{
					cursor_x  = 0;
				}
			} else if (c == '\r') {
				// skip em
			} else {
				if(scrollEnable && isWritingScrollArea && (cursor_y > (scroll_y+scroll_height - textsize_y*8))){
					scrollTextArea(textsize_y*8);
					cursor_y -= textsize_y*8;
					cursor_x = scroll_x;
				}
				drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize_x, textsize_y);
				cursor_x += textsize_x*6;
				if(wrap && scrollEnable && isWritingScrollArea && (cursor_x > (scroll_x+scroll_width - textsize_x*6))){
					cursor_y += textsize_y*8;
					cursor_x = scroll_x;
				}
				else if (wrap && (cursor_x > (_width - textsize_x*6))) {
					cursor_y += textsize_y*6;
					cursor_x = 0;
				}
			}
		}
	}
	return 1;
}

// Draw a character
void BMC_ILI9488_t3::drawChar(int16_t x, int16_t y, unsigned char c,
			    uint16_t fgcolor, uint16_t bgcolor, uint8_t size_x, uint8_t size_y)
{
	if((x >= _width)            || // Clip right
	   (y >= _height)           || // Clip bottom
	   ((x + 6 * size_x - 1) < 0) || // Clip left  TODO: is this correct?
	   ((y + 8 * size_y - 1) < 0))   // Clip top   TODO: is this correct?
		return;

//	Serial.printf("drawchar %d %d %c %x %x %d %d\n", x, y, c, fgcolor, bgcolor, size_x, size_y);
	if (fgcolor == bgcolor) {
		// This transparent approach is only about 20% faster
		if ((size_x == 1) && (size_y == 1)) {
			uint8_t mask = 0x01;
			int16_t xoff, yoff;
			for (yoff=0; yoff < 8; yoff++) {
				uint8_t line = 0;
				for (xoff=0; xoff < 5; xoff++) {
					if (BMCglcdfont[c * 5 + xoff] & mask) line |= 1;
					line <<= 1;
				}
				line >>= 1;
				xoff = 0;
				while (line) {
					if (line == 0x1F) {
						drawFastHLine(x + xoff, y + yoff, 5, fgcolor);
						break;
					} else if (line == 0x1E) {
						drawFastHLine(x + xoff, y + yoff, 4, fgcolor);
						break;
					} else if ((line & 0x1C) == 0x1C) {
						drawFastHLine(x + xoff, y + yoff, 3, fgcolor);
						line <<= 4;
						xoff += 4;
					} else if ((line & 0x18) == 0x18) {
						drawFastHLine(x + xoff, y + yoff, 2, fgcolor);
						line <<= 3;
						xoff += 3;
					} else if ((line & 0x10) == 0x10) {
						drawPixel(x + xoff, y + yoff, fgcolor);
						line <<= 2;
						xoff += 2;
					} else {
						line <<= 1;
						xoff += 1;
					}
				}
				mask = mask << 1;
			}
		} else {
			uint8_t mask = 0x01;
			int16_t xoff, yoff;
			for (yoff=0; yoff < 8; yoff++) {
				uint8_t line = 0;
				for (xoff=0; xoff < 5; xoff++) {
					if (BMCglcdfont[c * 5 + xoff] & mask) line |= 1;
					line <<= 1;
				}
				line >>= 1;
				xoff = 0;
				while (line) {
					if (line == 0x1F) {
						fillRect(x + xoff * size_x, y + yoff * size_y,
							5 * size_x, size_y, fgcolor);
						break;
					} else if (line == 0x1E) {
						fillRect(x + xoff * size_x, y + yoff * size_y,
							4 * size_x, size_y, fgcolor);
						break;
					} else if ((line & 0x1C) == 0x1C) {
						fillRect(x + xoff * size_x, y + yoff * size_y,
							3 * size_x, size_y, fgcolor);
						line <<= 4;
						xoff += 4;
					} else if ((line & 0x18) == 0x18) {
						fillRect(x + xoff * size_x, y + yoff * size_y,
							2 * size_x, size_y, fgcolor);
						line <<= 3;
						xoff += 3;
					} else if ((line & 0x10) == 0x10) {
						fillRect(x + xoff * size_x, y + yoff * size_y,
							size_x, size_y, fgcolor);
						line <<= 2;
						xoff += 2;
					} else {
						line <<= 1;
						xoff += 1;
					}
				}
				mask = mask << 1;
			}
		}
	} else {
		// This solid background approach is about 5 time faster
		uint8_t xc, yc;
		uint8_t xr, yr;
		uint8_t mask = 0x01;
		uint16_t color;

		// We need to offset by the origin.
		x+=_originx;
		y+=_originy;
		int16_t x_char_start = x;  // remember our X where we start outputting...

		if((x >= _displayclipx2)            || // Clip right
			 (y >= _displayclipy2)           || // Clip bottom
			 ((x + 6 * size_x - 1) < _displayclipx1) || // Clip left  TODO: this is not correct
			 ((y + 8 * size_y - 1) < _displayclipy1))   // Clip top   TODO: this is not correct
			return;


		#ifdef ENABLE_ILI9488_FRAMEBUFFER
		if (_use_fbtft) {
			RAFB * pfbPixel_row = &_pfbtft[ y*_width + x];
			// lets try to output the values directly...
			RAFB * pfbPixel;
			RAFB bgcolor_index = mapColorToPalletIndex(bgcolor);
			RAFB fgcolor_index = mapColorToPalletIndex(fgcolor);
			RAFB color_idx;
			for (yc=0; (yc < 8) && (y < _displayclipy2); yc++) {
				for (yr=0; (yr < size_y) && (y < _displayclipy2); yr++) {
					x = x_char_start; 		// get our first x position...
					if (y >= _displayclipy1) {
						pfbPixel = pfbPixel_row;
						for (xc=0; xc < 5; xc++) {
							if (BMCglcdfont[c * 5 + xc] & mask) {
								color_idx = fgcolor_index;
							} else {
								color_idx = bgcolor_index;
							}
							for (xr=0; xr < size_x; xr++) {
								if ((x >= _displayclipx1) && (x < _displayclipx2)) {
								*pfbPixel = color_idx;
								}
								pfbPixel++;
								x++;
							}
						}
						for (xr=0; xr < size_x; xr++) {
							if ((x >= _displayclipx1) && (x < _displayclipx2)) {
								*pfbPixel = bgcolor_index;
							}
							pfbPixel++;
							x++;
						}
					}
					pfbPixel_row += _width; // setup pointer to 
					y++;
				}
				mask = mask << 1;
			}

		} else 
		#endif
		{
			// need to build actual pixel rectangle we will output into.
			int16_t y_char_top = y;	// remember the y
			int16_t w =  6 * size_x;
			int16_t h = 8 * size_y;

			if(x < _displayclipx1) {	w -= (_displayclipx1-x); x = _displayclipx1; 	}
			if((x + w - 1) >= _displayclipx2)  w = _displayclipx2  - x;
			if(y < _displayclipy1) {	h -= (_displayclipy1 - y); y = _displayclipy1; 	}
			if((y + h - 1) >= _displayclipy2) h = _displayclipy2 - y;

			beginSPITransaction();
			setAddr(x, y, x + w -1, y + h - 1);

			y = y_char_top;	// restore the actual y.
			writecommand_cont(ILI9488_RAMWR);
			for (yc=0; (yc < 8) && (y < _displayclipy2); yc++) {
				for (yr=0; (yr < size_y) && (y < _displayclipy2); yr++) {
					x = x_char_start; 		// get our first x position...
					if (y >= _displayclipy1) {
						for (xc=0; xc < 5; xc++) {
							if (BMCglcdfont[c * 5 + xc] & mask) {
								color = fgcolor;
							} else {
								color = bgcolor;
							}
							for (xr=0; xr < size_x; xr++) {
								if ((x >= _displayclipx1) && (x < _displayclipx2)) {
									write16BitColor(color);
								}
								x++;
							}
						}
						for (xr=0; xr < size_x; xr++) {
							if ((x >= _displayclipx1) && (x < _displayclipx2)) {
								write16BitColor(bgcolor);
							}
							x++;
						}
					}
					y++;
				}
				mask = mask << 1;
			}
			writecommand_last(ILI9488_NOP);
			endSPITransaction();
		}
	}
}
void BMC_ILI9488_t3::setFont(const BMC_ILI9341_t3_font_t &f) {
	_gfx_last_char_x_write = 0;	// Don't use cached data here
	font = &f;
	if (gfxFont) {
        cursor_y -= 6;
		gfxFont = NULL;
	}
	fontbpp = 1;
	// Calculate additional metrics for Anti-Aliased font support (BDF extn v2.3)
	if (font && font->version==23){
		fontbpp = (font->reserved & 0b000011)+1;
		fontbppindex = (fontbpp >> 2)+1;
		fontbppmask = (1 << (fontbppindex+1))-1;
		fontppb = 8/fontbpp;
		fontalphamx = 31/((1<<fontbpp)-1);
		// Ensure text and bg color are different. Note: use setTextColor to set actual bg color
		if (textcolor == textbgcolor) textbgcolor = (textcolor==0x0000)?0xFFFF:0x0000;
	}
}

// Maybe support GFX Fonts as well?
void BMC_ILI9488_t3::setFont(const GFXfont *f) {
	font = NULL;	// turn off the other font... 
	_gfx_last_char_x_write = 0;	// Don't use cached data here
	if (f == gfxFont) return;	// same font or lack of so can bail.

    if(f) {            // Font struct pointer passed in?
        if(!gfxFont) { // And no current font struct?
            // Switching from classic to new font behavior.
            // Move cursor pos down 6 pixels so it's on baseline.
            cursor_y += 6;
        }

        // Test wondering high and low of Ys here... 
        int8_t miny_offset = 0;
#if 1
        for (uint8_t i=0; i <= (f->last - f->first); i++) {
        	if (f->glyph[i].yOffset < miny_offset) {
        		miny_offset = f->glyph[i].yOffset;
        	}
        }
#else        
        int max_delta = 0;
        uint8_t index_min = 0;
        uint8_t index_max = 0;

        int8_t minx_offset = 127;
        int8_t maxx_overlap = 0;
        uint8_t indexx_min = 0;
        uint8_t indexx_max = 0;
        for (uint8_t i=0; i <= (f->last - f->first); i++) {
        	if (f->glyph[i].yOffset < miny_offset) {
        		miny_offset = f->glyph[i].yOffset;
        		index_min = i;
        	}

        	if (f->glyph[i].xOffset < minx_offset) {
        		minx_offset = f->glyph[i].xOffset;
        		indexx_min = i;
        	}
        	if ( (f->glyph[i].yOffset + f->glyph[i].height) > max_delta) {
        		max_delta = (f->glyph[i].yOffset + f->glyph[i].height);
        		index_max = i;
        	}
        	int8_t x_overlap = f->glyph[i].xOffset + f->glyph[i].width - f->glyph[i].xAdvance;
        	if (x_overlap > maxx_overlap) {
        		maxx_overlap = x_overlap;
        		indexx_max = i;
        	}
        }
        Serial.printf("Set GFX Font(%x): Y: %d %d(%c) %d(%c) X: %d(%c) %d(%c)\n", (uint32_t)f, f->yAdvance, 
        	miny_offset, index_min + f->first, max_delta, index_max + f->first,
        	minx_offset, indexx_min + f->first, maxx_overlap, indexx_max + f->first);
#endif
        _gfxFont_min_yOffset = miny_offset;	// Probably only thing we need... May cache? 

    } else if(gfxFont) { // NULL passed.  Current font struct defined?
        // Switching from new to classic font behavior.
        // Move cursor pos up 6 pixels so it's at top-left of char.
        cursor_y -= 6;
    }
    gfxFont = f;
}

uint32_t BMC_ILI9488_t3::fetchpixel(const uint8_t *p, uint32_t index, uint32_t x)
{
	// The byte
	uint8_t b = p[index >> 3];
	// Shift to LSB position and mask to get value
	uint8_t s = ((fontppb-(x % fontppb)-1)*fontbpp);
	// Mask and return
	return (b >> s) & fontbppmask;
}


static uint32_t fetchbit(const uint8_t *p, uint32_t index)
{
	if (p[index >> 3] & (1 << (7 - (index & 7)))) return 1;
	return 0;
}

static uint32_t fetchbits_unsigned(const uint8_t *p, uint32_t index, uint32_t required)
{
	uint32_t val = 0;
	do {
		uint8_t b = p[index >> 3];
		uint32_t avail = 8 - (index & 7);
		if (avail <= required) {
			val <<= avail;
			val |= b & ((1 << avail) - 1);
			index += avail;
			required -= avail;
		} else {
			b >>= avail - required;
			val <<= required;
			val |= b & ((1 << required) - 1);
			break;
		}
	} while (required);
	return val;
}

static uint32_t fetchbits_signed(const uint8_t *p, uint32_t index, uint32_t required)
{
	uint32_t val = fetchbits_unsigned(p, index, required);
	if (val & (1 << (required - 1))) {
		return (int32_t)val - (1 << required);
	}
	return (int32_t)val;
}


void BMC_ILI9488_t3::drawFontChar(unsigned int c)
{
	uint32_t bitoffset;
	const uint8_t *data;

	//Serial.printf("drawFontChar(%c) %d\n", c, c);

	if (c >= font->index1_first && c <= font->index1_last) {
		bitoffset = c - font->index1_first;
		bitoffset *= font->bits_index;
	} else if (c >= font->index2_first && c <= font->index2_last) {
		bitoffset = c - font->index2_first + font->index1_last - font->index1_first + 1;
		bitoffset *= font->bits_index;
	} else if (font->unicode) {
		return; // TODO: implement sparse unicode
	} else {
		return;
	}
	//Serial.printf("  index =  %d\n", fetchbits_unsigned(font->index, bitoffset, font->bits_index));
	data = font->data + fetchbits_unsigned(font->index, bitoffset, font->bits_index);

	uint32_t encoding = fetchbits_unsigned(data, 0, 3);
	if (encoding != 0) return;
	uint32_t width = fetchbits_unsigned(data, 3, font->bits_width);
	bitoffset = font->bits_width + 3;
	uint32_t height = fetchbits_unsigned(data, bitoffset, font->bits_height);
	bitoffset += font->bits_height;
	//Serial.printf("  size =   %d,%d\n", width, height);
	//Serial.printf("  line space = %d\n", font->line_space);

	int32_t xoffset = fetchbits_signed(data, bitoffset, font->bits_xoffset);
	bitoffset += font->bits_xoffset;
	int32_t yoffset = fetchbits_signed(data, bitoffset, font->bits_yoffset);
	bitoffset += font->bits_yoffset;
	//Serial.printf("  offset = %d,%d\n", xoffset, yoffset);

	uint32_t delta = fetchbits_unsigned(data, bitoffset, font->bits_delta);
	bitoffset += font->bits_delta;
	//Serial.printf("  delta =  %d\n", delta);

	//Serial.printf("  cursor = %d,%d\n", cursor_x, cursor_y);

	 //horizontally, we draw every pixel, or none at all
	if (cursor_x < 0) cursor_x = 0;
	int32_t origin_x = cursor_x + xoffset;
	if (origin_x < 0) {
		cursor_x -= xoffset;
		origin_x = 0;
	}
	if (origin_x + (int)width > _width) {
		if (!wrap) return;
		origin_x = 0;
		if (xoffset >= 0) {
			cursor_x = 0;
		} else {
			cursor_x = -xoffset;
		}
		cursor_y += font->line_space;
	}
	if(wrap && scrollEnable && isWritingScrollArea && ((origin_x + (int)width) > (scroll_x+scroll_width))){
    	origin_x = 0;
		if (xoffset >= 0) {
			cursor_x = scroll_x;
		} else {
			cursor_x = -xoffset;
		}
		cursor_y += font->line_space;
    }
	
	if(scrollEnable && isWritingScrollArea && (cursor_y > (scroll_y+scroll_height - font->cap_height))){
		scrollTextArea(font->line_space);
		cursor_y -= font->line_space;
		cursor_x = scroll_x;
	} 
	if (cursor_y >= _height) return;

	// vertically, the top and/or bottom can be clipped
	int32_t origin_y = cursor_y + font->cap_height - height - yoffset;
	//Serial.printf("  origin = %d,%d\n", origin_x, origin_y);

	// TODO: compute top skip and number of lines
	int32_t linecount = height;
	//uint32_t loopcount = 0;
	int32_t y = origin_y;
	bool opaque = (textbgcolor != textcolor);

	// Going to try a fast Opaque method which works similar to drawChar, which is near the speed of writerect
	if (!opaque) {
		
		// Anti-alias support
		if (fontbpp>1){
			// This branch should, in most cases, never happen. This is because if an
			// anti-aliased font is being used, textcolor and textbgcolor should always
			// be different. Even though an anti-alised font is being used, pixels in this
			// case will all be solid because pixels are rendered on same colour as themselves!
			// This won't look very good.
			bitoffset = ((bitoffset + 7) & (-8)); // byte-boundary
			uint32_t xp = 0;
			uint8_t halfalpha = 1<<(fontbpp-1);
			while (linecount) {
				uint32_t x = 0;
				while(x<width) {
					// One pixel at a time, either on (if alpha > 0.5) or off
					if (fetchpixel(data, bitoffset, xp)>=halfalpha){
						Pixel(origin_x + x,y,textcolor);
					}
					bitoffset += fontbpp;
					x++;
					xp++;
				}
				y++;
				linecount--;
			}

		}
		// Soild pixels
		else{	
		
			while (linecount > 0) {
				//Serial.printf("    linecount = %d\n", linecount);
				uint32_t n = 1;
				if (fetchbit(data, bitoffset++) != 0) {
					n = fetchbits_unsigned(data, bitoffset, 3) + 2;
					bitoffset += 3;
				}
				uint32_t x = 0;
				do {
					int32_t xsize = width - x;
					if (xsize > 32) xsize = 32;
					uint32_t bits = fetchbits_unsigned(data, bitoffset, xsize);
					//Serial.printf("    multi line %d %d %x\n", n, x, bits);
					drawFontBits(opaque, bits, xsize, origin_x + x, y, n);
					bitoffset += xsize;
					x += xsize;
				} while (x < width);


				y += n;
				linecount -= n;
				//if (++loopcount > 100) {
					//Serial.println("     abort draw loop");
					//break;
				//}
			}
		} // 1bpp
	}
	
	// opaque
	else {
		// Now opaque mode... 
		// Now write out background color for the number of rows above the above the character
		// figure out bounding rectangle... 
		// In this mode we need to update to use the offset and bounding rectangles as we are doing it it direct.
		// also update the Origin 
		int cursor_x_origin = cursor_x + _originx;
		int cursor_y_origin = cursor_y + _originy;
		origin_x += _originx;
		origin_y += _originy;

		int start_x = (origin_x < cursor_x_origin) ? origin_x : cursor_x_origin; 	
		if (start_x < 0) start_x = 0;
		
		int start_y = (origin_y < cursor_y_origin) ? origin_y : cursor_y_origin; 
		if (start_y < 0) start_y = 0;
		int end_x = cursor_x_origin + delta; 
		if ((origin_x + (int)width) > end_x)
			end_x = origin_x + (int)width;
		if (end_x >= _displayclipx2)  end_x = _displayclipx2;	
		int end_y = cursor_y_origin + font->line_space; 
		if ((origin_y + (int)height) > end_y)
			end_y = origin_y + (int)height;
		if (end_y >= _displayclipy2) end_y = _displayclipy2;	
		end_x--;	// setup to last one we draw
		end_y--;
		int start_x_min = (start_x >= _displayclipx1) ? start_x : _displayclipx1;
		int start_y_min = (start_y >= _displayclipy1) ? start_y : _displayclipy1;

		// See if anything is in the display area.
		if((end_x < _displayclipx1) ||(start_x >= _displayclipx2) || (end_y < _displayclipy1) || (start_y >= _displayclipy2)) {
			cursor_x += delta;	// could use goto or another indent level...
		 	return;
		}
/*
		Serial.printf("drawFontChar(%c) %d\n", c, c);
		Serial.printf("  size =   %d,%d\n", width, height);
		Serial.printf("  line space = %d\n", font->line_space);
		Serial.printf("  offset = %d,%d\n", xoffset, yoffset);
		Serial.printf("  delta =  %d\n", delta);
		Serial.printf("  cursor = %d,%d\n", cursor_x, cursor_y);
		Serial.printf("  origin = %d,%d\n", origin_x, origin_y);

		Serial.printf("  Bounding: (%d, %d)-(%d, %d)\n", start_x, start_y, end_x, end_y);
		Serial.printf("  mins (%d %d),\n", start_x_min, start_y_min);
*/
		#ifdef ENABLE_ILI9488_FRAMEBUFFER
		if (_use_fbtft) {
			RAFB * pfbPixel_row = &_pfbtft[ start_y*_width + start_x];
			RAFB * pfbPixel;
			RAFB textbgcolor_index = mapColorToPalletIndex(textbgcolor);
			RAFB textcolor_index = mapColorToPalletIndex(textcolor);
			int screen_y = start_y;
			int screen_x;

			// Clear above character
			while (screen_y < origin_y) {
				pfbPixel = pfbPixel_row;
				// only output if this line is within the clipping region.
				if ((screen_y >= _displayclipy1) && (screen_y < _displayclipy2)) {
					for (screen_x = start_x; screen_x <= end_x; screen_x++) {
						if (screen_x >= _displayclipx1) {
							*pfbPixel = textbgcolor_index;
						}
						pfbPixel++;
					}
				}
				screen_y++;
				pfbPixel_row += _width;
			}
			
			// Anti-aliased font
			if (fontbpp>1){
				screen_y = origin_y;
				bitoffset = ((bitoffset + 7) & (-8)); // byte-boundary
				uint32_t xp = 0;
				int glyphend_x = origin_x+width;
				while (linecount) {
					pfbPixel = pfbPixel_row;
					screen_x = start_x;
					while(screen_x<=end_x) {
						// XXX: I'm sure clipping could be done way more efficiently than just chekcing every single pixel, but let's just get this going
						if ((screen_x >= _displayclipx1) && (screen_x < _displayclipx2) && (screen_y >= _displayclipy1) && (screen_y < _displayclipy2)) {
							// Clear before or after pixel
							if ((screen_x<origin_x) || (screen_x>=glyphend_x)){
								*pfbPixel = textbgcolor;
							}
							// Draw alpha-blended character
							else{
								uint8_t alpha = fetchpixel(data, bitoffset, xp);
								*pfbPixel = mapColorToPalletIndex(alphaBlendRGB565Premultiplied( textcolorPrexpanded, textbgcolorPrexpanded, (uint8_t)(alpha * fontalphamx)) );
								bitoffset += fontbpp;
								xp++;
							}
						} // clip
						screen_x++;
						pfbPixel++;
					}
					pfbPixel_row += _width;
					screen_y++;
					linecount--;
				}

			} // anti-aliased

			// 1bpp solid font
			else{			

				// Now lets process each of the data lines. 
				screen_y = origin_y;

				while (linecount > 0) {
					//Serial.printf("    linecount = %d\n", linecount);
					uint32_t b = fetchbit(data, bitoffset++);
					uint32_t n;
					if (b == 0) {
						//Serial.println("Single");
						n = 1;
					} else {
						//Serial.println("Multi");
						n = fetchbits_unsigned(data, bitoffset, 3) + 2;
						bitoffset += 3;
					}
					uint32_t bitoffset_row_start = bitoffset;
					while (n--) {
						pfbPixel = pfbPixel_row;
						if ((screen_y >= _displayclipy1) && (screen_y < _displayclipy2)) {
							bitoffset = bitoffset_row_start;	// we will work through these bits maybe multiple times

							for (screen_x = start_x; screen_x < origin_x; screen_x++) {
								if (screen_x >= _displayclipx1) {
									*pfbPixel = textbgcolor_index;
								} // make sure not clipped
								pfbPixel++;
							}
						}

						screen_x = origin_x;
						uint32_t x = 0;
						do {
							uint32_t xsize = width - x;
							if (xsize > 32) xsize = 32;
							uint32_t bits = fetchbits_unsigned(data, bitoffset, xsize);
							uint32_t bit_mask = 1 << (xsize-1);
							//Serial.printf(" %d %d %x %x\n", x, xsize, bits, bit_mask);
							if ((screen_y >= _displayclipy1) && (screen_y < _displayclipy2)) {
								while (bit_mask && (screen_x <= end_x)) {
									if ((screen_x >= _displayclipx1) && (screen_x < _displayclipx2)) {
										*pfbPixel = (bits & bit_mask) ? textcolor_index : textbgcolor_index;
									}
									pfbPixel++;	
									bit_mask = bit_mask >> 1;
									screen_x++;	// increment our pixel position. 
								}
							}
								bitoffset += xsize;
							x += xsize;
						} while (x < width);
						if ((screen_y >= _displayclipy1) && (screen_y < _displayclipy2)) {
							// output bg color and right hand side
							while (screen_x++ <= end_x) {
								*pfbPixel++ = textbgcolor_index;
							}
						}			 
						screen_y++;
						pfbPixel_row += _width;
						linecount--;
					}
				}
			} // 1bpp
			
			// clear below character
	 		while (screen_y++ <= end_y) {
				if ((screen_y >= _displayclipy1) && (screen_y < _displayclipy2)) {
					pfbPixel = pfbPixel_row;
					for (screen_x = start_x; screen_x <= end_x; screen_x++) {
						if (screen_x >= _displayclipx1) {
							*pfbPixel = textbgcolor_index;
						}
						pfbPixel++;
					}
				}
				pfbPixel_row += _width;
			}

		} else 
		#endif
		{
			beginSPITransaction();
			//Serial.printf("SetAddr %d %d %d %d\n", start_x_min, start_y_min, end_x, end_y);
			// output rectangle we are updating... We have already clipped end_x/y, but not yet start_x/y
			setAddr( start_x_min, start_y_min, end_x, end_y);
			writecommand_cont(ILI9488_RAMWR);
			int screen_y = start_y_min;
			int screen_x;
			
			// Clear above character
			while (screen_y < origin_y) {
				for (screen_x = start_x_min; screen_x <= end_x; screen_x++) {
					write16BitColor(textbgcolor);
				}
				screen_y++;
			}
			
			// Anti-aliased font
			if (fontbpp>1){
				screen_y = origin_y;
				bitoffset = ((bitoffset + 7) & (-8)); // byte-boundary
				int glyphend_x = origin_x+width;
				uint32_t xp = 0;
				while (linecount) {
				 	screen_x = start_x;
					while(screen_x<=end_x) {
						// XXX: I'm sure clipping could be done way more efficiently than just chekcing every single pixel, but let's just get this going
						if ((screen_x >= _displayclipx1) && (screen_x < _displayclipx2) && (screen_y >= _displayclipy1) && (screen_y < _displayclipy2)) {
							// Clear before or after pixel
							if ((screen_x<origin_x) || (screen_x>=glyphend_x)){
								write16BitColor(textbgcolor);
							}
							// Draw alpha-blended character
							else{
								uint8_t alpha = fetchpixel(data, bitoffset, xp);
								write16BitColor( alphaBlendRGB565Premultiplied( textcolorPrexpanded, textbgcolorPrexpanded, (uint8_t)(alpha * fontalphamx) ) );
								bitoffset += fontbpp;
								xp++;
							}
						} // clip
						screen_x++;
					}
					screen_y++;
					linecount--;
				}

			} // anti-aliased

			// 1bpp
			else{
				// Now lets process each of the data lines. 
				screen_y = origin_y;
				while (linecount > 0) {
					//Serial.printf("    linecount = %d\n", linecount);
					uint32_t b = fetchbit(data, bitoffset++);
					uint32_t n;
					if (b == 0) {
						//Serial.println("    Single");
						n = 1;
					} else {
						//Serial.println("    Multi");
						n = fetchbits_unsigned(data, bitoffset, 3) + 2;
						bitoffset += 3;
					}
					uint32_t bitoffset_row_start = bitoffset;
					while (n--) {
						// do some clipping here. 
						bitoffset = bitoffset_row_start;	// we will work through these bits maybe multiple times
						// We need to handle case where some of the bits may not be visible, but we still need to
						// read through them
						//Serial.printf("y:%d  %d %d %d %d\n", screen_y, start_x, origin_x, _displayclipx1, _displayclipx2);
						if ((screen_y >= _displayclipy1) && (screen_y < _displayclipy2)) {
							for (screen_x = start_x; screen_x < origin_x; screen_x++) {
								if ((screen_x >= _displayclipx1) && (screen_x < _displayclipx2)) {
									//Serial.write('-');
									write16BitColor(textbgcolor);
								}
							}
						}	
						uint32_t x = 0;
						screen_x = origin_x;
						do {
							uint32_t xsize = width - x;
							if (xsize > 32) xsize = 32;
							uint32_t bits = fetchbits_unsigned(data, bitoffset, xsize);
							uint32_t bit_mask = 1 << (xsize-1);
							//Serial.printf("     %d %d %x %x - ", x, xsize, bits, bit_mask);
							if ((screen_y >= _displayclipy1) && (screen_y < _displayclipy2)) {
								while (bit_mask) {
									if ((screen_x >= _displayclipx1) && (screen_x < _displayclipx2)) {
										write16BitColor((bits & bit_mask) ? textcolor : textbgcolor);
										//Serial.write((bits & bit_mask) ? '*' : '.');
									}
									bit_mask = bit_mask >> 1;
									screen_x++ ; // Current actual screen X
								}
								//Serial.println();
								bitoffset += xsize;
							}
							x += xsize;
						} while (x < width) ;
						if ((screen_y >= _displayclipy1) && (screen_y < _displayclipy2)) {
							// output bg color and right hand side
							while (screen_x++ <= end_x) {
								write16BitColor(textbgcolor);
								//Serial.write('+');
							}
							//Serial.println();
						}
						screen_y++;
						linecount--;
					}
				}
			} // 1bpp
			
			// clear below character - note reusing xcreen_x for this
			screen_x = (end_y + 1 - screen_y) * (end_x + 1 - start_x_min); // How many bytes we need to still output
			//Serial.printf("Clear Below: %d\n", screen_x);
			while (screen_x-- > 1) {
				write16BitColor(textbgcolor);
			}
			write16BitColor(textbgcolor, true);
			endSPITransaction();
		}

	}
	// Increment to setup for the next character.
	cursor_x += delta;

}

//strPixelLen			- gets pixel length of given ASCII string
int16_t BMC_ILI9488_t3::strPixelLen(const char * str, uint16_t cb)
{
//	Serial.printf("strPixelLen %s\n", str);
	if (!str) return(0);
	if (gfxFont) 
	{
		// BUGBUG:: just use the other function for now... May do this for all of them...
		int16_t x, y;
		uint16_t w, h;
		if (cb == 0xffff)
			getTextBounds(str, cursor_x, cursor_y, &x, &y, &w, &h);  // default no count passed in
		else
			getTextBounds((const uint8_t *)str, cb, cursor_x, cursor_y, &x, &y, &w, &h);
		return w;
	}

	uint16_t len=0, maxlen=0;
	while (*str && cb)
	{
		if (*str=='\n')
		{
			if ( len > maxlen )
			{
				maxlen=len;
				len=0;
			}
		}
		else
		{
			if (!font)
			{
				len+=textsize_x*6;
			}
			else
			{

				uint32_t bitoffset;
				const uint8_t *data;
				uint16_t c = *str;

//				Serial.printf("char %c(%d)\n", c,c);

				if (c >= font->index1_first && c <= font->index1_last) {
					bitoffset = c - font->index1_first;
					bitoffset *= font->bits_index;
				} else if (c >= font->index2_first && c <= font->index2_last) {
					bitoffset = c - font->index2_first + font->index1_last - font->index1_first + 1;
					bitoffset *= font->bits_index;
				} else if (font->unicode) {
					continue;
				} else {
					continue;
				}
				//Serial.printf("  index =  %d\n", fetchbits_unsigned(font->index, bitoffset, font->bits_index));
				data = font->data + fetchbits_unsigned(font->index, bitoffset, font->bits_index);

				uint32_t encoding = fetchbits_unsigned(data, 0, 3);
				if (encoding != 0) continue;
//				uint32_t width = fetchbits_unsigned(data, 3, font->bits_width);
//				Serial.printf("  width =  %d\n", width);
				bitoffset = font->bits_width + 3;
				bitoffset += font->bits_height;

//				int32_t xoffset = fetchbits_signed(data, bitoffset, font->bits_xoffset);
//				Serial.printf("  xoffset =  %d\n", xoffset);
				bitoffset += font->bits_xoffset;
				bitoffset += font->bits_yoffset;

				uint32_t delta = fetchbits_unsigned(data, bitoffset, font->bits_delta);
				bitoffset += font->bits_delta;
//				Serial.printf("  delta =  %d\n", delta);

				len += delta;//+width-xoffset;
//				Serial.printf("  len =  %d\n", len);
				if ( len > maxlen )
				{
					maxlen=len;
//					Serial.printf("  maxlen =  %d\n", maxlen);
				}
			
			}
		}
		str++;
	}
//	Serial.printf("Return  maxlen =  %d\n", maxlen);
	return( maxlen );
}

void BMC_ILI9488_t3::charBounds(char c, int16_t *x, int16_t *y,
  int16_t *minx, int16_t *miny, int16_t *maxx, int16_t *maxy) {

	// BUGBUG:: Not handling offset/clip
    if (font) {
        if(c == '\n') { // Newline?
            *x  = 0;    // Reset x to zero, advance y by one line
            *y += font->line_space;
        } else if(c != '\r') { // Not a carriage return; is normal char
			uint32_t bitoffset;
			const uint8_t *data;
			if (c >= font->index1_first && c <= font->index1_last) {
				bitoffset = c - font->index1_first;
				bitoffset *= font->bits_index;
			} else if (c >= font->index2_first && c <= font->index2_last) {
				bitoffset = c - font->index2_first + font->index1_last - font->index1_first + 1;
				bitoffset *= font->bits_index;
			} else if (font->unicode) {
				return; // TODO: implement sparse unicode
			} else {
				return;
			}
			//Serial.printf("  index =  %d\n", fetchbits_unsigned(font->index, bitoffset, font->bits_index));
			data = font->data + fetchbits_unsigned(font->index, bitoffset, font->bits_index);

			uint32_t encoding = fetchbits_unsigned(data, 0, 3);
			if (encoding != 0) return;
			uint32_t width = fetchbits_unsigned(data, 3, font->bits_width);
			bitoffset = font->bits_width + 3;
			uint32_t height = fetchbits_unsigned(data, bitoffset, font->bits_height);
			bitoffset += font->bits_height;
			//Serial.printf("  size =   %d,%d\n", width, height);
			//Serial.printf("  line space = %d\n", font->line_space);

			int32_t xoffset = fetchbits_signed(data, bitoffset, font->bits_xoffset);
			bitoffset += font->bits_xoffset;
			int32_t yoffset = fetchbits_signed(data, bitoffset, font->bits_yoffset);
			bitoffset += font->bits_yoffset;

			uint32_t delta = fetchbits_unsigned(data, bitoffset, font->bits_delta);
			bitoffset += font->bits_delta;

            int16_t
                    x1 = *x + xoffset,
                    y1 = *y + font->cap_height - height - yoffset,
                    x2 = x1 + width,
                    y2 = y1 + height;

		    if(wrap && (x2 > _width)) {
	            *x  = 0; // Reset x to zero, advance y by one line
	            *y += font->line_space;
	            x1 = *x + xoffset,
	            y1 = *y + yoffset,
	            x2 = x1 + width,
	            y2 = y1 + height;
        	}
            if(x1 < *minx) *minx = x1;
            if(y1 < *miny) *miny = y1;
            if(x2 > *maxx) *maxx = x2;
            if(y2 > *maxy) *maxy = y2;
            *x += delta;	// ? guessing here...
        }
    } 

    else if(gfxFont) {

        if(c == '\n') { // Newline?
            *x  = 0;    // Reset x to zero, advance y by one line
            *y += textsize_y * gfxFont->yAdvance;
        } else if(c != '\r') { // Not a carriage return; is normal char
            uint8_t first = gfxFont->first,
                    last  = gfxFont->last;
            if((c >= first) && (c <= last)) { // Char present in this font?
    			GFXglyph *glyph  = gfxFont->glyph + (c - first);
                uint8_t gw = glyph->width,
                        gh = glyph->height,
                        xa = glyph->xAdvance;
                int8_t  xo = glyph->xOffset,
                        yo = glyph->yOffset + gfxFont->yAdvance/2;
                if(wrap && ((*x+(((int16_t)xo+gw)*textsize_x)) > _width)) {
                    *x  = 0; // Reset x to zero, advance y by one line
                    *y += textsize_y * gfxFont->yAdvance;
                }
                int16_t tsx = (int16_t)textsize_x,
                        tsy = (int16_t)textsize_y,
                        x1 = *x + xo * tsx,
                        y1 = *y + yo * tsy,
                        x2 = x1 + gw * tsx - 1,
                        y2 = y1 + gh * tsy - 1;
                if(x1 < *minx) *minx = x1;
                if(y1 < *miny) *miny = y1;
                if(x2 > *maxx) *maxx = x2;
                if(y2 > *maxy) *maxy = y2;
                *x += xa * tsx;
            }
        }

    } else { // Default font

        if(c == '\n') {                     // Newline?
            *x  = 0;                        // Reset x to zero,
            *y += textsize_y * 8;           // advance y one line
            // min/max x/y unchaged -- that waits for next 'normal' character
        } else if(c != '\r') {  // Normal char; ignore carriage returns
            if(wrap && ((*x + textsize_x * 6) > _width)) { // Off right?
                *x  = 0;                    // Reset x to zero,
                *y += textsize_y * 8;       // advance y one line
            }
            int x2 = *x + textsize_x * 6 - 1, // Lower-right pixel of char
                y2 = *y + textsize_y * 8 - 1;
            if(x2 > *maxx) *maxx = x2;      // Track max x, y
            if(y2 > *maxy) *maxy = y2;
            if(*x < *minx) *minx = *x;      // Track min x, y
            if(*y < *miny) *miny = *y;
            *x += textsize_x * 6;             // Advance x one char
        }
    }
}

// Add in Adafruit versions of text bounds calculations. 
void BMC_ILI9488_t3::getTextBounds(const uint8_t *buffer, uint16_t len, int16_t x, int16_t y,
      int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h) {
    *x1 = x;
    *y1 = y;
    *w  = *h = 0;

    int16_t minx = _width, miny = _height, maxx = -1, maxy = -1;

    while(len--)
        charBounds(*buffer++, &x, &y, &minx, &miny, &maxx, &maxy);

    if(maxx >= minx) {
        *x1 = minx;
        *w  = maxx - minx + 1;
    }
    if(maxy >= miny) {
        *y1 = miny;
        *h  = maxy - miny + 1;
    }
}

void BMC_ILI9488_t3::getTextBounds(const char *str, int16_t x, int16_t y,
        int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h) {
    uint8_t c; // Current character

    *x1 = x;
    *y1 = y;
    *w  = *h = 0;

    int16_t minx = _width, miny = _height, maxx = -1, maxy = -1;

    while((c = *str++))
        charBounds(c, &x, &y, &minx, &miny, &maxx, &maxy);

    if(maxx >= minx) {
        *x1 = minx;
        *w  = maxx - minx + 1;
    }
    if(maxy >= miny) {
        *y1 = miny;
        *h  = maxy - miny + 1;
    }
}

void BMC_ILI9488_t3::getTextBounds(const String &str, int16_t x, int16_t y,
        int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h) {
    if (str.length() != 0) {
        getTextBounds(const_cast<char*>(str.c_str()), x, y, x1, y1, w, h);
    }
}

void BMC_ILI9488_t3::drawFontPixel( uint8_t alpha, uint32_t x, uint32_t y ){
	// Adjust alpha based on the number of alpha levels supported by the font (based on bpp)
	// Note: Implemented look-up table for alpha, but made absolutely no difference in speed (T3.6)
	alpha = (uint8_t)(alpha * fontalphamx);
	uint32_t result = ((((textcolorPrexpanded - textbgcolorPrexpanded) * alpha) >> 5) + textbgcolorPrexpanded) & 0b00000111111000001111100000011111;
	Pixel(x,y,(uint16_t)((result >> 16) | result));
}

void BMC_ILI9488_t3::drawFontBits(bool opaque, uint32_t bits, uint32_t numbits, int32_t x, int32_t y, uint32_t repeat)
{
	if (bits == 0) {
		if (opaque) {
			fillRect(x, y, numbits, repeat, textbgcolor);
		}
	} else {
		int32_t x1 = x;
		uint32_t n = numbits;
		int w;
		int bgw;

		w = 0;
		bgw = 0;

		do {
			n--;
			if (bits & (1 << n)) {
				if (bgw>0) {
					if (opaque) {
						fillRect(x1 - bgw, y, bgw, repeat, textbgcolor);
					}
					bgw=0;
				}
				w++;
			} else {
				if (w>0) {
					fillRect(x1 - w, y, w, repeat, textcolor);
					w = 0;
				}
				bgw++;
			}
			x1++;
		} while (n > 0);

		if (w > 0) {
			fillRect(x1 - w, y, w, repeat, textcolor);
		}

		if (bgw > 0) {
			if (opaque) {
				fillRect(x1 - bgw, y, bgw, repeat, textbgcolor);
			}
		}
	}
}

void BMC_ILI9488_t3::drawGFXFontChar(unsigned int c) {
	// Lets do Adafruit GFX character output here as well
    if(c == '\r') 	 return;

    // Some quick and dirty tests to see if we can
    uint8_t first = gfxFont->first;
    if((c < first) || (c > gfxFont->last)) return; 

    GFXglyph *glyph  = gfxFont->glyph + (c - first);
    uint8_t   w     = glyph->width,
              h     = glyph->height;
			  
    // wonder if we should look at xo, yo instead?         
    if((w == 0 ||  h == 0)  && (c != 32))   return;  // Is there an associated bitmap?
	
    int16_t xo = glyph->xOffset; // sic
    int16_t yo = glyph->yOffset + gfxFont->yAdvance/2;

    if(wrap && ((cursor_x + textsize_x * (xo + w)) > _width)) {
        cursor_x  = 0;
        cursor_y += (int16_t)textsize_y * gfxFont->yAdvance;
    }

    // Lets do the work to output the font character
    uint8_t  *bitmap = gfxFont->bitmap;

    uint16_t bo = glyph->bitmapOffset;
    uint8_t  xx, yy, bits = 0, bit = 0;
    //Serial.printf("DGFX_char: %c (%d,%d) : %u %u %u %u %d %d %x %x %d\n", c, cursor_x, cursor_y, w, h,  
    //			glyph->xAdvance, gfxFont->yAdvance, xo, yo, textcolor, textbgcolor, _use_fbtft);Serial.flush();

    if (textcolor == textbgcolor) {

	    // Serial.printf("DGFXChar: %c %u, %u, wh:%d %d o:%d %d\n", c, cursor_x, cursor_y, w, h, xo, yo);
	    // Todo: Add character clipping here

    	// NOTE: Adafruit GFX does not support Opaque font output as there
    	// are issues with proportionally spaced characters that may overlap
    	// So the below is not perfect as we may overwrite a small portion 
    	// of a letter with the next one, when we blank out... 
    	// But: I prefer to let each of us decide if the limitations are
    	// worth it or not.  If Not you still have the option to not
    	// Do transparent mode and instead blank out and blink...

	    for(yy=0; yy<h; yy++) {
			uint8_t w_left = w;
	    	xx = 0;
	        while (w_left) {
	            if(!(bit & 7)) {
	                bits = bitmap[bo++];
	            }
				// Could try up to 8 bits at time, but start off trying up to 4
	            uint8_t xCount;
	            if ((w_left >= 8) && ((bits & 0xff) == 0xff)) {
	            	xCount = 8;
	            	//Serial.print("8");
	                fillRect(cursor_x+(xo+xx)*textsize_x, cursor_y+(yo+yy)*textsize_y,
	                      xCount * textsize_x, textsize_y, textcolor);
	            } else if ((w_left >= 4) && ((bits & 0xf0) == 0xf0)) {
	            	xCount = 4;
	            	//Serial.print("4");
	                fillRect(cursor_x+(xo+xx)*textsize_x, cursor_y+(yo+yy)*textsize_y,
	                      xCount * textsize_x, textsize_y, textcolor);
	            } else if ((w_left >= 3) && ((bits & 0xe0) == 0xe0)) {
	            	//Serial.print("3");
	            	xCount = 3;
	                fillRect(cursor_x+(xo+xx)*textsize_x, cursor_y+(yo+yy)*textsize_y,
                      xCount * textsize_x, textsize_y, textcolor);
	            } else if ((w_left >= 2) && ((bits & 0xc0) == 0xc0)) {
	            	//Serial.print("2");
	            	xCount = 2;
	                fillRect(cursor_x+(xo+xx)*textsize_x, cursor_y+(yo+yy)*textsize_y,
	                      xCount * textsize_x, textsize_y, textcolor);
	            } else {
	            	xCount = 1;
	            	if(bits & 0x80) {
		                if((textsize_x == 1) && (textsize_y == 1)){
		                    drawPixel(cursor_x+xo+xx, cursor_y+yo+yy, textcolor);
		                } else {
		                fillRect(cursor_x+(xo+xx)*textsize_x, cursor_y+(yo+yy)*textsize_y,
		                      textsize_x, textsize_y, textcolor);
		                }
		            }
	            }
	            xx += xCount;
	            w_left -= xCount;
	            bit += xCount;
	            bits <<= xCount;
			}
	    }
    	_gfx_last_char_x_write = 0;
		} else {
		// To Do, properly clipping and offsetting...
		// This solid background approach is about 5 time faster
		// Lets calculate bounding rectangle that we will update
		// We need to offset by the origin.

		// We are going direct so do some offsets and clipping
		int16_t x_offset_cursor = cursor_x + _originx;	// This is where the offseted cursor is.
		int16_t x_start = x_offset_cursor;  // I am assuming no negative x offsets.
		int16_t x_end = x_offset_cursor + (glyph->xAdvance * textsize_x);
		if (glyph->xAdvance < (xo + w)) x_end = x_offset_cursor + ((xo + w)* textsize_x);  // BUGBUG Overlflows into next char position.
		int16_t x_left_fill = x_offset_cursor + xo * textsize_x;
		int16_t x;
		if (xo < 0) { 
			// Unusual character that goes back into previous character
			//Serial.printf("GFX Font char XO < 0: %c %d %d %u %u %u\n", c, xo, yo, w, h, glyph->xAdvance );
			x_start += xo * textsize_x;
			x_left_fill = 0;	// Don't need to fill anything here... 
		}

		int16_t y_start = cursor_y + _originy + (_gfxFont_min_yOffset * textsize_y)+ gfxFont->yAdvance*textsize_y/2;  // UP to most negative value.
		int16_t y_end = y_start +  gfxFont->yAdvance * textsize_y;  // how far we will update
		int16_t y = y_start;
		//int8_t y_top_fill = (yo - _gfxFont_min_yOffset) * textsize_y;	 // both negative like -10 - -16 = 6...
		int8_t y_top_fill = (yo - gfxFont->yAdvance/2 - _gfxFont_min_yOffset) * textsize_y;


		// See if anything is within clip rectangle, if not bail
		if((x_start >= _displayclipx2)   || // Clip right
			 (y_start >= _displayclipy2) || // Clip bottom
			 (x_end < _displayclipx1)    || // Clip left
			 (y_end < _displayclipy1))  	// Clip top 
		{
			// But remember to first update the cursor position
			cursor_x += glyph->xAdvance * (int16_t)textsize_x;
			return;
		}

		// If our y_end > _displayclipy2 set it to _displayclipy2 as to not have to test both  Likewise X
		if (y_end > _displayclipy2) y_end = _displayclipy2;
		if (x_end > _displayclipx2) x_end = _displayclipx2;
		// If we get here and 
		if (_gfx_last_cursor_y != (cursor_y + _originy))  _gfx_last_char_x_write = 0;

		#ifdef ENABLE_ILI9488_FRAMEBUFFER
		if (_use_fbtft) {
			RAFB * pfbPixel_row = &_pfbtft[ y_start *_width + x_start];
			// lets try to output the values directly...
			RAFB * pfbPixel;
			RAFB textbgcolor_index = mapColorToPalletIndex(textbgcolor);
			RAFB textcolor_index = mapColorToPalletIndex(textcolor);
			
			// First lets fill in the top parts above the actual rectangle...
			while (y_top_fill--) {
				pfbPixel = pfbPixel_row;
				if ( (y >= _displayclipy1) && (y < _displayclipy2)) {
					for (int16_t xx = x_start; xx < x_end; xx++) {
						if ((xx >= _displayclipx1) && (xx >= x_offset_cursor)) {
							if ((xx >= _gfx_last_char_x_write) || (*pfbPixel != mapColorToPalletIndex(_gfx_last_char_textcolor)))
								*pfbPixel = textbgcolor_index;
						}
						pfbPixel++;
					}					
				}
				pfbPixel_row += _width;
				y++;
			}
			// Now lets output all of the pixels for each of the rows.. 
			for(yy=0; (yy<h) && (y < _displayclipy2); yy++) {
				uint16_t bo_save = bo;
				uint8_t bit_save = bit;
				uint8_t bits_save = bits;
				for (uint8_t yts = 0; (yts < textsize_y) && (y < _displayclipy2); yts++) {
					pfbPixel = pfbPixel_row;
					// need to repeat the stuff for each row...
					bo = bo_save;
					bit = bit_save;
					bits = bits_save;
					x = x_start;
					if (y >= _displayclipy1) {
						while (x < x_left_fill) {
							if ( (x >= _displayclipx1) && (x < _displayclipx2)) {
								if ((x >= _gfx_last_char_x_write) || (*pfbPixel != mapColorToPalletIndex(_gfx_last_char_textcolor))) 
									*pfbPixel = textbgcolor_index;;
							}
							pfbPixel++;
							x++;

						}
				        for(xx=0; xx<w; xx++) {
				            if(!(bit++ & 7)) {
				                bits = bitmap[bo++];
				            }
				            //uint8_t color_idx = (bits & 0x80)? textcolor_index : textbgcolor_index;
				            for (uint8_t xts = 0; xts < textsize_x; xts++) {
								if ( (x >= _displayclipx1) && (x < _displayclipx2)) {
									if (bits & 0x80) 
				            			*pfbPixel = textcolor_index; 
				            		else if (x >= x_offset_cursor) { 
										if ((x >= _gfx_last_char_x_write) || (*pfbPixel != mapColorToPalletIndex(_gfx_last_char_textcolor))) 
											*pfbPixel = textbgcolor_index;
									}
								}
								pfbPixel++;
				            	x++;	// remember our logical position...
				            }
				            bits <<= 1;
				        }
				        // Fill in any additional bg colors to right of our output
				        while (x++ < x_end) {
							if (x >= _displayclipx1) {
				        		*pfbPixel = textbgcolor_index;;
				        	}
							pfbPixel++;
				        }
				    }
			        y++;	// remember which row we just output
					pfbPixel_row += _width;
			    }
		    }
		    // And output any more rows below us...
			while (y < y_end) {
				if (y >= _displayclipy1) {
					pfbPixel = pfbPixel_row;
					for (int16_t xx = x_start; xx < x_end; xx++) {
						if ((xx >= _displayclipx1) && (xx >= x_offset_cursor)) {
							if ((xx >= _gfx_last_char_x_write) || (*pfbPixel != _gfx_last_char_textcolor))
								*pfbPixel = textbgcolor_index;
			        	}
						pfbPixel++;
					}					
				}
				pfbPixel_row += _width;
				y++;
			}
			
		} else 
		#endif
		{
			// lets try to output text in one output rectangle
			//Serial.printf("    SPI (%d %d) (%d %d)\n", x_start, y_start, x_end, y_end);Serial.flush();
			// compute the actual region we will output given 
			beginSPITransaction();
		
			setAddr((x_start >= _displayclipx1) ? x_start : _displayclipx1, 
					(y_start >= _displayclipy1) ? y_start : _displayclipy1, 
					x_end  - 1,  y_end - 1); 
			writecommand_cont(ILI9488_RAMWR);
			//Serial.printf("SetAddr: %u %u %u %u\n", (x_start >= _displayclipx1) ? x_start : _displayclipx1, 
			//		(y_start >= _displayclipy1) ? y_start : _displayclipy1, 
			//		x_end  - 1,  y_end - 1); 
			// First lets fill in the top parts above the actual rectangle...
			//Serial.printf("    y_top_fill %d x_left_fill %d\n", y_top_fill, x_left_fill);
			while (y_top_fill--) {
				if ( (y >= _displayclipy1) && (y < _displayclipy2)) {
					for (int16_t xx = x_start; xx < x_end; xx++) {
						if (xx >= _displayclipx1) {
							write16BitColor(gfxFontLastCharPosFG(xx,y)? _gfx_last_char_textcolor : (xx < x_offset_cursor)? _gfx_last_char_textbgcolor : textbgcolor);
						}
					}					
				}
				y++;
			}
			//Serial.println("    After top fill"); Serial.flush();
			// Now lets output all of the pixels for each of the rows.. 
			for(yy=0; (yy<h) && (y < _displayclipy2); yy++) {
				uint16_t bo_save = bo;
				uint8_t bit_save = bit;
				uint8_t bits_save = bits;
				for (uint8_t yts = 0; (yts < textsize_y) && (y < _displayclipy2); yts++) {
					// need to repeat the stuff for each row...
					bo = bo_save;
					bit = bit_save;
					bits = bits_save;
					x = x_start;
					if (y >= _displayclipy1) {
						while (x < x_left_fill) {
							if ( (x >= _displayclipx1) && (x < _displayclipx2)) {
								// Don't need to check if we are in previous char as in this case x_left_fill is set to 0...
								write16BitColor(gfxFontLastCharPosFG(x,y)? _gfx_last_char_textcolor :  textbgcolor);
							}
							x++;
						}
				        for(xx=0; xx<w; xx++) {
				            if(!(bit++ & 7)) {
				                bits = bitmap[bo++];
				            }
				            for (uint8_t xts = 0; xts < textsize_x; xts++) {
								if ( (x >= _displayclipx1) && (x < _displayclipx2)) {
									if (bits & 0x80) 
										write16BitColor(textcolor); 
									else  
										write16BitColor(gfxFontLastCharPosFG(x,y)? _gfx_last_char_textcolor : (x < x_offset_cursor)? _gfx_last_char_textbgcolor : textbgcolor);		
								}
				            	x++;	// remember our logical position...
				            }
				            bits <<= 1;
				        }
				        // Fill in any additional bg colors to right of our output
				        while (x < x_end) {
							if (x >= _displayclipx1) {
				        		write16BitColor(gfxFontLastCharPosFG(x,y)? _gfx_last_char_textcolor : (x < x_offset_cursor)? _gfx_last_char_textbgcolor : textbgcolor);
				        	}
				        	x++;
				        }
			    	}
		        	y++;	// remember which row we just output
			    }
		    }
		    // And output any more rows below us...
		    //Serial.println("    Bottom fill"); Serial.flush();
			while (y < y_end) {
				if (y >= _displayclipy1) {
					for (int16_t xx = x_start; xx < x_end; xx++) {
						if (xx >= _displayclipx1)  {
							write16BitColor(gfxFontLastCharPosFG(xx,y)? _gfx_last_char_textcolor : (xx < x_offset_cursor)? _gfx_last_char_textbgcolor : textbgcolor);
						}
					}
				}
				y++;
			}
			writecommand_last(ILI9488_NOP);
			endSPITransaction();
		}
		_gfx_c_last = c; 
		_gfx_last_cursor_x = cursor_x + _originx;  
		_gfx_last_cursor_y = cursor_y + _originy; 
		_gfx_last_char_x_write = x_end; 
		_gfx_last_char_textcolor = textcolor; 
		_gfx_last_char_textbgcolor = textbgcolor;
		
	}

    cursor_x += glyph->xAdvance * (int16_t)textsize_x;
}

// Some fonts overlap characters if we detect that the previous 
// character wrote out more width than they advanced in X direction
// we may want to know if the last character output a FG or BG at a position. 
	// Opaque font chracter overlap?
//	unsigned int _gfx_c_last;
//	int16_t   _gfx_last_cursor_x, _gfx_last_cursor_y;
//	int16_t	 _gfx_last_x_overlap = 0;
	
bool BMC_ILI9488_t3::gfxFontLastCharPosFG(int16_t x, int16_t y) {
    GFXglyph *glyph  = gfxFont->glyph + (_gfx_c_last -  gfxFont->first);

    uint8_t   w     = glyph->width,
              h     = glyph->height;


    int16_t xo = glyph->xOffset; // sic
    int16_t yo = glyph->yOffset + gfxFont->yAdvance/2;
    if (x >= _gfx_last_char_x_write) return false; 	// we did not update here...
    if (y < (_gfx_last_cursor_y + (yo*textsize_y)))  return false;  // above
    if (y >= (_gfx_last_cursor_y + (yo+h)*textsize_y)) return false; // below


    // Lets compute which Row this y is in the bitmap
    int16_t y_bitmap = (y - ((_gfx_last_cursor_y + (yo*textsize_y))) + textsize_y - 1) / textsize_y;
    int16_t x_bitmap = (x - ((_gfx_last_cursor_x + (xo*textsize_x))) + textsize_x - 1) / textsize_x;
    uint16_t  pixel_bit_offset = y_bitmap * w + x_bitmap;

    return ((gfxFont->bitmap[glyph->bitmapOffset + (pixel_bit_offset >> 3)]) & (0x80 >> (pixel_bit_offset & 0x7)));
}

void BMC_ILI9488_t3::setCursor(int16_t x, int16_t y, bool autoCenter) {
	_center_x_text = autoCenter;	// remember the state. 
	_center_y_text = autoCenter;	// remember the state. 
	if (x == BMC_ILI9488_t3::CENTER) {
		_center_x_text = true;
		x = _width/2;
	}
	if (y == BMC_ILI9488_t3::CENTER) {
		_center_y_text = true;
		y = _height/2;
	}
	if (x < 0) x = 0;
	else if (x >= _width) x = _width - 1;
	cursor_x = x;
	if (y < 0) y = 0;
	else if (y >= _height) y = _height - 1;
	cursor_y = y;
	
	if(x>=scroll_x && x<=(scroll_x+scroll_width) && y>=scroll_y && y<=(scroll_y+scroll_height)){
		isWritingScrollArea	= true;
	} else {
		isWritingScrollArea = false;
	}
	_gfx_last_char_x_write = 0;	// Don't use cached data here
}

void BMC_ILI9488_t3::getCursor(int16_t *x, int16_t *y) {
  *x = cursor_x;
  *y = cursor_y;
}

void BMC_ILI9488_t3::setTextSize(uint8_t s_x, uint8_t s_y) {
    textsize_x = (s_x > 0) ? s_x : 1;
    textsize_y = (s_y > 0) ? s_y : 1;
	_gfx_last_char_x_write = 0;	// Don't use cached data here
}

uint8_t BMC_ILI9488_t3::getTextSize() {
	return textsize_x;  // BUGBUG:: two values now...
}

void BMC_ILI9488_t3::setTextColor(uint16_t c) {
  // For 'transparent' background, we'll set the bg
  // to the same as fg instead of using a flag
  textcolor = textbgcolor = c;
}

void BMC_ILI9488_t3::setTextColor(uint16_t c, uint16_t b) {
  textcolor   = c;
  textbgcolor = b;
  // pre-expand colors for fast alpha-blending later
  textcolorPrexpanded = (textcolor | (textcolor << 16)) & 0b00000111111000001111100000011111;
  textbgcolorPrexpanded = (textbgcolor | (textbgcolor << 16)) & 0b00000111111000001111100000011111;
}

void BMC_ILI9488_t3::setTextWrap(boolean w) {
  wrap = w;
}

boolean BMC_ILI9488_t3::getTextWrap()
{
	return wrap;
}

uint8_t BMC_ILI9488_t3::getRotation(void) {
  return rotation;
}

void BMC_ILI9488_t3::sleep(bool enable) {
	beginSPITransaction();
	if (enable) {
		writecommand_cont(ILI9488_DISPOFF);		
		writecommand_last(ILI9488_SLPIN);	
		  endSPITransaction();
	} else {
		writecommand_cont(ILI9488_DISPON);
		writecommand_last(ILI9488_SLPOUT);
		endSPITransaction();
		delay(5);
	}
}



/***************************************************************************************
** Function name:           setTextDatum
** Description:             Set the text position reference datum
***************************************************************************************/
void BMC_ILI9488_t3::setTextDatum(uint8_t d)
{
  textdatum = d;
}


/***************************************************************************************
** Function name:           drawNumber
** Description:             draw a long integer
***************************************************************************************/
int16_t BMC_ILI9488_t3::drawNumber(long long_num, int poX, int poY)
{
  char str[14];
  ltoa(long_num, str, 10);
  return drawString(str, poX, poY);
}


int16_t BMC_ILI9488_t3::drawFloat(float floatNumber, int dp, int poX, int poY)
{
  char str[14];               // Array to contain decimal string
  uint8_t ptr = 0;            // Initialise pointer for array
  int8_t  digits = 1;         // Count the digits to avoid array overflow
  float rounding = 0.5;       // Round up down delta

  if (dp > 7) dp = 7; // Limit the size of decimal portion

  // Adjust the rounding value
  for (uint8_t i = 0; i < dp; ++i) rounding /= 10.0f;

  if (floatNumber < -rounding)    // add sign, avoid adding - sign to 0.0!
  {
    str[ptr++] = '-'; // Negative number
    str[ptr] = 0; // Put a null in the array as a precaution
    digits = 0;   // Set digits to 0 to compensate so pointer value can be used later
    floatNumber = -floatNumber; // Make positive
  }

  floatNumber += rounding; // Round up or down

  // For error put ... in string and return (all TFT_ILI9488_ESP library fonts contain . character)
  if (floatNumber >= 2147483647) {
    strcpy(str, "...");
    //return drawString(str, poX, poY);
  }
  // No chance of overflow from here on

  // Get integer part
  unsigned long temp = (unsigned long)floatNumber;

  // Put integer part into array
  ltoa(temp, str + ptr, 10);

  // Find out where the null is to get the digit count loaded
  while ((uint8_t)str[ptr] != 0) ptr++; // Move the pointer along
  digits += ptr;                  // Count the digits

  str[ptr++] = '.'; // Add decimal point
  str[ptr] = '0';   // Add a dummy zero
  str[ptr + 1] = 0; // Add a null but don't increment pointer so it can be overwritten

  // Get the decimal portion
  floatNumber = floatNumber - temp;

  // Get decimal digits one by one and put in array
  // Limit digit count so we don't get a false sense of resolution
  uint8_t i = 0;
  while ((i < dp) && (digits < 9)) // while (i < dp) for no limit but array size must be increased
  {
    i++;
    floatNumber *= 10;       // for the next decimal
    temp = floatNumber;      // get the decimal
    ltoa(temp, str + ptr, 10);
    ptr++; digits++;         // Increment pointer and digits count
    floatNumber -= temp;     // Remove that digit
  }

  // Finally we can plot the string and return pixel length
  return drawString(str, poX, poY);
}

/***************************************************************************************
** Function name:           drawString (with or without user defined font)
** Description :            draw string with padding if it is defined
***************************************************************************************/
// Without font number, uses font set by setTextFont()
int16_t BMC_ILI9488_t3::drawString(const String& string, int poX, int poY)
{
  int16_t len = string.length() + 2;
  char buffer[len];
  string.toCharArray(buffer, len);
  return drawString(buffer, len-2, poX, poY);
}

int16_t BMC_ILI9488_t3::drawString(const char string[], int16_t len, int poX, int poY)
{
  int16_t sumX = 0;
  uint8_t padding = 1;
  
  uint16_t cwidth =
      strPixelLen(string, len); // Find the pixel width of the string in the font
  uint16_t cheight = textsize*8;
  
  if (textdatum || padX)
  {
    switch(textdatum) {
      case TC_DATUM:
        poX -= cwidth/2;
        padding += 1;
        break;
      case TR_DATUM:
        poX -= cwidth;
        padding += 2;
        break;
      case ML_DATUM:
        poY -= cheight/2;
        //padding += 0;
        break;
      case MC_DATUM:
        poX -= cwidth/2;
        poY -= cheight/2;
        padding += 1;
        break;
      case MR_DATUM:
        poX -= cwidth;
        poY -= cheight/2;
        padding += 2;
        break;
      case BL_DATUM:
        poY -= cheight;
        //padding += 0;
        break;
      case BC_DATUM:
        poX -= cwidth/2;
        poY -= cheight;
        padding += 1;
        break;
      case BR_DATUM:
        poX -= cwidth;
        poY -= cheight;
        padding += 2;
        break;
	 /*
      case L_BASELINE:
        poY -= baseline;
        //padding += 0;
        break;
      case C_BASELINE:
        poX -= cwidth/2;
        poY -= baseline;
        //padding += 1;
        break;
      case R_BASELINE:
        poX -= cwidth;
        poY -= baseline;
        padding += 2;
        break;
	*/
    }
    // Check coordinates are OK, adjust if not
    if (poX < 0) poX = 0;
    if (poX+cwidth > width())   poX = width() - cwidth;
    if (poY < 0) poY = 0;
    //if (poY+cheight-baseline >_height) poY = _height - cheight;
  }
  if(font == NULL){
	  for(uint8_t i = 0; i < len; i++){
		drawChar((int16_t) (poX+sumX), (int16_t) poY, string[i], textcolor, textbgcolor, textsize);
		sumX += cwidth/(len-2) + padding;
	  }
  } else {
	  setCursor(poX, poY);
	  for(uint8_t i = 0; i < len; i++){
		drawFontChar(string[i]);
		setCursor(cursor_x, cursor_y);
	  }
  }
return sumX;
}

void BMC_ILI9488_t3::scrollTextArea(uint8_t scrollSize){
	uint16_t awColors[scroll_width];
	for (int y=scroll_y+scrollSize; y < (scroll_y+scroll_height); y++) { 
		readRect(scroll_x, y, scroll_width, 1, awColors); 
		writeRect(scroll_x, y-scrollSize, scroll_width, 1, awColors);  
	}
	fillRect(scroll_x, (scroll_y+scroll_height)-scrollSize, scroll_width, scrollSize, scrollbgcolor);
}

void BMC_ILI9488_t3::setScrollTextArea(int16_t x, int16_t y, int16_t w, int16_t h){
	scroll_x = x; 
	scroll_y = y;
	scroll_width = w; 
	scroll_height = h;
}

void BMC_ILI9488_t3::setScrollBackgroundColor(uint16_t color){
	scrollbgcolor=color;
	fillRect(scroll_x,scroll_y,scroll_width,scroll_height,scrollbgcolor);
}

void BMC_ILI9488_t3::enableScroll(void){
	scrollEnable = true;
}

void BMC_ILI9488_t3::disableScroll(void){
	scrollEnable = false;
}

void BMC_ILI9488_t3::resetScrollBackgroundColor(uint16_t color){
	scrollbgcolor=color;
}	


//=============================================================================
// DMA - Async support
//=============================================================================
#ifdef ENABLE_ILI9488_FRAMEBUFFER

#if defined(__IMXRT1052__) || defined(__IMXRT1062__)  // Teensy 4.x
void BMC_ILI9488_t3::dmaInterrupt(void) {
	if (_dmaActiveDisplay[0])  {
		_dmaActiveDisplay[0]->process_dma_interrupt();
	}
}
void BMC_ILI9488_t3::dmaInterrupt1(void) {
	if (_dmaActiveDisplay[1])  {
		_dmaActiveDisplay[1]->process_dma_interrupt();
	}
}
void BMC_ILI9488_t3::dmaInterrupt2(void) {
	if (_dmaActiveDisplay[2])  {
		_dmaActiveDisplay[2]->process_dma_interrupt();
	}
}


#else
void BMC_ILI9488_t3::dmaInterrupt(void) {
	if (_dmaActiveDisplay)  {
		_dmaActiveDisplay->process_dma_interrupt();
	}
}
#endif

#endif

#ifdef DEBUG_ASYNC_UPDATE
extern void dumpDMA_TCD(DMABaseClass *dmabc);
#endif

#define COUNT_SUBFRAMES_PER_FRAME (ILI9488_TFTHEIGHT*ILI9488_TFTWIDTH/DMA_PIXELS_OUTPUT_PER_DMA)

#if defined(__IMXRT1052__) || defined(__IMXRT1062__) || defined(__MK66FX1M0__)
// T3.6 and T4 processing
void BMC_ILI9488_t3::process_dma_interrupt(void) {
#if defined(ENABLE_EXT_DMA_UPDATES)
//-----------------------------------------------
// Frame buffer is in DMA memory format 
//---------------------------------------------------	
	_dmatx.clearInterrupt();
	if (_frame_callback_on_HalfDone && (_dmatx.TCD->SADDR > _dmasettings[2].TCD->SADDR)) {
		_dma_sub_frame_count = 1;	// set as partial frame.
		if (_frame_complete_callback) (*_frame_complete_callback)();
	} else {
		_dma_frame_count++;
		_dma_sub_frame_count = 0;

		// See if we are in continuous mode or not..
		if ((_dma_state & ILI9488_DMA_CONT) == 0) {
			// We are in single refresh mode or the user has called cancel so
			// Lets try to release the CS pin
			//Serial.printf("Before FSR wait: %x %x\n", _pimxrt_spi->FSR, _pimxrt_spi->SR);
			while (_pimxrt_spi->FSR & 0x1f)  ;	// wait until this one is complete

			//Serial.printf("Before SR busy wait: %x\n", _pimxrt_spi->SR);
			while (_pimxrt_spi->SR & LPSPI_SR_MBF)  ;	// wait until this one is complete

			_dmatx.clearComplete();
			//Serial.println("Restore FCR");
			_pimxrt_spi->FCR = LPSPI_FCR_TXWATER(15); // _spi_fcr_save;	// restore the FSR status... 
				_pimxrt_spi->DER = 0;		// DMA no longer doing TX (or RX)

			_pimxrt_spi->CR = LPSPI_CR_MEN | LPSPI_CR_RRF | LPSPI_CR_RTF;   // actually clear both...
			_pimxrt_spi->SR = 0x3f00;	// clear out all of the other status...

			maybeUpdateTCR(_tcr_dc_assert | LPSPI_TCR_FRAMESZ(7));	// output Command with 8 bits
			// Serial.printf("Output NOP (SR %x CR %x FSR %x FCR %x %x TCR:%x)\n", _pimxrt_spi->SR, _pimxrt_spi->CR, _pimxrt_spi->FSR, 
			//	_pimxrt_spi->FCR, _spi_fcr_save, _pimxrt_spi->TCR);
			writecommand_last(ILI9488_NOP);
			endSPITransaction();
			_dma_state &= ~ILI9488_DMA_ACTIVE;
			_dmaActiveDisplay[_spi_num]  = 0;	// We don't have a display active any more... 
		} else {
			// Lets try to flush out memory
			// 
			if (_frame_complete_callback) (*_frame_complete_callback)();
			else if ((uint32_t)_pfbtft >= 0x20200000u)  arm_dcache_flush(_pfbtft, CBALLOC);
		}
	}	
	asm("dsb");
#else
//-----------------------------------------------
// Build DMA output buffers from Frame buffer mode... 
//---------------------------------------------------	
#ifdef DEBUG_ASYNC_LEDS
	digitalWriteFast(DEBUG_PIN_2, HIGH);
#endif
	_dma_sub_frame_count++;
	if (_dma_sub_frame_count < COUNT_SUBFRAMES_PER_FRAME)
	{
		// We need to fill in the finished buffer with the next set of pixel data
		bool frame_complete =  fillDMApixelBuffer((_dma_sub_frame_count & 1) ? _dma_pixel_buffer0 : _dma_pixel_buffer1);
 		if (frame_complete && ((_dma_state & ILI9488_DMA_CONT) == 0) ) {
			_dmasettings[1].disableOnCompletion();
		}
	} else {

		_dma_frame_count++;
		//Serial.println("\nFrame complete");

		if ((_dma_state & ILI9488_DMA_CONT) == 0) {
			// We are in single refresh mode or the user has called cancel so
			// Lets try to release the CS pin
			// Lets wait until FIFO is not empty
			// Serial.printf("Before FSR wait: %x %x\n", _pimxrt_spi->FSR, _pimxrt_spi->SR);
			//Serial.println("End DMA transfer");
#if defined(__IMXRT1052__) || defined(__IMXRT1062__)  // Teensy 4.x
			while (_pimxrt_spi->FSR & 0x1f)  ;	// wait until this one is complete

			 //Serial.printf("Before SR busy wait: %x\n", _pimxrt_spi->SR);
			while (_pimxrt_spi->SR & LPSPI_SR_MBF)  ;	// wait until this one is complete

			_dmatx.clearComplete();
			//Serial.println("Restore FCR");
			_pimxrt_spi->FCR = LPSPI_FCR_TXWATER(15); // _spi_fcr_save;	// restore the FSR status... 
	 		_pimxrt_spi->DER = 0;		// DMA no longer doing TX (or RX)

			_pimxrt_spi->CR = LPSPI_CR_MEN | LPSPI_CR_RRF | LPSPI_CR_RTF;   // actually clear both...
			_pimxrt_spi->SR = 0x3f00;	// clear out all of the other status...


			maybeUpdateTCR(_tcr_dc_assert | LPSPI_TCR_FRAMESZ(7));	// output Command with 8 bits
			// Serial.printf("Output NOP (SR %x CR %x FSR %x FCR %x %x TCR:%x)\n", _pimxrt_spi->SR, _pimxrt_spi->CR, _pimxrt_spi->FSR, 
			//	_pimxrt_spi->FCR, _spi_fcr_save, _pimxrt_spi->TCR);
#elif defined(__MK66FX1M0__) 
			// T3.6
			// Maybe only have to wait for fifo not to be full so we can output NOP>>> 
			waitFifoNotFull();
#endif

	#ifdef DEBUG_ASYNC_LEDS
			digitalWriteFast(DEBUG_PIN_3, HIGH);
	#endif
			#if defined(__IMXRT1052__) || defined(__IMXRT1062__)  // Teensy 4.x
			_pending_rx_count = 0;	// Make sure count is zero
			#endif
			writecommand_last(ILI9488_NOP);
	#ifdef DEBUG_ASYNC_LEDS
			digitalWriteFast(DEBUG_PIN_3, LOW);
	#endif

			// Serial.println("Do End transaction");
			endSPITransaction();
			_dma_state &= ~ILI9488_DMA_ACTIVE;
			#if defined(__IMXRT1062__)  // Teensy 4.x
			_dmaActiveDisplay[_spi_num]  = nullptr;
			#else
			_dmaActiveDisplay = nullptr;	// We don't have a display active any more... 
			#endif
	 		 //Serial.println("After End transaction");

		} else {
			// Still going on. - setup to grab pixels from start of frame again...
			_dma_sub_frame_count = 0;
			//_dma_pixel_index = 0;
			fillDMApixelBuffer(_dma_pixel_buffer1);
		}
	}
#ifdef DEBUG_ASYNC_LEDS
	digitalWriteFast(DEBUG_PIN_2, LOW);
#endif
	_dmatx.clearInterrupt();
	asm("dsb");
#endif	
}


// T3.5 - without scatter gather support
#elif defined(__MK64FX512__)
void BMC_ILI9488_t3::process_dma_interrupt(void) {
#ifdef DEBUG_ASYNC_LEDS
	digitalWriteFast(DEBUG_PIN_2, HIGH);
#endif
	// Clear out the interrupt and complete state
	_dmatx.clearInterrupt();
	_dmatx.clearComplete();

	// Guess if we we are totally done or not...
	// Hack since we are reading a page ahead look at pixel_index 
	if (_dma_pixel_index == DMA_PIXELS_OUTPUT_PER_DMA)  {
		_dma_frame_count++;
		_dma_sub_frame_count = 0;
		if ((_dma_state & ILI9488_DMA_CONT) == 0) {
			// We are done!
			_pkinetisk_spi->RSER = 0;
			//_pkinetisk_spi->MCR = SPI_MCR_MSTR | SPI_MCR_CLR_RXF | SPI_MCR_PCSIS(0x1F);  // clear out the queue
			_pkinetisk_spi->SR = 0xFF0F0000;

			writecommand_last(ILI9488_NOP);
			endSPITransaction();
			_dma_state &= ~ILI9488_DMA_ACTIVE;
			_dmaActiveDisplay = 0;	// We don't have a display active any more... 
		}
	}

	_dma_sub_frame_count++;

	// Now lets alternate buffers
	if (_dmatx.TCD->SADDR < (void*)_dma_pixel_buffer1) {
		_dmatx.sourceBuffer(_dma_pixel_buffer1, sizeof(_dma_pixel_buffer1));
		_dmatx.enable();

		fillDMApixelBuffer(_dma_pixel_buffer0);
	} else {
		_dmatx.sourceBuffer(_dma_pixel_buffer0, sizeof(_dma_pixel_buffer0));
		_dmatx.enable();

		fillDMApixelBuffer(_dma_pixel_buffer1);
	}
#ifdef DEBUG_ASYNC_LEDS
	digitalWriteFast(DEBUG_PIN_2, LOW);
#endif
}
#endif

#ifdef ENABLE_ILI9488_FRAMEBUFFER
void	BMC_ILI9488_t3::initDMASettings(void) 
{
	// Serial.printf("initDMASettings called %d\n", _dma_state);
	if (_dma_state) {  // should test for init, but...
		return;	// we already init this. 
	}

	// T3.6 and T4... 
#if defined(__IMXRT1052__) || defined(__IMXRT1062__)  // Teensy 4.x
	#if defined(ENABLE_EXT_DMA_UPDATES)
	//=============================================
	// Storing data in 32 bits so can do direct DMAsss
	//=============================================
	// 320*480/5 = 30720
	_dmasettings[0].sourceBuffer(_pfbtft, (COUNT_WORDS_WRITE)*4);
	_dmasettings[0].destination(_pimxrt_spi->TDR);
	// _dmasettings[0].TCD->ATTR_DST = 1;  // Will do 32 bit writes
	_dmasettings[0].replaceSettingsOnCompletion(_dmasettings[1]);

	_dmasettings[1].sourceBuffer(&_pfbtft[COUNT_WORDS_WRITE], COUNT_WORDS_WRITE*4);
	_dmasettings[1].destination(_pimxrt_spi->TDR);
	//_dmasettings[1].TCD->ATTR_DST = 1;
	_dmasettings[1].replaceSettingsOnCompletion(_dmasettings[2]);

	_dmasettings[2].sourceBuffer(&_pfbtft[COUNT_WORDS_WRITE*2], COUNT_WORDS_WRITE*4);
	_dmasettings[2].destination(_pimxrt_spi->TDR);
	//_dmasettings[2].TCD->ATTR_DST = 1;
	_dmasettings[2].replaceSettingsOnCompletion(_dmasettings[3]);
	if (_frame_callback_on_HalfDone) _dmasettings[2].interruptAtHalf();
	else  _dmasettings[2].TCD->CSR &= ~DMA_TCD_CSR_INTHALF;
	_dmasettings[3].sourceBuffer(&_pfbtft[COUNT_WORDS_WRITE*3], COUNT_WORDS_WRITE*4);
	_dmasettings[3].destination(_pimxrt_spi->TDR);
	//_dmasettings[3].TCD->ATTR_DST = 1;
	_dmasettings[3].replaceSettingsOnCompletion(_dmasettings[4]);

	_dmasettings[4].sourceBuffer(&_pfbtft[COUNT_WORDS_WRITE*4], COUNT_WORDS_WRITE*4);
	_dmasettings[4].destination(_pimxrt_spi->TDR);
	//_dmasettings[4].TCD->ATTR_DST = 1;
	_dmasettings[4].replaceSettingsOnCompletion(_dmasettings[0]);
	_dmasettings[4].interruptAtCompletion();


	//============================================
	#else
	// Now lets setup DMA access to this memory... 
	// Try to do like T3.6 except not kludge for first word...
	// Serial.println("DMA initDMASettings - before settings");
	// Serial.printf("  CWW: %d %d %d\n", CBALLOC, SCREEN_DMA_NUM_SETTINGS, COUNT_WORDS_WRITE);
	_dmasettings[0].sourceBuffer(_dma_pixel_buffer0, sizeof(_dma_pixel_buffer0));
	_dmasettings[0].destination(_pimxrt_spi->TDR);
//	_dmasettings[0].TCD->ATTR_DST = 0;		// This should be 2 (32 bit)
	_dmasettings[0].replaceSettingsOnCompletion(_dmasettings[1]);
	_dmasettings[0].interruptAtCompletion();

	_dmasettings[1].sourceBuffer(_dma_pixel_buffer1, sizeof(_dma_pixel_buffer1));
	_dmasettings[1].destination(_pimxrt_spi->TDR);
//	_dmasettings[1].TCD->ATTR_DST = 0;
	_dmasettings[1].replaceSettingsOnCompletion(_dmasettings[0]);
	_dmasettings[1].interruptAtCompletion();

	#endif
	// Setup DMA main object
	//Serial.println("Setup _dmatx");
	// Serial.println("DMA initDMASettings - before dmatx");
	_dmatx.begin(true);
	_dmatx.triggerAtHardwareEvent(_spi_hardware->tx_dma_channel);
	_dmatx = _dmasettings[0];
	if (_spi_num == 0) _dmatx.attachInterrupt(dmaInterrupt);
	else if (_spi_num == 1) _dmatx.attachInterrupt(dmaInterrupt1);
	else _dmatx.attachInterrupt(dmaInterrupt2);
#elif defined(__MK66FX1M0__) 
	_dmasettings[0].sourceBuffer(&_dma_pixel_buffer0[3], sizeof(_dma_pixel_buffer0)-3);
	_dmasettings[0].destination(_pkinetisk_spi->PUSHR);
	_dmasettings[0].TCD->ATTR_DST = 0;
	_dmasettings[0].replaceSettingsOnCompletion(_dmasettings[1]);
	_dmasettings[0].interruptAtCompletion();

	_dmasettings[1].sourceBuffer(_dma_pixel_buffer1, sizeof(_dma_pixel_buffer1));
	_dmasettings[1].destination(_pkinetisk_spi->PUSHR);
	_dmasettings[1].TCD->ATTR_DST = 0;
	_dmasettings[1].replaceSettingsOnCompletion(_dmasettings[2]);
	_dmasettings[1].interruptAtCompletion();

	_dmasettings[2].sourceBuffer(_dma_pixel_buffer0, sizeof(_dma_pixel_buffer0));
	_dmasettings[2].destination(_pkinetisk_spi->PUSHR);
	_dmasettings[2].TCD->ATTR_DST = 0;
	_dmasettings[2].replaceSettingsOnCompletion(_dmasettings[1]);
	_dmasettings[2].interruptAtCompletion();
	// Setup DMA main object
	//Serial.println("Setup _dmatx");
	// Serial.println("DMA initDMASettings - before dmatx");
	_dmatx.begin(true);
	_dmatx.triggerAtHardwareEvent(_spi_hardware->tx_dma_channel);
	_dmatx = _dmasettings[0];
	_dmatx.attachInterrupt(dmaInterrupt);
#elif defined(__MK64FX512__)
	// Teensy 3.5
	// T3.5
	// Lets setup the write size.  For SPI we can use up to 32767 so same size as we use on T3.6...
	// But SPI1 and SPI2 max of 511.  We will use 480 in that case as even divider...
/*
	_dmarx.disable();
	_dmarx.source(_pkinetisk_spi->POPR);
	_dmarx.TCD->ATTR_SRC = 1;
	_dmarx.destination(_dma_dummy_rx);
	_dmarx.disableOnCompletion();
	_dmarx.triggerAtHardwareEvent(_spi_hardware->rx_dma_channel);
	_dmarx.attachInterrupt(dmaInterrupt);
	_dmarx.interruptAtCompletion();
*/
	// We may be using settings chain here so lets set it up. 
	// Now lets setup TX chain.  Note if trigger TX is not set
	// we need to have the RX do it for us.
	// BUGBUG:: REAL Hack
	if (!_csport) {
		// Should also probably change the masks... But
		pinMode(_cs, OUTPUT);
		_csport    = portOutputRegister(digitalPinToPort(_cs));
		_cspinmask = digitalPinToBitMask(_cs);
		Serial.println("DMASettings (T3.5) change CS pin to standard IO");
	}

	_dmatx.disable();
	_dmatx.sourceBuffer(&_dma_pixel_buffer0[3], sizeof(_dma_pixel_buffer0)-3);
	_dmatx.destination(_pkinetisk_spi->PUSHR);
	_dmatx.TCD->ATTR_DST = 0;
	_dmatx.disableOnCompletion();
	_dmatx.interruptAtCompletion();
	_dmatx.attachInterrupt(dmaInterrupt);

	// SPI1/2 only have one dma_channel
	if (_spi_hardware->tx_dma_channel) {
		_dmatx.triggerAtHardwareEvent(_spi_hardware->tx_dma_channel);
	} else {
		_dmatx.triggerAtHardwareEvent(_spi_hardware->rx_dma_channel);
	}
#endif

	_dma_state = ILI9488_DMA_INIT;  // Should be first thing set!
	// Serial.println("DMA initDMASettings - end");

}
#endif

#ifdef DEBUG_ASYNC_UPDATE
void dumpDMA_TCD(DMABaseClass *dmabc)
{
	Serial.printf("%x %x:", (uint32_t)dmabc, (uint32_t)dmabc->TCD);

	Serial.printf("SA:%x SO:%d AT:%x NB:%x SL:%d DA:%x DO: %d CI:%x DL:%x CS:%x BI:%x\n", (uint32_t)dmabc->TCD->SADDR,
		dmabc->TCD->SOFF, dmabc->TCD->ATTR, dmabc->TCD->NBYTES, dmabc->TCD->SLAST, (uint32_t)dmabc->TCD->DADDR, 
		dmabc->TCD->DOFF, dmabc->TCD->CITER, dmabc->TCD->DLASTSGA, dmabc->TCD->CSR, dmabc->TCD->BITER);
}
#endif

void BMC_ILI9488_t3::dumpDMASettings() {
#ifdef DEBUG_ASYNC_UPDATE
#if defined(__MK66FX1M0__) 
	dumpDMA_TCD(&_dmatx);
	dumpDMA_TCD(&_dmasettings[0]);
	dumpDMA_TCD(&_dmasettings[1]);
	dumpDMA_TCD(&_dmasettings[2]);
#elif defined(__MK64FX512__)
	dumpDMA_TCD(&_dmatx);
//	dumpDMA_TCD(&_dmarx);
#elif defined(__IMXRT1052__) || defined(__IMXRT1062__)  // Teensy 4.x
	// Serial.printf("DMA dump TCDs %d\n", _dmatx.channel);
	dumpDMA_TCD(&_dmatx);
	dumpDMA_TCD(&_dmasettings[0]);
	dumpDMA_TCD(&_dmasettings[1]);
#else
#endif	
#endif

}

// Fill the pixel buffer with data... 
#if defined( ENABLE_ILI9488_FRAMEBUFFER) &&  !defined(ENABLE_EXT_DMA_UPDATES)
#if (defined(__IMXRT1052__) || defined(__IMXRT1062__) )  // Teensy 4.x

bool BMC_ILI9488_t3::fillDMApixelBuffer(uint32_t *dma_buffer_pointer)
{
	RAFB *frame_buffer_pixel_ptr = &_pfbtft[_dma_pixel_index];

	for (uint16_t i = 0; i < DMA_PIXELS_OUTPUT_PER_DMA; i++) {
		#ifdef ILI9488_USES_PALLET
		uint16_t color = _pallet[*frame_buffer_pixel_ptr++]; 	// extract the 16 bit color
		#else
		uint16_t color = *frame_buffer_pixel_ptr++; 	// extract the 16 bit color
		#endif
		uint32_t r = (color & 0xF800) >> 11;
		uint32_t g = (color & 0x07E0) >> 5;
		uint32_t b = color & 0x001F;

		r = (r * 255) / 31;
		g = (g * 255) / 63;
		b = (b * 255) / 31;
	
		*dma_buffer_pointer++ = (r << 16) | (g << 8) | b;
	}
	_dma_pixel_index += DMA_PIXELS_OUTPUT_PER_DMA;
	if (_dma_pixel_index >= (ILI9488_TFTHEIGHT*ILI9488_TFTWIDTH)) {
		_dma_pixel_index = 0;
		return true;
	}

	return false;
}

#else
// T3.x - Don't have 24/32 bit SPI transfers so output byte at a time...
bool BMC_ILI9488_t3::fillDMApixelBuffer(RAFB *dma_buffer_pointer)
{
	RAFB *frame_buffer_pixel_ptr = &_pfbtft[_dma_pixel_index];

	for (uint16_t i = 0; i < DMA_PIXELS_OUTPUT_PER_DMA; i++) {
		uint16_t color = _pallet[*frame_buffer_pixel_ptr++]; 	// extract the 16 bit color
		uint8_t r = (color & 0xF800) >> 11;
		uint8_t g = (color & 0x07E0) >> 5;
		uint8_t b = color & 0x001F;

		r = (r * 255) / 31;
		g = (g * 255) / 63;
		b = (b * 255) / 31;
	
		*dma_buffer_pointer++ = r;
		*dma_buffer_pointer++ = g;
		*dma_buffer_pointer++ = b;
	}
	_dma_pixel_index += DMA_PIXELS_OUTPUT_PER_DMA;
	if (_dma_pixel_index >= (ILI9488_TFTHEIGHT*ILI9488_TFTWIDTH)) {
		_dma_pixel_index = 0;
		return true;
	}

	return false;
}
#endif
#endif

bool BMC_ILI9488_t3::updateScreenAsync(bool update_cont)					// call to say update the screen now.
{
	// Not sure if better here to check flag or check existence of buffer.
	// Will go by buffer as maybe can do interesting things?
	// BUGBUG:: only handles full screen so bail on the rest of it...
#ifdef ENABLE_ILI9488_FRAMEBUFFER
	if (!_use_fbtft) return false;


#ifdef DEBUG_ASYNC_LEDS
	digitalWriteFast(DEBUG_PIN_1, HIGH);
#endif
	// Init DMA settings. 
	initDMASettings();

	// Don't start one if already active.
	if (_dma_state & ILI9488_DMA_ACTIVE) {
	#ifdef DEBUG_ASYNC_LEDS
		digitalWriteFast(DEBUG_PIN_1, LOW);
	#endif
		return false;
	}

#if !defined(__MK64FX512__)
	_dmatx = _dmasettings[0];
	_dmasettings[1].TCD->CSR &= ~( DMA_TCD_CSR_DREQ);  // Don't disable on completion.
#endif
	if (!update_cont) {
		// In this case we will only run through once...
		_dma_state &= ~ILI9488_DMA_CONT;
	}
#ifdef DEBUG_ASYNC_UPDATE
	Serial.println("dumpDMASettings called");
	dumpDMASettings();
#endif

	beginSPITransaction();
	// Doing full window. 
	// We need to convert the first page of colors.  Could/should hack up
	// some of the above code to allow this to be done while waiting for
	// the startup SPI output to finish. 
	_dma_pixel_index = 0;
	_dma_frame_count = 0;  // Set frame count back to zero. 
	_dma_sub_frame_count = 0;	
	

#if defined(__IMXRT1052__) || defined(__IMXRT1062__)  // Teensy 4.x
	//==========================================
	// T4
	//==========================================
	#if defined(ENABLE_EXT_DMA_UPDATES)
	// BUGBUG try first not worry about continueous or not.
  	// Start off remove disable on completion from both...
	// it will be the ISR that disables it... 
	if ((uint32_t)_pfbtft >= 0x20200000u)  arm_dcache_flush(_pfbtft, CBALLOC);

	_dmasettings[4].TCD->CSR &= ~( DMA_TCD_CSR_DREQ);
	setAddr(0, 0, _width-1, _height-1);
	writecommand_last(ILI9488_RAMWR);
	_spi_fcr_save = _pimxrt_spi->FCR;	// remember the FCR
	_pimxrt_spi->FCR = 0;	// clear water marks... 	
	maybeUpdateTCR(_tcr_dc_not_assert | LPSPI_TCR_FRAMESZ(23) | LPSPI_TCR_RXMSK /*| LPSPI_TCR_CONT*/);
 	_pimxrt_spi->DER = LPSPI_DER_TDDE;
	_pimxrt_spi->SR = 0x3f00;	// clear out all of the other status...

  	//_dmatx.triggerAtHardwareEvent(DMAMUX_SOURCE_LPSPI4_TX );

 	_dmatx = _dmasettings[0];

  	_dmatx.begin(false);
  	_dmatx.enable();

	_dmaActiveDisplay[_spi_num]  = this;
	if (update_cont) {
		_dma_state |= ILI9488_DMA_CONT;
	} else {
		_dma_state &= ~ILI9488_DMA_CONT;
		_dmasettings[4].disableOnCompletion();
	}

	_dma_state |= ILI9488_DMA_ACTIVE;
	#else
	//====================================
	setAddr(0, 0, _width-1, _height-1);
	fillDMApixelBuffer(_dma_pixel_buffer0);  // Fill the first buffer
	writecommand_last(ILI9488_RAMWR);

	// Update TCR to 16 bit mode. and output the first entry.
	_spi_fcr_save = _pimxrt_spi->FCR;	// remember the FCR
	_pimxrt_spi->FCR = 0;	// clear water marks... 	
	maybeUpdateTCR(_tcr_dc_not_assert | LPSPI_TCR_FRAMESZ(23) | LPSPI_TCR_RXMSK /*| LPSPI_TCR_CONT*/);
//	_pimxrt_spi->CFGR1 |= LPSPI_CFGR1_NOSTALL;
//	maybeUpdateTCR(_tcr_dc_not_assert | LPSPI_TCR_FRAMESZ(15) | LPSPI_TCR_CONT);
 	_pimxrt_spi->DER = LPSPI_DER_TDDE;
	_pimxrt_spi->SR = 0x3f00;	// clear out all of the other status...

  	//_dmatx.triggerAtHardwareEvent(DMAMUX_SOURCE_LPSPI4_TX );

 	_dmatx = _dmasettings[0];

  	_dmatx.begin(false);
  	_dmatx.enable();
	fillDMApixelBuffer(_dma_pixel_buffer1); 	// fill the second one

	_dmaActiveDisplay[_spi_num]  = this;
	if (update_cont) {
		_dma_state |= ILI9488_DMA_CONT;
	} else {
		_dma_state &= ~ILI9488_DMA_CONT;

	}

	_dma_state |= ILI9488_DMA_ACTIVE;
	#endif
#elif defined(__MK66FX1M0__) 
	//==========================================
	// T3.6
	//==========================================

	setAddr(0, 0, _width-1, _height-1);
	fillDMApixelBuffer(_dma_pixel_buffer0);  // Fill the first buffer
	writecommand_cont(ILI9488_RAMWR);

	// Write the first Word out before enter DMA as to setup the proper CS/DC/Continue flaugs
	// need to deal with first pixel... 
	write16BitColor(_pallet[*_pfbtft]);	
	_dma_frame_count = 0;  // Set frame count back to zero. 
	_dmaActiveDisplay = this;
	_dma_state |= ILI9488_DMA_ACTIVE;
	_pkinetisk_spi->RSER |= SPI_RSER_TFFF_DIRS |	 SPI_RSER_TFFF_RE;	 // Set DMA Interrupt Request Select and Enable register
	_pkinetisk_spi->MCR &= ~SPI_MCR_HALT;  //Start transfers.
	_dmatx.enable();
	fillDMApixelBuffer(_dma_pixel_buffer1); 	// fill the second one

	_dmaActiveDisplay = this;
	if (update_cont) {
		_dma_state |= ILI9488_DMA_CONT;
	} else {
		_dma_state &= ~ILI9488_DMA_CONT;

	}

	_dma_state |= ILI9488_DMA_ACTIVE;
#elif defined(__MK64FX512__)
	//==========================================
	// T3.5
	//==========================================

	setAddr(0, 0, _width-1, _height-1);
	fillDMApixelBuffer(_dma_pixel_buffer0);  // Fill the first buffer
	writecommand_cont(ILI9488_RAMWR);

	// Write the first Word out before enter DMA as to setup the proper CS/DC/Continue flaugs
	// need to deal with first pixel... 
	write16BitColor(_pallet[*_pfbtft]);	
	_dmatx.sourceBuffer(&_dma_pixel_buffer0[3], sizeof(_dma_pixel_buffer0)-3);
	_dma_frame_count = 0;  // Set frame count back to zero. 
	_dmaActiveDisplay = this;
	_dma_state |= ILI9488_DMA_ACTIVE;
	_pkinetisk_spi->RSER |= SPI_RSER_TFFF_DIRS | SPI_RSER_TFFF_RE;	 // Set DMA Interrupt Request Select and Enable register
	_pkinetisk_spi->MCR &= ~SPI_MCR_HALT;  //Start transfers.
  	//_dmatx.begin(false);
	_dmatx.enable();
	fillDMApixelBuffer(_dma_pixel_buffer1); 	// fill the second one

	_dmaActiveDisplay = this;
	if (update_cont) {
		_dma_state |= ILI9488_DMA_CONT;
	} else {
		_dma_state &= ~ILI9488_DMA_CONT;

	}

	_dma_state |= ILI9488_DMA_ACTIVE;
#endif	
#ifdef DEBUG_ASYNC_LEDS
	digitalWriteFast(DEBUG_PIN_1, LOW);
#endif


	return true;
    #else
    return false;     // no frame buffer so will never start... 
	#endif

}			 

void BMC_ILI9488_t3::endUpdateAsync() {
	// make sure it is on
	#ifdef ENABLE_ILI9488_FRAMEBUFFER
	if (_dma_state & ILI9488_DMA_CONT) {
		noInterrupts();
		_dma_state &= ~ILI9488_DMA_CONT; // Turn of the continueous mode
		interrupts();
		#if defined(ENABLE_EXT_DMA_UPDATES)
		_dmasettings[4].disableOnCompletion();
		#endif
	}
	#endif
}
	
void BMC_ILI9488_t3::waitUpdateAsyncComplete(void) 
{
	#ifdef ENABLE_ILI9488_FRAMEBUFFER
#ifdef DEBUG_ASYNC_LEDS
	digitalWriteFast(DEBUG_PIN_3, HIGH);
#endif

	while ((_dma_state & ILI9488_DMA_ACTIVE)) {
		// asm volatile("wfi");
	};
#ifdef DEBUG_ASYNC_LEDS
	digitalWriteFast(DEBUG_PIN_3, LOW);
#endif
	#endif	
}



	void BMC_ILI9488_t3::HLine(int16_t x, int16_t y, int16_t w, uint16_t color)
	 {
		#ifdef ENABLE_ILI9488_FRAMEBUFFER
	  	if (_use_fbtft) {
	  		drawFastHLine(x, y, w, color);
	  		return;
	  	}
	  	#endif
	    x+=_originx;
	    y+=_originy;

	    // Rectangular clipping
	    if((y < _displayclipy1) || (x >= _displayclipx2) || (y >= _displayclipy2)) return;
	    if(x<_displayclipx1) { w = w - (_displayclipx1 - x); x = _displayclipx1; }
	    if((x+w-1) >= _displayclipx2)  w = _displayclipx2-x;
	    if (w<1) return;

		setAddr(x, y, x+w-1, y);
		writecommand_cont(ILI9488_RAMWR);
		write16BitColor(color, w, false);
	}
	
	void BMC_ILI9488_t3::VLine(int16_t x, int16_t y, int16_t h, uint16_t color)
	 {
		#ifdef ENABLE_ILI9488_FRAMEBUFFER
	  	if (_use_fbtft) {
	  		drawFastVLine(x, y, h, color);
	  		return;
	  	}
	  	#endif
		x+=_originx;
	    y+=_originy;

	    // Rectangular clipping
	    if((x < _displayclipx1) || (x >= _displayclipx2) || (y >= _displayclipy2)) return;
	    if(y < _displayclipy1) { h = h - (_displayclipy1 - y); y = _displayclipy1;}
	    if((y+h-1) >= _displayclipy2) h = _displayclipy2-y;
	    if(h<1) return;

		setAddr(x, y, x, y+h-1);
		writecommand_cont(ILI9488_RAMWR);
		write16BitColor(color, h, false);
	}
	
	void BMC_ILI9488_t3::Pixel(int16_t x, int16_t y, uint16_t color)
	 {
	    x+=_originx;
	    y+=_originy;

	  	if((x < _displayclipx1) ||(x >= _displayclipx2) || (y < _displayclipy1) || (y >= _displayclipy2)) return;

		#ifdef ENABLE_ILI9488_FRAMEBUFFER
	  	if (_use_fbtft) {
	  		_pfbtft[y*_width + x] = mapColorToPalletIndex(color);
	  		return;
	  	}
	  	#endif
		setAddr(x, y, x, y);
		writecommand_cont(ILI9488_RAMWR);
		write16BitColor(color);
	}

#endif