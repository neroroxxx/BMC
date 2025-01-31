/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2024 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  This is the version stored in EEPROM.

  The CRC in EEPROM determines weather the EEPROM should be erased after
  uploading a new sketch, this version is intended for use by the editor
  for compatibility as new features are added/removed and/or patches are made.

  Anytime there's a change that requires the editor to read/write data in a new
  way then the minor version number will be changed.

  Anytime the EEPROM structure or any new feature that builds a new EEPROM
  structure then the Major version will be increased.

  However anytime we reach the maximum Minor version number (255) then the
  Major version will also be increased.
*/

// BMC Version stored in EEPROM (for editor usage)
#define BMC_VERSION_MAJ     2
#define BMC_VERSION_MIN     2
#define BMC_VERSION_PATCH   5

#define BMC_VERSION_STR "2.2.5"

//16 bits unsigned, LSB byte is minor, MSB byte is major
#define BMC_VERSION ((BMC_VERSION_MAJ<<8) | BMC_VERSION_MIN)
#define BMC_SEM_VERSION ((BMC_VERSION<<8) | BMC_VERSION_PATCH)
