#ifndef BMC_GFX_FONTS_H
#define BMC_GFX_FONTS_H

#include <Adafruit_GFX.h>

// #include "display/fonts/bravo/BMCGFXFont10pt7b.h"
// #include "display/fonts/bravo/BMCGFXFont16pt7b.h"
// #include "display/fonts/bravo/BMCGFXFont24pt7b.h"
// #include "display/fonts/bravo/BMCGFXFont32pt7b.h"
// #include "display/fonts/bravo/BMCGFXFont40pt7b.h"
// #include "display/fonts/bravo/BMCGFXFont48pt7b.h"

// #include "display/fonts/liberation/BMCGFXFont10pt7b.h"
// #include "display/fonts/liberation/BMCGFXFont14pt7b.h"
// #include "display/fonts/liberation/BMCGFXFont16pt7b.h"
// #include "display/fonts/liberation/BMCGFXFont24pt7b.h"
// #include "display/fonts/liberation/BMCGFXFont32pt7b.h"
// #include "display/fonts/liberation/BMCGFXFont40pt7b.h"
// #include "display/fonts/liberation/BMCGFXFont48pt7b.h"

#include "display/fonts/fabiolo/BMCGFXFont10pt7b.h"
#include "display/fonts/fabiolo/BMCGFXFont14pt7b.h"
#include "display/fonts/fabiolo/BMCGFXFont16pt7b.h"
#include "display/fonts/fabiolo/BMCGFXFont24pt7b.h"
#include "display/fonts/fabiolo/BMCGFXFont32pt7b.h"
#include "display/fonts/fabiolo/BMCGFXFont40pt7b.h"
#include "display/fonts/fabiolo/BMCGFXFont48pt7b.h"


#define BMC_FONT_XXL         	 &BMCGFXFont48pt7b
#define BMC_FONT_XL          	 &BMCGFXFont40pt7b
#define BMC_FONT_LG          	 &BMCGFXFont32pt7b
#define BMC_FONT_MD          	 &BMCGFXFont24pt7b
#define BMC_FONT_SM          	 &BMCGFXFont16pt7b
#define BMC_FONT_XS          	 &BMCGFXFont10pt7b
#define BMC_FONT_DEFAULT     	 BMC_FONT_SM

#endif