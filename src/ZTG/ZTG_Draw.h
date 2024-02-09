/*
 * MIT License

Copyright (c) 2024 zLouis043

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

 */

#ifndef ZTG_DRAW_H
#define ZTG_DRAW_H

#include <stdint.h>
#include <stdbool.h>

#include "ZTG_Defines.h"
#include "ZTG_Core.h"
#include "ZTG_Vectors.h"
#include "Fonts/fonts.h"


extern Window window;

ZTGAPI bool ztg_mov_to(size_t x, size_t y);
ZTGAPI void ztg_mask_begin(size_t x1, size_t y1, size_t x2, size_t y2, maskType mask_type);
ZTGAPI void ztg_mask_end();
ZTGAPI void ztg_draw_char(short c, size_t x, size_t y, int foreground_color, int background_color);
ZTGAPI void ztg_draw_pixel(size_t x, size_t y, int color);
ZTGAPI void ztg_draw_string(char * str, size_t x, size_t y, int foreground_color, int background_color);
ZTGAPI void ztg_render_char(struct bitmap_font font, char c, size_t x, size_t y, int color);
ZTGAPI void ztg_render_string(struct bitmap_font font, char * string, size_t x, size_t y, int color);
ZTGAPI void ztg_draw_line(int x1, int y1, int x2, int y2, int color);
ZTGAPI void ztg_draw_horizontal_line_by_width(int sx, int ex, int ny, int color);
ZTGAPI void ztg_draw_rect(int x1, int y1, int x2, int y2, int color);
ZTGAPI void ztg_draw_filled_rect(int x1, int y1, int x2, int y2, int color);
ZTGAPI void ztg_draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color);
ZTGAPI void ztg_draw_filled_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color);
ZTGAPI void ztg_draw_circle(int xc, int yc, int r, int color);
ZTGAPI void ztg_draw_filled_circle(int xc, int yc, int r, int color);
ZTGAPI void ztg_draw_ellipse(int x0, int y0, int x1, int y1, int color);
ZTGAPI void ztg_draw_filled_ellipse(int x0, int y0, int x1, int y1, int color);
ZTGAPI void ztg_draw_thick_rect(int x1, int y1, int x2, int y2, int thickness, int color);
ZTGAPI void ztg_draw_thick_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int thickness, int color);
ZTGAPI void ztg_draw_thick_circle(int xc, int yc, int r, int thickness, int color);
ZTGAPI void ztg_draw_thick_ellipse(int x0, int y0, int x1, int y1, int thickness, int color);

ZTGAPI void ztg_mask_begin_Vec(iVec2 v1, iVec2 v2, maskType mask_type);
ZTGAPI void ztg_draw_char_Vec(short c, iVec2 v, int foreground_color, int background_color);
ZTGAPI void ztg_draw_pixel_Vec(iVec2 v, int color);
ZTGAPI void ztg_draw_string_Vec(char * str, iVec2 v, int foreground_color, int background_color);
ZTGAPI void ztg_render_char_Vec(struct bitmap_font font, char c, iVec2 v, int color);
ZTGAPI void ztg_render_string_Vec(struct bitmap_font font, char * string, iVec2 v, int color);
ZTGAPI void ztg_draw_line_Vec(iVec2 v1, iVec2 v2, int color);
ZTGAPI void ztg_draw_rect_Vec(iVec2 v1, iVec2 v2, int color);
ZTGAPI void ztg_draw_filled_rect_Vec(iVec2 v1, iVec2 v2, int color);
ZTGAPI void ztg_draw_triangle_Vec(iVec2 v1, iVec2 v2, iVec2 v3, int color);
ZTGAPI void ztg_draw_filled_triangle_Vec(iVec2 v1, iVec2 v2, iVec2 v3, int color);
ZTGAPI void ztg_draw_circle_Vec(iVec2 v, int r, int color);
ZTGAPI void ztg_draw_filled_circle_Vec(iVec2 v, int r, int color);
ZTGAPI void ztg_draw_ellipse_Vec(iVec2 v1, iVec2 v2, int color);
ZTGAPI void ztg_draw_filled_ellipse_Vec(iVec2 v1, iVec2 v2, int color);
ZTGAPI void ztg_draw_thick_rect_Vec(iVec2 v1, iVec2 v2, int thickness, int color);
ZTGAPI void ztg_draw_thick_triangle_Vec(iVec2 v1, iVec2 v2, iVec2 v3, int thickness, int color);
ZTGAPI void ztg_draw_thick_circle_Vec(iVec2 v, int r, int thickness, int color);
ZTGAPI void ztg_draw_thick_ellipse_Vec(iVec2 v1, iVec2 v2, int thickness, int color);

ZTGAPI void ztg_clear(int color);
ZTGAPI void ztg_show_fps(int x, int y, int color);
#endif //ZTG_DRAW_H
