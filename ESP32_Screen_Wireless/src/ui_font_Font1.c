/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --bpp 1 --size 12 --font C:/Users/ADMIN/SquareLine/assets/Open 24 Display St.ttf -o C:/Users/ADMIN/SquareLine/assets\ui_font_Font1.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "ui.h"

#ifndef UI_FONT_FONT1
#define UI_FONT_FONT1 1
#endif

#if UI_FONT_FONT1

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfd, 0x80,

    /* U+0022 "\"" */
    0xf0,

    /* U+0023 "#" */
    0x0, 0x0, 0x64, 0x4, 0x43, 0x33, 0x8, 0x80,
    0x88, 0x77, 0x41, 0x10, 0x22, 0x2, 0x20,

    /* U+0024 "$" */
    0x21, 0x3d, 0x4a, 0x43, 0xc5, 0x28, 0x5c, 0x40,

    /* U+0025 "%" */
    0x8e, 0xc4, 0x42, 0x21, 0x1a, 0x88,

    /* U+0026 "&" */
    0x61, 0x45, 0x18, 0x72, 0x79, 0x27, 0x70,

    /* U+0027 "'" */
    0xc0,

    /* U+0028 "(" */
    0x72, 0x49, 0x24, 0x60,

    /* U+0029 ")" */
    0xc4, 0x92, 0x49, 0xc0,

    /* U+002A "*" */
    0x77, 0x9c, 0x40,

    /* U+002B "+" */
    0x21, 0x8, 0xe2, 0x10, 0x80,

    /* U+002C "," */
    0xc0,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x8, 0x84, 0x42, 0x21, 0x10, 0x80,

    /* U+0030 "0" */
    0x7c, 0x63, 0x52, 0x56, 0x31, 0x70,

    /* U+0031 "1" */
    0x2e, 0x90, 0x49, 0x20,

    /* U+0032 "2" */
    0x70, 0x42, 0x1f, 0x42, 0x10, 0x70,

    /* U+0033 "3" */
    0xe1, 0x11, 0xf1, 0x11, 0xe0,

    /* U+0034 "4" */
    0x8c, 0x63, 0x17, 0x84, 0x21, 0x8,

    /* U+0035 "5" */
    0x74, 0x21, 0xf, 0x4, 0x21, 0x70,

    /* U+0036 "6" */
    0x74, 0x21, 0xf, 0x46, 0x31, 0x70,

    /* U+0037 "7" */
    0xf1, 0x11, 0x1, 0x11, 0x10,

    /* U+0038 "8" */
    0x7c, 0x63, 0x1f, 0x46, 0x31, 0x70,

    /* U+0039 "9" */
    0x74, 0x63, 0x17, 0x84, 0x21, 0x70,

    /* U+003A ":" */
    0x41,

    /* U+003B ";" */
    0x83,

    /* U+003C "<" */
    0x2c, 0x62,

    /* U+003D "=" */
    0xf0, 0xf0,

    /* U+003E ">" */
    0x8c, 0x38,

    /* U+003F "?" */
    0xe1, 0x11, 0xf8, 0x88, 0x80,

    /* U+0040 "@" */
    0x7c, 0x6b, 0x52, 0x76, 0xb1, 0x78,

    /* U+0041 "A" */
    0x7c, 0x63, 0x1f, 0x46, 0x31, 0x88,

    /* U+0042 "B" */
    0xfc, 0x63, 0x1f, 0x46, 0x31, 0x70,

    /* U+0043 "C" */
    0x78, 0x88, 0x8, 0x88, 0x70,

    /* U+0044 "D" */
    0xfc, 0x63, 0x10, 0x46, 0x31, 0x70,

    /* U+0045 "E" */
    0x78, 0x88, 0xf8, 0x88, 0x70,

    /* U+0046 "F" */
    0x78, 0x88, 0xf8, 0x88, 0x80,

    /* U+0047 "G" */
    0x74, 0x21, 0x3, 0x46, 0x31, 0x70,

    /* U+0048 "H" */
    0x8c, 0x63, 0x1f, 0x46, 0x31, 0x88,

    /* U+0049 "I" */
    0xf7, 0x80,

    /* U+004A "J" */
    0x8, 0x42, 0x10, 0x46, 0x31, 0x70,

    /* U+004B "K" */
    0x84, 0xed, 0x4f, 0x46, 0x31, 0x88,

    /* U+004C "L" */
    0x8, 0x88, 0x8, 0x88, 0x70,

    /* U+004D "M" */
    0x7f, 0xc4, 0x62, 0x31, 0x10, 0x4, 0x46, 0x23,
    0x11, 0x88, 0x80,

    /* U+004E "N" */
    0x8e, 0x6b, 0x30, 0x46, 0x31, 0x88,

    /* U+004F "O" */
    0x7c, 0x63, 0x10, 0x46, 0x31, 0x70,

    /* U+0050 "P" */
    0x7c, 0x63, 0x1f, 0x42, 0x10, 0x80,

    /* U+0051 "Q" */
    0x7c, 0x63, 0x10, 0x46, 0x35, 0x71, 0x0,

    /* U+0052 "R" */
    0x7c, 0x63, 0x1f, 0x4a, 0x51, 0x0,

    /* U+0053 "S" */
    0x74, 0x21, 0xf, 0x4, 0x21, 0x70,

    /* U+0054 "T" */
    0xf8, 0x8, 0x42, 0x0, 0x84, 0x20,

    /* U+0055 "U" */
    0x8c, 0x63, 0x10, 0x46, 0x31, 0x78,

    /* U+0056 "V" */
    0x8c, 0x63, 0x18, 0x82, 0x6a, 0x40,

    /* U+0057 "W" */
    0x88, 0xc4, 0x62, 0x31, 0x18, 0x88, 0x2, 0x76,
    0xaa, 0x64, 0x0,

    /* U+0058 "X" */
    0x9a, 0x98, 0x7, 0x1, 0x8a, 0x98,

    /* U+0059 "Y" */
    0x8c, 0x41, 0x35, 0x20, 0x84, 0x20,

    /* U+005A "Z" */
    0xf0, 0x84, 0x40, 0x21, 0x10, 0x70,

    /* U+005B "[" */
    0x72, 0x49, 0x24, 0x60,

    /* U+005C "\\" */
    0x82, 0x10, 0xc2, 0x8, 0x41, 0x8,

    /* U+005D "]" */
    0xc4, 0x92, 0x49, 0xc0,

    /* U+005E "^" */
    0x2, 0x95, 0x10,

    /* U+005F "_" */
    0xf0,

    /* U+0060 "`" */
    0x50,

    /* U+0061 "a" */
    0x7c, 0x63, 0x1f, 0x46, 0x31, 0x88,

    /* U+0062 "b" */
    0xfc, 0x63, 0x1f, 0x46, 0x31, 0x70,

    /* U+0063 "c" */
    0x78, 0x88, 0x8, 0x88, 0x70,

    /* U+0064 "d" */
    0xfc, 0x63, 0x10, 0x46, 0x31, 0x70,

    /* U+0065 "e" */
    0x78, 0x88, 0xf8, 0x88, 0x70,

    /* U+0066 "f" */
    0x78, 0x88, 0xf8, 0x88, 0x80,

    /* U+0067 "g" */
    0x74, 0x21, 0x3, 0x46, 0x31, 0x70,

    /* U+0068 "h" */
    0x8c, 0x63, 0x1f, 0x46, 0x31, 0x88,

    /* U+0069 "i" */
    0xf7, 0x80,

    /* U+006A "j" */
    0x8, 0x42, 0x10, 0x46, 0x31, 0x70,

    /* U+006B "k" */
    0x84, 0xed, 0x4f, 0x46, 0x31, 0x88,

    /* U+006C "l" */
    0x8, 0x88, 0x8, 0x88, 0x70,

    /* U+006D "m" */
    0x7f, 0xc4, 0x62, 0x31, 0x10, 0x4, 0x46, 0x23,
    0x11, 0x88, 0x80,

    /* U+006E "n" */
    0x8e, 0x6b, 0x30, 0x46, 0x31, 0x88,

    /* U+006F "o" */
    0x7c, 0x63, 0x10, 0x46, 0x31, 0x70,

    /* U+0070 "p" */
    0x7c, 0x63, 0x1f, 0x42, 0x10, 0x80,

    /* U+0071 "q" */
    0x7c, 0x63, 0x10, 0x46, 0x35, 0x71, 0x0,

    /* U+0072 "r" */
    0x7c, 0x63, 0x1f, 0x4a, 0x51, 0x0,

    /* U+0073 "s" */
    0x74, 0x21, 0xf, 0x4, 0x21, 0x70,

    /* U+0074 "t" */
    0xf8, 0x8, 0x42, 0x0, 0x84, 0x20,

    /* U+0075 "u" */
    0x8c, 0x63, 0x10, 0x46, 0x31, 0x78,

    /* U+0076 "v" */
    0x8c, 0x63, 0x18, 0x82, 0x6a, 0x40,

    /* U+0077 "w" */
    0x88, 0xc4, 0x62, 0x31, 0x18, 0x88, 0x2, 0x76,
    0xaa, 0x64, 0x0,

    /* U+0078 "x" */
    0x9a, 0x98, 0x7, 0x1, 0x8a, 0x98,

    /* U+0079 "y" */
    0x8c, 0x41, 0x35, 0x20, 0x84, 0x20,

    /* U+007A "z" */
    0xf0, 0x84, 0x40, 0x21, 0x10, 0x70,

    /* U+007B "{" */
    0x24, 0x9c, 0x49, 0x20,

    /* U+007C "|" */
    0xff, 0x70,

    /* U+007D "}" */
    0x92, 0x47, 0x24, 0x80,

    /* U+007E "~" */
    0x4d, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 85, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 29, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 38, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 11},
    {.bitmap_index = 4, .adv_w = 197, .box_w = 12, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 19, .adv_w = 85, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 27, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 33, .adv_w = 119, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 40, .adv_w = 19, .box_w = 1, .box_h = 2, .ofs_x = 0, .ofs_y = 11},
    {.bitmap_index = 41, .adv_w = 56, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 45, .adv_w = 57, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 69, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 52, .adv_w = 76, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 57, .adv_w = 29, .box_w = 1, .box_h = 2, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 58, .adv_w = 63, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 59, .adv_w = 28, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 60, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 66, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 72, .adv_w = 57, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 76, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 82, .adv_w = 85, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 87, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 99, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 85, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 28, .box_w = 1, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 52, .box_w = 1, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 124, .adv_w = 65, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 126, .adv_w = 66, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 128, .adv_w = 65, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 130, .adv_w = 85, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 135, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 153, .adv_w = 85, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 85, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 85, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 180, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 186, .adv_w = 26, .box_w = 1, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 200, .adv_w = 85, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 153, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 222, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 85, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 241, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 253, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 259, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 265, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 144, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 282, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 288, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 294, .adv_w = 84, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 300, .adv_w = 56, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 57, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 314, .adv_w = 98, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 317, .adv_w = 61, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 318, .adv_w = 96, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 319, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 325, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 331, .adv_w = 85, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 336, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 342, .adv_w = 85, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 347, .adv_w = 85, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 358, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 364, .adv_w = 26, .box_w = 1, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 366, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 372, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 378, .adv_w = 85, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 383, .adv_w = 153, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 394, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 400, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 412, .adv_w = 85, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 419, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 425, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 431, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 443, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 144, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 460, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 466, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 472, .adv_w = 84, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 56, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 482, .adv_w = 28, .box_w = 1, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 484, .adv_w = 56, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 488, .adv_w = 94, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 7}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_Font1 = {
#else
lv_font_t ui_font_Font1 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_FONT1*/

