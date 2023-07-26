// /**
// ** The FontStruction “Tiny3x3a”
// ** (https://fontstruct.com/fontstructions/show/670512) by “Michaelangel007” is
// ** licensed under a Creative Commons Attribution Non-commercial Share Alike
// *license
// ** (http://creativecommons.org/licenses/by-nc-sa/3.0/).
// ** “Tiny3x3a” was originally cloned (copied) from the FontStruction
// ** “CHECKER” (https://fontstruct.com/fontstructions/show/2391) by Wolf grant
// ** Grant, which is licensed under a Creative Commons Attribution Non-commercial
// ** Share Alike license (http://creativecommons.org/licenses/by-nc-sa/3.0/).
// *
// * Converted by eadmaster with fontconvert
// **/
// #ifndef BMC_DISPLAY_FONT
// #define BMC_DISPLAY_FONT



// // Created by http://oleddisplay.squix.ch/ Consider a donation
// // In case of problems make sure that you are using the font file with the correct version!
// const uint8_t BMCDisplay_FontBitmaps[] PROGMEM = {
//   0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x10, 0xC6, 0xB3, 0x84, 0x00, 0xFC,
//   0x0F, 0xC0, 0xFC, 0x00, 0x21, 0xCF, 0x88, 0x20, 0x80, 0x20, 0x82, 0x3E,
//   0x70, 0x80, 0x00, 0x86, 0x3F, 0x60, 0x80, 0x00, 0x41, 0xBF, 0x18, 0x40,
//   0x21, 0x8F, 0xD9, 0x24, 0x10, 0x40, 0x82, 0x09, 0x26, 0xFC, 0x61, 0x00,
//   0x38, 0xFB, 0xFF, 0xFF, 0xEF, 0x8E, 0x00, 0x00, 0x96, 0xFF, 0x6C, 0x90,
//   0x00, 0x02, 0x4D, 0xBF, 0xDA, 0x40, 0x00, 0x13, 0x7F, 0x73, 0x10, 0x8C,
//   0xEF, 0xEC, 0x80, 0x00, 0xFA, 0x00, 0xB6, 0x80, 0x52, 0xBE, 0xAF, 0xA9,
//   0x40, 0x23, 0xE8, 0xC3, 0x17, 0xC4, 0xC6, 0x44, 0x44, 0x4C, 0x60, 0x45,
//   0x28, 0x8A, 0xC9, 0xA0, 0x6D, 0x40, 0x2A, 0x48, 0x88, 0x00, 0x88, 0x92,
//   0xA0, 0x00, 0x22, 0xA7, 0x3E, 0x72, 0xA2, 0x00, 0x21, 0x3E, 0x42, 0x00,
//   0x66, 0x48, 0xF8, 0x00, 0xF0, 0x08, 0x88, 0x88, 0x00, 0x74, 0x67, 0x5C,
//   0xC5, 0xC0, 0x59, 0x24, 0xB8, 0x00, 0x74, 0x42, 0xE8, 0x43, 0xE0, 0xF8,
//   0x44, 0x60, 0xC5, 0xC0, 0x11, 0x95, 0x2F, 0x88, 0x40, 0xFC, 0x3C, 0x10,
//   0xC5, 0xC0, 0x3A, 0x21, 0xE8, 0xC5, 0xC0, 0xF8, 0x42, 0x22, 0x22, 0x00,
//   0x74, 0x62, 0xE8, 0xC5, 0xC0, 0x74, 0x62, 0xF0, 0x8B, 0x80, 0xA0, 0x45,
//   0x80, 0x12, 0x48, 0x42, 0x10, 0xF8, 0x3E, 0x00, 0x82, 0x08, 0x22, 0x22,
//   0x00, 0x74, 0x42, 0x62, 0x00, 0x80, 0x74, 0x6B, 0x7B, 0x41, 0xE0, 0x22,
//   0xA3, 0x1F, 0xC6, 0x20, 0xF4, 0x63, 0xE8, 0xC7, 0xC0, 0x74, 0x61, 0x08,
//   0x45, 0xC0, 0xF4, 0x63, 0x18, 0xC7, 0xC0, 0xFC, 0x21, 0xE8, 0x43, 0xE0,
//   0xFC, 0x21, 0xE8, 0x42, 0x00, 0x7C, 0x61, 0x09, 0xC5, 0xE0, 0x8C, 0x63,
//   0xF8, 0xC6, 0x20, 0xE9, 0x24, 0xB8, 0x00, 0x38, 0x84, 0x21, 0x49, 0x80,
//   0x8C, 0xA9, 0x8A, 0x4A, 0x20, 0x84, 0x21, 0x08, 0x43, 0xE0, 0x8E, 0xEB,
//   0x58, 0xC6, 0x20, 0x8C, 0x73, 0x59, 0xC6, 0x20, 0x74, 0x63, 0x18, 0xC5,
//   0xC0, 0xF4, 0x63, 0xE8, 0x42, 0x00, 0x74, 0x63, 0x1A, 0xC9, 0xA0, 0xF2,
//   0x28, 0xBC, 0xA2, 0x48, 0x80, 0x74, 0x60, 0xE0, 0xC5, 0xC0, 0xFA, 0xA2,
//   0x08, 0x20, 0x82, 0x00, 0x8C, 0x63, 0x18, 0xC5, 0xC0, 0x8C, 0x63, 0x18,
//   0xA8, 0x80, 0x8C, 0x63, 0x5A, 0xD5, 0x40, 0x8C, 0x54, 0x45, 0x46, 0x20,
//   0x8C, 0x54, 0x42, 0x10, 0x80, 0xF8, 0x44, 0xE4, 0x43, 0xE0, 0xCF, 0x88,
//   0x88, 0x8F, 0x04, 0x10, 0x41, 0x04, 0x00, 0xCF, 0x11, 0x11, 0x1F, 0x22,
//   0xA2, 0x00, 0xF8, 0x00, 0xD9, 0x10, 0x60, 0x9D, 0x27, 0x80, 0x04, 0x21,
//   0x6C, 0xC7, 0x36, 0x74, 0x61, 0x17, 0x00, 0x00, 0x42, 0xD9, 0xC6, 0x6D,
//   0x74, 0x7F, 0x07, 0x00, 0x02, 0x54, 0xE4, 0x44, 0x74, 0xE6, 0xD0, 0xB8,
//   0x00, 0x84, 0x2D, 0x98, 0xC6, 0x20, 0x02, 0x06, 0x22, 0x27, 0x10, 0x11,
//   0x19, 0x60, 0x08, 0x89, 0xAC, 0xA9, 0x62, 0x22, 0x22, 0x70, 0xD2, 0xAA,
//   0xAA, 0xA8, 0x00, 0xB6, 0x63, 0x18, 0x80, 0x74, 0x63, 0x17, 0x00, 0xB6,
//   0x73, 0x68, 0x40, 0x00, 0x6C, 0xE6, 0xD0, 0x84, 0x00, 0xB6, 0x61, 0x08,
//   0x00, 0x74, 0x1C, 0x1F, 0x00, 0x21, 0x3E, 0x42, 0x14, 0x40, 0x8C, 0x63,
//   0x36, 0x80, 0x8C, 0x62, 0xA2, 0x00, 0x8C, 0x6B, 0x55, 0x00, 0x8A, 0x88,
//   0xA8, 0x80, 0x8C, 0x5E, 0x18, 0xB8, 0x00, 0xF8, 0x88, 0x8F, 0x80, 0x29,
//   0x44, 0x88, 0x00, 0xEE, 0x00, 0x89, 0x14, 0xA0, 0x00
// };

