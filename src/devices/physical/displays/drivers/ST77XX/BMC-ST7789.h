#ifndef _BMC_ST7789H_
#define _BMC_ST7789H_

#include "utility/BMC-Def.h"

#if BMC_MAX_MINI_DISPLAY > 0

#include "devices/physical/displays/drivers/ST77XX/BMC-ST77xx.h"

/// Subclass of ST77XX type display for ST7789 TFT Driver
class BMC_ST7789 : public BMC_ST77xx {
public:
  BMC_ST7789(int8_t cs, int8_t dc, int8_t mosi, int8_t sclk,
                  int8_t rst = -1);
  BMC_ST7789(int8_t cs, int8_t dc, int8_t rst);
#if !defined(ESP8266)
  BMC_ST7789(SPIClass *spiClass, int8_t cs, int8_t dc, int8_t rst);
#endif // end !ESP8266

  void setRotation(uint8_t m);
  void init(uint16_t width, uint16_t height, uint8_t spiMode = SPI_MODE0);

protected:
  uint8_t _colstart2 = 0, ///< Offset from the right
      _rowstart2 = 0;     ///< Offset from the bottom

private:
  uint16_t windowWidth;
  uint16_t windowHeight;
};

#endif // _ADAFRUIT_ST7789H_

#endif