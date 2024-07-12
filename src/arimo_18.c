/*******************************************************************************
 * Size: 18 px
 * Bpp: 2
 * Opts: 
 ******************************************************************************/

// #ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
// #else
// #include "lvgl/lvgl.h"
// #endif

#ifndef ARIMO_18
#define ARIMO_18 1
#endif

#if ARIMO_18

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0025 "%" */
    0xf, 0xc0, 0x3, 0x40, 0x34, 0xb0, 0xb, 0x0,
    0x30, 0x30, 0xc, 0x0, 0x70, 0x30, 0x38, 0x0,
    0x70, 0x30, 0x70, 0x0, 0x30, 0x30, 0xd2, 0xf0,
    0x34, 0xb2, 0x8e, 0x2c, 0x1f, 0xc7, 0xc, 0xc,
    0x0, 0xd, 0xc, 0xd, 0x0, 0x2c, 0xc, 0xd,
    0x0, 0x30, 0xc, 0xc, 0x0, 0xe0, 0xe, 0x1c,
    0x1, 0xc0, 0x3, 0xf0,

    /* U+002C "," */
    0x75, 0xd2, 0x4c, 0x10,

    /* U+002E "." */
    0x75, 0xd0,

    /* U+0030 "0" */
    0x3, 0xfc, 0x0, 0xf5, 0xf0, 0x2c, 0x3, 0x83,
    0x80, 0x2c, 0x34, 0x1, 0xc7, 0x40, 0x1d, 0x74,
    0x1, 0xd7, 0x40, 0x1d, 0x34, 0x1, 0xc3, 0x80,
    0x2c, 0x2c, 0x3, 0x80, 0xf5, 0xf0, 0x2, 0xf8,
    0x0,

    /* U+0031 "1" */
    0x3, 0xc0, 0x7, 0xf0, 0x7, 0x5c, 0x0, 0x7,
    0x0, 0x1, 0xc0, 0x0, 0x70, 0x0, 0x1c, 0x0,
    0x7, 0x0, 0x1, 0xc0, 0x0, 0x70, 0x0, 0x1c,
    0x0, 0x5b, 0x54, 0xbf, 0xff, 0x0,

    /* U+0032 "2" */
    0x6, 0xfd, 0x1, 0xf5, 0xf4, 0x3c, 0x3, 0xc1,
    0x40, 0x2c, 0x0, 0x3, 0x80, 0x0, 0x74, 0x0,
    0x1e, 0x0, 0xb, 0x80, 0x2, 0xd0, 0x0, 0xb4,
    0x0, 0x1d, 0x0, 0x3, 0xd5, 0x54, 0x3f, 0xff,
    0xc0,

    /* U+0033 "3" */
    0x7, 0xfd, 0x1, 0xe5, 0xf4, 0x3c, 0x3, 0xc1,
    0x40, 0x3c, 0x0, 0x3, 0x80, 0x0, 0xb0, 0x1,
    0xfc, 0x0, 0x5, 0xb4, 0x0, 0x2, 0xc1, 0x0,
    0x1c, 0x38, 0x2, 0xc2, 0xe5, 0xb8, 0x7, 0xfd,
    0x0,

    /* U+0034 "4" */
    0x0, 0xf, 0x0, 0x3, 0xf0, 0x0, 0xbf, 0x0,
    0xd, 0xf0, 0x3, 0x8f, 0x0, 0x70, 0xf0, 0xd,
    0xf, 0x2, 0xc0, 0xf0, 0x70, 0xf, 0xb, 0xff,
    0xfd, 0x0, 0xf, 0x0, 0x0, 0xf0, 0x0, 0xf,
    0x0,

    /* U+0035 "5" */
    0x2f, 0xff, 0x82, 0xd5, 0x50, 0x2c, 0x0, 0x2,
    0xc0, 0x0, 0x3c, 0x0, 0x3, 0xef, 0xd0, 0x3e,
    0x5b, 0x80, 0x0, 0x2c, 0x0, 0x1, 0xc0, 0x0,
    0x1c, 0x38, 0x3, 0xc2, 0xe5, 0xf4, 0x7, 0xfd,
    0x0,

    /* U+0036 "6" */
    0x2, 0xfd, 0x0, 0xb5, 0xb4, 0x1d, 0x3, 0x82,
    0xc0, 0x0, 0x38, 0x0, 0x3, 0x9f, 0xe0, 0x3e,
    0x5b, 0x83, 0xc0, 0x2c, 0x38, 0x1, 0xc3, 0xc0,
    0x1c, 0x1c, 0x3, 0xc0, 0xf5, 0xb4, 0x2, 0xfd,
    0x0,

    /* U+0037 "7" */
    0x3f, 0xff, 0xc1, 0x55, 0x7c, 0x0, 0x3, 0x40,
    0x0, 0xb0, 0x0, 0x1c, 0x0, 0x3, 0x80, 0x0,
    0x74, 0x0, 0xb, 0x0, 0x0, 0xe0, 0x0, 0x1d,
    0x0, 0x2, 0xc0, 0x0, 0x2c, 0x0, 0x3, 0xc0,
    0x0,

    /* U+0038 "8" */
    0x7, 0xfd, 0x1, 0xe1, 0xb4, 0x3c, 0x3, 0xc3,
    0xc0, 0x3c, 0x1d, 0x7, 0x40, 0x7f, 0xd0, 0x1e,
    0x5b, 0x43, 0x80, 0x2c, 0x34, 0x1, 0xc3, 0x40,
    0x1c, 0x3c, 0x2, 0xc1, 0xe5, 0xb4, 0x7, 0xfd,
    0x0,

    /* U+0039 "9" */
    0x7, 0xf8, 0x1, 0xf5, 0xf0, 0x3c, 0x3, 0x83,
    0x80, 0x2c, 0x34, 0x2, 0xc3, 0x80, 0x3c, 0x2e,
    0xb, 0xc0, 0xbf, 0xac, 0x0, 0x2, 0xc0, 0x0,
    0x3c, 0x2c, 0x7, 0x41, 0xe5, 0xf0, 0x7, 0xf8,
    0x0,

    /* U+0042 "B" */
    0xbf, 0xfe, 0x2, 0xd5, 0x6f, 0xb, 0x0, 0x2c,
    0x2c, 0x0, 0x74, 0xb0, 0x2, 0xc2, 0xc0, 0x1e,
    0xb, 0xff, 0xe0, 0x2d, 0x55, 0xf4, 0xb0, 0x0,
    0xf2, 0xc0, 0x2, 0xcb, 0x0, 0xf, 0x2d, 0x55,
    0xf4, 0xbf, 0xfe, 0x40,

    /* U+0043 "C" */
    0x0, 0xbf, 0xe0, 0x1, 0xf9, 0x6f, 0x0, 0xf0,
    0x0, 0xf0, 0xb4, 0x0, 0x14, 0x3c, 0x0, 0x0,
    0xe, 0x0, 0x0, 0x3, 0x80, 0x0, 0x0, 0xe0,
    0x0, 0x0, 0x3c, 0x0, 0x0, 0xb, 0x40, 0x1,
    0xc0, 0xf0, 0x1, 0xf0, 0xf, 0x96, 0xf0, 0x0,
    0xbf, 0xd0, 0x0,

    /* U+0044 "D" */
    0xbf, 0xfe, 0x0, 0xb5, 0x5b, 0xd0, 0xb0, 0x0,
    0xf0, 0xb0, 0x0, 0x38, 0xb0, 0x0, 0x3c, 0xb0,
    0x0, 0x2c, 0xb0, 0x0, 0x2c, 0xb0, 0x0, 0x2c,
    0xb0, 0x0, 0x3c, 0xb0, 0x0, 0x78, 0xb0, 0x0,
    0xf0, 0xb5, 0x5b, 0xc0, 0xbf, 0xfe, 0x0,

    /* U+0045 "E" */
    0xbf, 0xff, 0xf2, 0xe5, 0x55, 0x4b, 0x0, 0x0,
    0x2c, 0x0, 0x0, 0xb0, 0x0, 0x2, 0xc0, 0x0,
    0xb, 0xff, 0xfd, 0x2d, 0x55, 0x50, 0xb0, 0x0,
    0x2, 0xc0, 0x0, 0xb, 0x0, 0x0, 0x2e, 0x55,
    0x54, 0xbf, 0xff, 0xf0,

    /* U+0046 "F" */
    0xbf, 0xff, 0xdb, 0x95, 0x54, 0xb0, 0x0, 0xb,
    0x0, 0x0, 0xb0, 0x0, 0xb, 0x0, 0x0, 0xb4,
    0x0, 0xb, 0xff, 0xfc, 0xb5, 0x55, 0x4b, 0x0,
    0x0, 0xb0, 0x0, 0xb, 0x0, 0x0, 0xb0, 0x0,
    0x0,

    /* U+0047 "G" */
    0x0, 0xbf, 0xe0, 0x1, 0xf9, 0x6f, 0x40, 0xf0,
    0x0, 0xf0, 0xb0, 0x0, 0x4, 0x3c, 0x0, 0x0,
    0xe, 0x0, 0x0, 0x3, 0x80, 0x0, 0x0, 0xe0,
    0xb, 0xfe, 0x3c, 0x0, 0x57, 0x8b, 0x40, 0x0,
    0xe0, 0xf0, 0x0, 0x38, 0xf, 0x96, 0xfc, 0x0,
    0xbf, 0xe4, 0x0,

    /* U+0048 "H" */
    0xb0, 0x0, 0x3a, 0xc0, 0x0, 0xeb, 0x0, 0x3,
    0xac, 0x0, 0xe, 0xb0, 0x0, 0x3a, 0xd0, 0x1,
    0xeb, 0xff, 0xff, 0xad, 0x55, 0x5e, 0xb0, 0x0,
    0x3a, 0xc0, 0x0, 0xeb, 0x0, 0x3, 0xac, 0x0,
    0xe, 0xb0, 0x0, 0x38,

    /* U+0049 "I" */
    0x75, 0xd7, 0x5d, 0x75, 0xd7, 0x5d, 0x75, 0xd7,
    0x5d, 0x74,

    /* U+004A "J" */
    0x1, 0xfe, 0x0, 0x5e, 0x0, 0xe, 0x0, 0xe,
    0x0, 0xe, 0x0, 0xe, 0x0, 0xe, 0x0, 0xe,
    0x0, 0xe, 0x60, 0xe, 0x74, 0x1d, 0x3e, 0x7c,
    0xb, 0xe0,

    /* U+004B "K" */
    0xb0, 0x1, 0xe2, 0xc0, 0x1e, 0xb, 0x0, 0xe0,
    0x2c, 0xf, 0x0, 0xb0, 0xf0, 0x2, 0xcf, 0x0,
    0xb, 0xfe, 0x0, 0x2e, 0x2d, 0x0, 0xb0, 0x3c,
    0x2, 0xc0, 0x3c, 0xb, 0x0, 0x7c, 0x2c, 0x0,
    0x78, 0xb0, 0x0, 0xb4,

    /* U+004C "L" */
    0xb0, 0x0, 0x2c, 0x0, 0xb, 0x0, 0x2, 0xc0,
    0x0, 0xb0, 0x0, 0x2c, 0x0, 0xb, 0x0, 0x2,
    0xc0, 0x0, 0xb0, 0x0, 0x2c, 0x0, 0xb, 0x0,
    0x2, 0xe5, 0x54, 0xbf, 0xff, 0x40,

    /* U+004D "M" */
    0xbc, 0x0, 0xf, 0xaf, 0x0, 0x3, 0xeb, 0xe0,
    0x2, 0xfa, 0xec, 0x0, 0xee, 0xb3, 0x40, 0x73,
    0xac, 0xe0, 0x2c, 0xeb, 0x1c, 0xd, 0x3a, 0xc3,
    0x47, 0xe, 0xb0, 0xb2, 0x83, 0xac, 0x1c, 0xd0,
    0xeb, 0x3, 0xb0, 0x3a, 0xc0, 0xb8, 0xe, 0xb0,
    0x1d, 0x3, 0x80,

    /* U+004E "N" */
    0xb8, 0x0, 0x3a, 0xf4, 0x0, 0xeb, 0xf0, 0x3,
    0xac, 0xe0, 0xe, 0xb2, 0xc0, 0x3a, 0xc3, 0x80,
    0xeb, 0x7, 0x43, 0xac, 0xf, 0xe, 0xb0, 0xe,
    0x3a, 0xc0, 0x2c, 0xeb, 0x0, 0x3b, 0xac, 0x0,
    0x7e, 0xb0, 0x0, 0xf8,

    /* U+004F "O" */
    0x0, 0xbf, 0xe0, 0x0, 0x7e, 0x5b, 0xd0, 0xf,
    0x0, 0xf, 0x2, 0xc0, 0x0, 0x38, 0x3c, 0x0,
    0x3, 0xc3, 0x80, 0x0, 0x2c, 0x38, 0x0, 0x2,
    0xc3, 0x80, 0x0, 0x2c, 0x3c, 0x0, 0x3, 0xc2,
    0xd0, 0x0, 0x38, 0xf, 0x0, 0xf, 0x0, 0x7e,
    0x5b, 0xc0, 0x0, 0xbf, 0xe0, 0x0,

    /* U+0050 "P" */
    0xbf, 0xfe, 0x2, 0xd5, 0x6f, 0x4b, 0x0, 0xf,
    0x2c, 0x0, 0x2c, 0xb0, 0x0, 0xb2, 0xc0, 0x3,
    0xcb, 0x0, 0x2d, 0x2f, 0xff, 0xd0, 0xb5, 0x50,
    0x2, 0xc0, 0x0, 0xb, 0x0, 0x0, 0x2c, 0x0,
    0x0, 0xb0, 0x0, 0x0,

    /* U+0051 "Q" */
    0x0, 0xbf, 0xe0, 0x0, 0x7e, 0x5b, 0xd0, 0xf,
    0x0, 0xf, 0x2, 0xc0, 0x0, 0x38, 0x3c, 0x0,
    0x3, 0xc3, 0x80, 0x0, 0x2c, 0x38, 0x0, 0x2,
    0xc3, 0x80, 0x0, 0x2c, 0x3c, 0x0, 0x3, 0xc2,
    0xc0, 0x0, 0x38, 0xf, 0x0, 0xf, 0x0, 0x7e,
    0x5b, 0xd0, 0x0, 0xbf, 0xe0, 0x0, 0x0, 0x74,
    0x0, 0x0, 0x3, 0x80, 0x0, 0x0, 0x2e, 0x40,
    0x0, 0x0, 0xbe, 0x0,

    /* U+0052 "R" */
    0xbf, 0xff, 0x80, 0xb5, 0x56, 0xf0, 0xb0, 0x0,
    0x78, 0xb0, 0x0, 0x38, 0xb0, 0x0, 0x38, 0xb0,
    0x1, 0xf0, 0xbf, 0xff, 0xc0, 0xb5, 0x5f, 0x0,
    0xb0, 0x7, 0x80, 0xb0, 0x2, 0xc0, 0xb0, 0x0,
    0xe0, 0xb0, 0x0, 0xb4, 0xb0, 0x0, 0x3c,

    /* U+0053 "S" */
    0x2, 0xff, 0x80, 0xf, 0x95, 0xf0, 0x1c, 0x0,
    0x38, 0x2c, 0x0, 0x0, 0x1e, 0x0, 0x0, 0xb,
    0xe4, 0x0, 0x1, 0xbf, 0xd0, 0x0, 0x1, 0xf8,
    0x0, 0x0, 0x2c, 0x14, 0x0, 0x2c, 0x3c, 0x0,
    0x3c, 0x1f, 0x96, 0xf4, 0x2, 0xff, 0x80,

    /* U+0054 "T" */
    0xbf, 0xff, 0xf8, 0x56, 0xe5, 0x40, 0x7, 0x40,
    0x0, 0x1d, 0x0, 0x0, 0x74, 0x0, 0x1, 0xd0,
    0x0, 0x7, 0x40, 0x0, 0x1d, 0x0, 0x0, 0x74,
    0x0, 0x1, 0xd0, 0x0, 0x7, 0x40, 0x0, 0x1d,
    0x0, 0x0, 0x74, 0x0,

    /* U+0055 "U" */
    0xb0, 0x0, 0x3a, 0xc0, 0x0, 0xeb, 0x0, 0x3,
    0xac, 0x0, 0xe, 0xb0, 0x0, 0x3a, 0xc0, 0x0,
    0xeb, 0x0, 0x3, 0xac, 0x0, 0xe, 0xb0, 0x0,
    0x39, 0xd0, 0x1, 0xd3, 0xc0, 0xf, 0x7, 0xe6,
    0xf4, 0x2, 0xfe, 0x0,

    /* U+0056 "V" */
    0xb0, 0x0, 0xe, 0x74, 0x0, 0x1d, 0x3c, 0x0,
    0x3c, 0x2c, 0x0, 0x38, 0xe, 0x0, 0xb0, 0xf,
    0x0, 0xf0, 0x7, 0x41, 0xd0, 0x3, 0x82, 0xc0,
    0x2, 0xc3, 0x80, 0x0, 0xd7, 0x0, 0x0, 0xeb,
    0x0, 0x0, 0x7d, 0x0, 0x0, 0x3c, 0x0,

    /* U+0057 "W" */
    0xf0, 0x1, 0xd0, 0x3, 0xec, 0x0, 0xb8, 0x0,
    0xe3, 0x40, 0x3f, 0x0, 0x70, 0xf0, 0xd, 0xc0,
    0x3c, 0x2c, 0x7, 0x38, 0xe, 0x7, 0x43, 0x8b,
    0x7, 0x40, 0xe0, 0xd1, 0xc2, 0xc0, 0x3c, 0x70,
    0x34, 0xf0, 0xb, 0x2c, 0xe, 0x38, 0x1, 0xde,
    0x2, 0xdd, 0x0, 0x3b, 0x40, 0x7b, 0x0, 0xb,
    0xc0, 0xf, 0x80, 0x1, 0xf0, 0x3, 0xd0, 0x0,

    /* U+0058 "X" */
    0x3c, 0x0, 0x3c, 0xe, 0x0, 0xb0, 0x7, 0x40,
    0xe0, 0x3, 0xc3, 0xc0, 0x0, 0xeb, 0x0, 0x0,
    0x7e, 0x0, 0x0, 0x3d, 0x0, 0x0, 0xff, 0x0,
    0x1, 0xd3, 0x80, 0x3, 0x82, 0xd0, 0xf, 0x0,
    0xf0, 0x2d, 0x0, 0x38, 0x78, 0x0, 0x2d,

    /* U+0059 "Y" */
    0x78, 0x0, 0x2d, 0x2c, 0x0, 0x38, 0xf, 0x0,
    0xb0, 0x7, 0x41, 0xd0, 0x3, 0xc3, 0xc0, 0x0,
    0xeb, 0x0, 0x0, 0xbe, 0x0, 0x0, 0x3c, 0x0,
    0x0, 0x3c, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x3c,
    0x0, 0x0, 0x3c, 0x0, 0x0, 0x3c, 0x0,

    /* U+005A "Z" */
    0x3f, 0xff, 0xf0, 0x55, 0x57, 0xc0, 0x0, 0x2c,
    0x0, 0x1, 0xd0, 0x0, 0xe, 0x0, 0x0, 0xf0,
    0x0, 0xb, 0x0, 0x0, 0x74, 0x0, 0x3, 0x80,
    0x0, 0x3c, 0x0, 0x2, 0xd0, 0x0, 0xf, 0x55,
    0x54, 0x7f, 0xff, 0xf4,

    /* U+0061 "a" */
    0x7, 0xfd, 0x0, 0x79, 0x7c, 0x2, 0x80, 0x38,
    0x0, 0x0, 0xe0, 0xb, 0xff, 0x80, 0xf4, 0xe,
    0x3, 0x80, 0x38, 0xd, 0x2, 0xe0, 0x3d, 0x2b,
    0xc0, 0x7f, 0x87, 0xc0,

    /* U+0062 "b" */
    0xf0, 0x0, 0x3c, 0x0, 0xf, 0x0, 0x3, 0xdf,
    0xe0, 0xfd, 0x6e, 0x3d, 0x3, 0xcf, 0x0, 0xb3,
    0xc0, 0x1c, 0xf0, 0x7, 0x3c, 0x2, 0xcf, 0x0,
    0xf3, 0xf4, 0xb8, 0xe7, 0xf8, 0x0,

    /* U+0063 "c" */
    0x7, 0xf8, 0x7, 0x97, 0xc3, 0xc0, 0x74, 0xe0,
    0x0, 0x34, 0x0, 0xd, 0x0, 0x3, 0x80, 0x0,
    0xf0, 0x1d, 0x1e, 0x5f, 0x1, 0xfe, 0x0,

    /* U+0064 "d" */
    0x0, 0x3, 0xc0, 0x0, 0xf0, 0x0, 0x3c, 0x2f,
    0xdf, 0x2e, 0x1f, 0xcf, 0x0, 0xf3, 0x80, 0x3c,
    0xd0, 0xf, 0x34, 0x3, 0xce, 0x0, 0xf3, 0xc0,
    0x7c, 0xb9, 0x7f, 0xb, 0xf6, 0xc0,

    /* U+0065 "e" */
    0x7, 0xfd, 0x1, 0xe5, 0xb4, 0x3c, 0x3, 0xc3,
    0x80, 0x2c, 0x3f, 0xff, 0xc3, 0x80, 0x0, 0x38,
    0x0, 0x3, 0xc0, 0x14, 0x1f, 0x5b, 0x40, 0x7f,
    0xd0,

    /* U+0066 "f" */
    0xb, 0xc1, 0xe4, 0x1c, 0xf, 0xfc, 0x2d, 0x1,
    0xc0, 0x1c, 0x1, 0xc0, 0x1c, 0x1, 0xc0, 0x1c,
    0x1, 0xc0, 0x1c, 0x0,

    /* U+0067 "g" */
    0xb, 0xf2, 0xcb, 0x97, 0xf3, 0xc0, 0x7c, 0xe0,
    0xf, 0x34, 0x3, 0xcd, 0x0, 0xf3, 0x40, 0x3c,
    0xe0, 0x1f, 0x2e, 0x1f, 0xc2, 0xf8, 0xf0, 0x0,
    0x3c, 0x60, 0xe, 0x1e, 0x5f, 0x1, 0xfe, 0x0,

    /* U+0068 "h" */
    0xf0, 0x0, 0xf0, 0x0, 0xf0, 0x0, 0xf3, 0xf8,
    0xfd, 0x6d, 0xf0, 0xf, 0xf0, 0xf, 0xf0, 0xf,
    0xf0, 0xf, 0xf0, 0xf, 0xf0, 0xf, 0xf0, 0xf,
    0xf0, 0xf,

    /* U+0069 "i" */
    0xf5, 0xf, 0xff, 0xff, 0xff, 0xff, 0xf0,

    /* U+006A "j" */
    0xf, 0x5, 0x0, 0xf, 0xf, 0xf, 0xf, 0xf,
    0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0x1e,
    0x7c,

    /* U+006B "k" */
    0xf0, 0x0, 0x3c, 0x0, 0xf, 0x0, 0x3, 0xc0,
    0x74, 0xf0, 0x74, 0x3c, 0x38, 0xf, 0x38, 0x3,
    0xfc, 0x0, 0xff, 0xc0, 0x3c, 0x78, 0xf, 0xb,
    0x43, 0xc0, 0xf0, 0xf0, 0xe, 0x0,

    /* U+006C "l" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,

    /* U+006D "m" */
    0xe7, 0xf4, 0xbe, 0x3e, 0xf, 0x91, 0xef, 0x1,
    0xe0, 0x3f, 0xc0, 0x74, 0xf, 0xf0, 0x1d, 0x3,
    0xfc, 0x7, 0x40, 0xff, 0x1, 0xd0, 0x3f, 0xc0,
    0x74, 0xf, 0xf0, 0x1d, 0x3, 0xfc, 0x7, 0x40,
    0xf0,

    /* U+006E "n" */
    0xe3, 0xf8, 0xfc, 0x1d, 0xf0, 0xf, 0xf0, 0xf,
    0xf0, 0xf, 0xf0, 0xf, 0xf0, 0xf, 0xf0, 0xf,
    0xf0, 0xf, 0xf0, 0xf,

    /* U+006F "o" */
    0x7, 0xfd, 0x1, 0xe5, 0xb4, 0x3c, 0x3, 0xc3,
    0x80, 0x2c, 0x34, 0x1, 0xc3, 0x40, 0x1c, 0x38,
    0x2, 0xc3, 0xc0, 0x3c, 0x1e, 0x5b, 0x40, 0x7f,
    0xd0,

    /* U+0070 "p" */
    0xe7, 0xf8, 0x3f, 0x7, 0x8f, 0x0, 0xb3, 0xc0,
    0x1c, 0xf0, 0x7, 0x3c, 0x1, 0xcf, 0x0, 0xb3,
    0xc0, 0x3c, 0xfd, 0x2e, 0x3d, 0xfe, 0xf, 0x0,
    0x3, 0xc0, 0x0, 0xf0, 0x0, 0x3c, 0x0, 0x0,

    /* U+0071 "q" */
    0xb, 0xf6, 0xcb, 0x87, 0xf3, 0xc0, 0x3c, 0xe0,
    0xf, 0x34, 0x3, 0xcd, 0x0, 0xf3, 0x80, 0x3c,
    0xf0, 0x1f, 0x2e, 0x5f, 0xc2, 0xfd, 0xf0, 0x0,
    0x3c, 0x0, 0xf, 0x0, 0x3, 0xc0, 0x0, 0xf0,

    /* U+0072 "r" */
    0x0, 0x39, 0xef, 0xd3, 0xc0, 0xf0, 0x3c, 0xf,
    0x3, 0xc0, 0xf0, 0x3c, 0xf, 0x0,

    /* U+0073 "s" */
    0xb, 0xf8, 0xf, 0x47, 0xc3, 0x40, 0x10, 0xf0,
    0x0, 0x1f, 0xe4, 0x0, 0x6f, 0x80, 0x0, 0x74,
    0x80, 0xd, 0x3d, 0x5f, 0x2, 0xfe, 0x0,

    /* U+0074 "t" */
    0xc, 0x7, 0xb, 0xf8, 0xb0, 0x2c, 0xb, 0x2,
    0xc0, 0xb0, 0x2c, 0xb, 0x2, 0xd4, 0x3f,

    /* U+0075 "u" */
    0xf0, 0xf, 0xf0, 0xf, 0xf0, 0xf, 0xf0, 0xf,
    0xf0, 0xf, 0xf0, 0xf, 0xf0, 0xf, 0xf0, 0xf,
    0xb9, 0x7f, 0x2f, 0xcb,

    /* U+0076 "v" */
    0xf0, 0x3, 0xdc, 0x0, 0xd3, 0x80, 0xb0, 0xb0,
    0x38, 0x1c, 0xd, 0x3, 0x8b, 0x0, 0xb3, 0x80,
    0x1d, 0xd0, 0x3, 0xf0, 0x0, 0xb8, 0x0,

    /* U+0077 "w" */
    0x38, 0x7, 0x40, 0xb0, 0xb0, 0x2e, 0x3, 0x81,
    0xc0, 0xec, 0xd, 0x3, 0x43, 0x30, 0x70, 0xe,
    0x1c, 0xd2, 0xc0, 0x2c, 0xa2, 0x8e, 0x0, 0x73,
    0x47, 0x34, 0x0, 0xec, 0xe, 0xc0, 0x3, 0xf0,
    0x3e, 0x0, 0x7, 0x80, 0xb4, 0x0,

    /* U+0078 "x" */
    0x74, 0x7, 0x4b, 0x3, 0x80, 0xe2, 0xc0, 0x1e,
    0xd0, 0x2, 0xe0, 0x0, 0xfc, 0x0, 0x77, 0x40,
    0x38, 0xb0, 0x3c, 0xf, 0x1c, 0x1, 0xd0,

    /* U+0079 "y" */
    0xf0, 0x3, 0xdd, 0x0, 0xd3, 0x80, 0xb0, 0xb0,
    0x38, 0x1d, 0xd, 0x3, 0x87, 0x0, 0xb3, 0x80,
    0xe, 0xc0, 0x3, 0xf0, 0x0, 0x78, 0x0, 0x1c,
    0x0, 0xe, 0x0, 0x1b, 0x0, 0x1f, 0x40, 0x0,

    /* U+007A "z" */
    0x3f, 0xff, 0x1, 0x57, 0x80, 0x3, 0xc0, 0x2,
    0xd0, 0x1, 0xe0, 0x0, 0xf0, 0x0, 0xb0, 0x0,
    0x74, 0x0, 0x3d, 0x55, 0x1f, 0xff, 0xc0,

    /* U+2103 "℃" */
    0x5, 0x0, 0x5, 0x50, 0x7, 0x68, 0xb, 0xff,
    0xe0, 0xc0, 0xc3, 0xd0, 0xb, 0x8c, 0xc, 0xb4,
    0x0, 0x28, 0x3b, 0x4f, 0x0, 0x0, 0x0, 0x0,
    0xe0, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x0,
    0x0, 0xe0, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0,
    0x0, 0x0, 0xf0, 0x0, 0x18, 0x0, 0x7, 0xc0,
    0x3, 0xc0, 0x0, 0x2f, 0x46, 0xf0, 0x0, 0x0,
    0x7f, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 80, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 256, .box_w = 16, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 56, .adv_w = 80, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 160, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 91, .adv_w = 160, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 121, .adv_w = 160, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 160, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 160, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 160, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 253, .adv_w = 160, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 160, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 160, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 160, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 192, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 421, .adv_w = 208, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 464, .adv_w = 208, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 503, .adv_w = 192, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 539, .adv_w = 176, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 572, .adv_w = 224, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 615, .adv_w = 208, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 651, .adv_w = 80, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 661, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 687, .adv_w = 192, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 723, .adv_w = 160, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 753, .adv_w = 240, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 796, .adv_w = 208, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 832, .adv_w = 224, .box_w = 14, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 878, .adv_w = 192, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 914, .adv_w = 224, .box_w = 14, .box_h = 17, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 974, .adv_w = 208, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1013, .adv_w = 192, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1052, .adv_w = 176, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1088, .adv_w = 208, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1124, .adv_w = 192, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1163, .adv_w = 272, .box_w = 17, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1219, .adv_w = 192, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1258, .adv_w = 192, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1297, .adv_w = 176, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1333, .adv_w = 160, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1361, .adv_w = 160, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1391, .adv_w = 144, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1414, .adv_w = 160, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1444, .adv_w = 160, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1469, .adv_w = 80, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1489, .adv_w = 160, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1521, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1547, .adv_w = 64, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1554, .adv_w = 64, .box_w = 4, .box_h = 17, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 1571, .adv_w = 144, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1601, .adv_w = 64, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1608, .adv_w = 240, .box_w = 13, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1641, .adv_w = 160, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1661, .adv_w = 160, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1686, .adv_w = 160, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1718, .adv_w = 160, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1750, .adv_w = 96, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1764, .adv_w = 144, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1787, .adv_w = 80, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1802, .adv_w = 160, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1822, .adv_w = 144, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1845, .adv_w = 208, .box_w = 15, .box_h = 10, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1883, .adv_w = 144, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1906, .adv_w = 144, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1938, .adv_w = 144, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1961, .adv_w = 302, .box_w = 18, .box_h = 14, .ofs_x = 1, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x5, 0xc, 0xe
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 15, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 4, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 48, .range_length = 10, .glyph_id_start = 5,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 66, .range_length = 25, .glyph_id_start = 15,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 97, .range_length = 26, .glyph_id_start = 40,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 8451, .range_length = 1, .glyph_id_start = 66,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    1, 33,
    1, 38,
    6, 6,
    19, 3,
    19, 4,
    25, 1,
    25, 33,
    25, 35,
    25, 36,
    25, 38,
    25, 64,
    29, 1,
    29, 3,
    29, 4,
    31, 33,
    31, 35,
    31, 36,
    31, 38,
    33, 1,
    33, 3,
    33, 4,
    33, 28,
    33, 40,
    33, 42,
    33, 44,
    33, 48,
    33, 54,
    33, 57,
    33, 58,
    33, 60,
    33, 62,
    33, 64,
    35, 3,
    35, 4,
    35, 40,
    35, 44,
    35, 48,
    35, 54,
    35, 57,
    35, 60,
    35, 64,
    36, 3,
    36, 4,
    36, 40,
    36, 44,
    36, 54,
    36, 57,
    36, 60,
    36, 64,
    38, 1,
    38, 3,
    38, 4,
    38, 40,
    38, 44,
    38, 48,
    38, 54,
    38, 55,
    38, 56,
    38, 60,
    38, 61,
    45, 45,
    57, 3,
    57, 4,
    61, 3,
    61, 4,
    62, 3,
    62, 4,
    64, 3,
    64, 4
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -5, -5, -21, -32, -32, -11, -21, -21,
    -21, -21, -11, -5, -37, -37, -5, -5,
    -5, -5, -5, -32, -32, -5, -32, -32,
    -32, -11, -32, -11, -32, -11, -16, -16,
    -26, -26, -21, -16, -5, -16, -11, -11,
    -11, -16, -16, -11, -5, -5, -5, -5,
    -3, -5, -37, -37, -21, -26, -11, -26,
    -21, -26, -16, -16, -5, -16, -16, -21,
    -21, -16, -16, -21, -21
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 69,
    .glyph_ids_size = 0
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 5,
    .bpp = 2,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t arimo_18 = {
#else
lv_font_t arimo_18 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 17,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if ARIMO_18*/