// const GFXglyph BMCDisplay_FontGlyphs[] PROGMEM = {
//   {     0,   6,   6,   6,    0,   -7 },   // 0x12 'non-printable'
//   {     5,   6,   7,   6,    0,   -8 },   // 0x13 'non-printable'
//   {    11,   6,   5,   6,    0,   -7 },   // 0x14 'non-printable'
//   {    16,   6,   6,   6,    0,   -7 },   // 0x15 'non-printable'
//   {    21,   6,   6,   6,    0,   -7 },   // 0x16 'non-printable'
//   {    26,   6,   6,   6,    0,   -8 },   // 0x17 'non-printable'
//   {    31,   6,   6,   6,    0,   -8 },   // 0x18 'non-printable'
//   {    36,   6,   7,   6,    0,   -8 },   // 0x19 'non-printable'
//   {    42,   6,   7,   6,    0,   -8 },   // 0x1A 'non-printable'
//   {    48,   7,   7,   7,    0,   -8 },   // 0x1B 'non-printable'
//   {    55,   6,   7,   6,    0,   -8 },   // 0x1C 'non-printable'
//   {    61,   6,   7,   6,    0,   -8 },   // 0x1D 'non-printable'
//   {    67,   4,   7,   6,    1,   -8 },   // 0x1E 'non-printable'
//   {    71,   4,   7,   6,    1,   -8 },   // 0x1F 'non-printable'
//   {    75,   1,   1,   6,    0,   -2 },   // 0x20 ' '
//   {    76,   1,   7,   6,    2,   -8 },   // 0x21 '!'
//   {    78,   3,   3,   6,    0,   -8 },   // 0x22 '"'
//   {    80,   5,   7,   6,    0,   -8 },   // 0x23 '#'
//   {    85,   5,   8,   6,    0,   -8 },   // 0x24 '$'
//   {    90,   5,   7,   6,    0,   -8 },   // 0x25 '%'
//   {    95,   5,   7,   6,    0,   -8 },   // 0x26 '&'
//   {   100,   3,   4,   6,    1,   -8 },   // 0x27 '''
//   {   102,   3,   7,   6,    1,   -8 },   // 0x28 '('
//   {   106,   3,   7,   6,    1,   -8 },   // 0x29 ')'
//   {   110,   6,   7,   7,    0,   -8 },   // 0x2A '*'
//   {   116,   5,   5,   6,    0,   -7 },   // 0x2B '+'
//   {   120,   4,   4,   6,    1,   -4 },   // 0x2C ','
//   {   122,   5,   1,   6,    0,   -5 },   // 0x2D '-'
//   {   124,   2,   2,   6,    2,   -3 },   // 0x2E '.'
//   {   125,   5,   5,   6,    0,   -7 },   // 0x2F '/'
//   {   129,   5,   7,   6,    0,   -8 },   // 0x30 '0'
//   {   134,   3,   7,   6,    1,   -8 },   // 0x31 '1'
//   {   138,   5,   7,   6,    0,   -8 },   // 0x32 '2'
//   {   143,   5,   7,   6,    0,   -8 },   // 0x33 '3'
//   {   148,   5,   7,   6,    0,   -8 },   // 0x34 '4'
//   {   153,   5,   7,   6,    0,   -8 },   // 0x35 '5'
//   {   158,   5,   7,   6,    0,   -8 },   // 0x36 '6'
//   {   163,   5,   7,   6,    0,   -8 },   // 0x37 '7'
//   {   168,   5,   7,   6,    0,   -8 },   // 0x38 '8'
//   {   173,   5,   7,   6,    0,   -8 },   // 0x39 '9'
//   {   178,   1,   3,   6,    2,   -6 },   // 0x3A ':'
//   {   179,   2,   5,   6,    1,   -6 },   // 0x3B ';'
//   {   181,   4,   7,   6,    1,   -8 },   // 0x3C '<'
//   {   185,   5,   3,   6,    0,   -6 },   // 0x3D '='
//   {   188,   5,   7,   6,    1,   -8 },   // 0x3E '>'
//   {   193,   5,   7,   6,    0,   -8 },   // 0x3F '?'
//   {   198,   5,   7,   6,    0,   -8 },   // 0x40 '@'
//   {   203,   5,   7,   6,    0,   -8 },   // 0x41 'A'
//   {   208,   5,   7,   6,    0,   -8 },   // 0x42 'B'
//   {   213,   5,   7,   6,    0,   -8 },   // 0x43 'C'
//   {   218,   5,   7,   6,    0,   -8 },   // 0x44 'D'
//   {   223,   5,   7,   6,    0,   -8 },   // 0x45 'E'
//   {   228,   5,   7,   6,    0,   -8 },   // 0x46 'F'
//   {   233,   5,   7,   6,    0,   -8 },   // 0x47 'G'
//   {   238,   5,   7,   6,    0,   -8 },   // 0x48 'H'
//   {   243,   3,   7,   6,    1,   -8 },   // 0x49 'I'
//   {   247,   5,   7,   6,    0,   -8 },   // 0x4A 'J'
//   {   252,   5,   7,   6,    0,   -8 },   // 0x4B 'K'
//   {   257,   5,   7,   6,    0,   -8 },   // 0x4C 'L'
//   {   262,   5,   7,   6,    0,   -8 },   // 0x4D 'M'
//   {   267,   5,   7,   6,    0,   -8 },   // 0x4E 'N'
//   {   272,   5,   7,   6,    0,   -8 },   // 0x4F 'O'
//   {   277,   5,   7,   6,    0,   -8 },   // 0x50 'P'
//   {   282,   5,   7,   6,    0,   -8 },   // 0x51 'Q'
//   {   287,   6,   7,   6,    0,   -8 },   // 0x52 'R'
//   {   293,   5,   7,   6,    0,   -8 },   // 0x53 'S'
//   {   298,   6,   7,   6,    0,   -8 },   // 0x54 'T'
//   {   304,   5,   7,   6,    0,   -8 },   // 0x55 'U'
//   {   309,   5,   7,   6,    0,   -8 },   // 0x56 'V'
//   {   314,   5,   7,   6,    0,   -8 },   // 0x57 'W'
//   {   319,   5,   7,   6,    0,   -8 },   // 0x58 'X'
//   {   324,   5,   7,   6,    0,   -8 },   // 0x59 'Y'
//   {   329,   5,   7,   6,    0,   -8 },   // 0x5A 'Z'
//   {   334,   4,   8,   6,    1,   -9 },   // 0x5B '['
//   {   338,   5,   6,   6,    0,   -8 },   // 0x5C '\'
//   {   343,   4,   8,   6,    1,   -9 },   // 0x5D ']'
//   {   347,   5,   3,   6,    0,   -8 },   // 0x5E '^'
//   {   350,   5,   1,   6,    0,   -2 },   // 0x5F '_'
//   {   352,   3,   4,   6,    1,   -8 },   // 0x60 '`'
//   {   354,   5,   5,   6,    0,   -6 },   // 0x61 'a'
//   {   358,   5,   8,   6,    0,   -9 },   // 0x62 'b'
//   {   363,   5,   5,   6,    0,   -6 },   // 0x63 'c'
//   {   367,   5,   8,   6,    0,   -9 },   // 0x64 'd'
//   {   372,   5,   5,   6,    0,   -6 },   // 0x65 'e'
//   {   376,   4,   8,   6,    1,   -9 },   // 0x66 'f'
//   {   380,   5,   6,   6,    0,   -6 },   // 0x67 'g'
//   {   385,   5,   7,   6,    0,   -8 },   // 0x68 'h'
//   {   390,   4,   8,   6,    0,   -9 },   // 0x69 'i'
//   {   394,   4,   7,   6,    0,   -8 },   // 0x6A 'j'
//   {   398,   4,   8,   6,    0,   -9 },   // 0x6B 'k'
//   {   402,   4,   7,   6,    0,   -8 },   // 0x6C 'l'
//   {   406,   6,   5,   6,    0,   -6 },   // 0x6D 'm'
//   {   411,   5,   5,   6,    0,   -6 },   // 0x6E 'n'
//   {   415,   5,   5,   6,    0,   -6 },   // 0x6F 'o'
//   {   419,   5,   6,   6,    0,   -6 },   // 0x70 'p'
//   {   424,   5,   6,   6,    0,   -6 },   // 0x71 'q'
//   {   429,   5,   5,   6,    0,   -6 },   // 0x72 'r'
//   {   433,   5,   5,   6,    0,   -6 },   // 0x73 's'
//   {   437,   5,   7,   6,    0,   -8 },   // 0x74 't'
//   {   442,   5,   5,   6,    0,   -6 },   // 0x75 'u'
//   {   446,   5,   5,   6,    0,   -6 },   // 0x76 'v'
//   {   450,   5,   5,   6,    0,   -6 },   // 0x77 'w'
//   {   454,   5,   5,   6,    0,   -6 },   // 0x78 'x'
//   {   458,   5,   6,   6,    0,   -6 },   // 0x79 'y'
//   {   463,   5,   5,   6,    0,   -6 },   // 0x7A 'z'
//   {   467,   3,   7,   6,    1,   -8 },   // 0x7B '{'
//   {   471,   1,   7,   6,    2,   -8 },   // 0x7C '|'
//   {   473,   3,   7,   6,    1,   -8 }    // 0x7D '}'
// };

// const GFXfont BMCDisplay_Font PROGMEM = {
// (uint8_t  *)BMCDisplay_FontBitmaps,        (GFXglyph *)BMCDisplay_FontGlyphs, 0x12, 0x7E,         8};





// #endif