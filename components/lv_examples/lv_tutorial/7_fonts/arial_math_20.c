
#include "lvgl/lv_misc/lv_font.h"

/***********************************************************************************
 * arial.ttf 20 px Font in U+2200 (∀) .. U+222f (∯)  range with 4 bpp
 * Sparse font with only these characters: ∑∞
***********************************************************************************/

/*Store the image of the letters (glyph)*/
static const uint8_t arial_math_20_glyph_bitmap[] = {
    /*Unicode: U+2211 (∑) , Width: 10 */
    0x00, 0x00, 0x00, 0x00, 0x00,  //..........
    0x00, 0x00, 0x00, 0x00, 0x00,  //..........
    0x00, 0x00, 0x00, 0x00, 0x00,  //..........
    0xff, 0xff, 0xff, 0xff, 0xff,  //@@@@@@@@@@
    0x96, 0x00, 0x00, 0x00, 0x00,  //%+........
    0x0c, 0x30, 0x00, 0x00, 0x00,  //.@........
    0x01, 0xc1, 0x00, 0x00, 0x00,  //..@.......
    0x00, 0x4b, 0x00, 0x00, 0x00,  //..+%......
    0x00, 0x07, 0x80, 0x00, 0x00,  //...+%.....
    0x00, 0x00, 0xb5, 0x00, 0x00,  //....%+....
    0x00, 0x00, 0x3c, 0x00, 0x00,  //.....@....
    0x00, 0x00, 0xc2, 0x00, 0x00,  //....@.....
    0x00, 0x09, 0x50, 0x00, 0x00,  //...%+.....
    0x00, 0x59, 0x00, 0x00, 0x00,  //..+%......
    0x02, 0xc0, 0x00, 0x00, 0x00,  //..@.......
    0x0c, 0x20, 0x00, 0x00, 0x00,  //.@........
    0x95, 0x00, 0x00, 0x00, 0x00,  //%+........
    0xff, 0xff, 0xff, 0xff, 0xff,  //@@@@@@@@@@
    0x00, 0x00, 0x00, 0x00, 0x00,  //..........
    0x00, 0x00, 0x00, 0x00, 0x00,  //..........


    /*Unicode: U+221e (∞) , Width: 9 */
    0x00, 0x00, 0x00, 0x00, 0x00,  //.........
    0x00, 0x00, 0x00, 0x00, 0x00,  //.........
    0x00, 0x00, 0x00, 0x00, 0x00,  //.........
    0x00, 0x00, 0x00, 0x00, 0x00,  //.........
    0x00, 0x00, 0x00, 0x00, 0x00,  //.........
    0x00, 0x00, 0x00, 0x00, 0x00,  //.........
    0x5f, 0xd3, 0x08, 0xff, 0x50,  //+@@..%@@+
    0xf5, 0x3e, 0xa8, 0x15, 0xf0,  //@+.@%%.+@
    0xf0, 0x09, 0xe0, 0x00, 0xf0,  //@..%@...@
    0xf5, 0x3d, 0xa7, 0x15, 0xf0,  //@+.@%+.+@
    0x5f, 0xd3, 0x08, 0xff, 0x50,  //+@@..%@@+
    0x00, 0x00, 0x00, 0x00, 0x00,  //.........
    0x00, 0x00, 0x00, 0x00, 0x00,  //.........
    0x00, 0x00, 0x00, 0x00, 0x00,  //.........
    0x00, 0x00, 0x00, 0x00, 0x00,  //.........
    0x00, 0x00, 0x00, 0x00, 0x00,  //.........
    0x00, 0x00, 0x00, 0x00, 0x00,  //.........
    0x00, 0x00, 0x00, 0x00, 0x00,  //.........
    0x00, 0x00, 0x00, 0x00, 0x00,  //.........
    0x00, 0x00, 0x00, 0x00, 0x00,  //.........


};


/*Store the glyph descriptions*/
static const lv_font_glyph_dsc_t arial_math_20_glyph_dsc[] = {
    {.w_px = 10,  .glyph_index = 0},  /*Unicode: U+2211 (∑)*/
    {.w_px = 9,   .glyph_index = 100},    /*Unicode: U+221e (∞)*/
};

/*List of unicode characters*/
static const uint32_t arial_math_20_unicode_list[] = {
    8721, /*Unicode: U+2211 (∑)*/
    8734, /*Unicode: U+221e (∞)*/
    0,    /*End indicator*/
};

lv_font_t arial_math_20 = {
    .unicode_first = 8704,  /*First Unicode letter in this font*/
    .unicode_last = 8751,   /*Last Unicode letter in this font*/
    .h_px = 20,             /*Font height in pixels*/
    .glyph_bitmap = arial_math_20_glyph_bitmap, /*Bitmap of glyphs*/
    .glyph_dsc = arial_math_20_glyph_dsc,       /*Description of glyphs*/
    .unicode_list = arial_math_20_unicode_list, /*List of unicode characters*/
    .get_bitmap = lv_font_get_bitmap_sparse,    /*Function pointer to get glyph's bitmap*/
    .get_width = lv_font_get_width_sparse,  /*Function pointer to get glyph's width*/
    .bpp = 4,               /*Bit per pixel*/
    .next_page = NULL,      /*Pointer to a font extension*/
};
