#ifndef ZTG_ZTG_DRAW_H
#define ZTG_ZTG_DRAW_H

#include <stdint.h>

#include "ZTG_Core.h"
#include "ZTG_Vectors.h"
#include "Fonts/fonts.h"

extern Window window;

#define ztg_mov_to(x, y) \
        ztg_mov_to_in_buffer_file_line(__FILE__, __LINE__, (x), (y))
uint8_t ztg_mov_to_in_buffer_file_line(char* filename, size_t line, size_t x, size_t y);
void ztg_mask_begin(size_t x1, size_t y1, size_t x2, size_t y2);
void ztg_mask_end();
void ztg_draw_char(short c, size_t x, size_t y, int foreground_color, int background_color);
void ztg_draw_pixel(size_t x, size_t y, int color);
void ztg_draw_string(char * str, size_t x, size_t y, int foreground_color, int background_color);
void ztg_render_char(struct bitmap_font font, char c, size_t x, size_t y, int color);
void ztg_render_string(struct bitmap_font font, char * string, size_t x, size_t y, int color);
void ztg_draw_line(int x1, int y1, int x2, int y2, int color);
void ztg_draw_horizontal_line_by_width(int sx, int ex, int ny, int color);
void ztg_draw_rect(int x1, int y1, int x2, int y2, int color);
void ztg_draw_filled_rect(int x1, int y1, int x2, int y2, int color);
void ztg_draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color);
void ztg_draw_filled_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color);
void ztg_draw_circle(int xc, int yc, int r, int color);
void ztg_draw_filled_circle(int xc, int yc, int r, int color);
void ztg_draw_ellipse(int x0, int y0, int x1, int y1, int color);
void ztg_draw_filled_ellipse(int x0, int y0, int x1, int y1, int color);
void ztg_draw_thick_rect(int x1, int y1, int x2, int y2, int thickness, int color);
void ztg_draw_thick_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int thickness, int color);
void ztg_draw_thick_circle(int xc, int yc, int r, int thickness, int color);
void ztg_draw_thick_ellipse(int x0, int y0, int x1, int y1, int thickness, int color);

void ztg_mask_begin_Vec(iVec2 v1, iVec2 v2);
void ztg_draw_char_Vec(short c, iVec2 v, int foreground_color, int background_color);
void ztg_draw_pixel_Vec(iVec2 v, int color);
void ztg_draw_string_Vec(char * str, iVec2 v, int foreground_color, int background_color);
void ztg_render_char_Vec(struct bitmap_font font, char c, iVec2 v, int color);
void ztg_render_string_Vec(struct bitmap_font font, char * string, iVec2 v, int color);
void ztg_draw_line_Vec(iVec2 v1, iVec2 v2, int color);
void ztg_draw_rect_Vec(iVec2 v1, iVec2 v2, int color);
void ztg_draw_filled_rect_Vec(iVec2 v1, iVec2 v2, int color);
void ztg_draw_triangle_Vec(iVec2 v1, iVec2 v2, iVec2 v3, int color);
void ztg_draw_filled_triangle_Vec(iVec2 v1, iVec2 v2, iVec2 v3, int color);
void ztg_draw_circle_Vec(iVec2 v, int r, int color);
void ztg_draw_filled_circle_Vec(iVec2 v, int r, int color);
void ztg_draw_ellipse_Vec(iVec2 v1, iVec2 v2, int color);
void ztg_draw_filled_ellipse_Vec(iVec2 v1, iVec2 v2, int color);
void ztg_draw_thick_rect_Vec(iVec2 v1, iVec2 v2, int thickness, int color);
void ztg_draw_thick_triangle_Vec(iVec2 v1, iVec2 v2, iVec2 v3, int thickness, int color);
void ztg_draw_thick_circle_Vec(iVec2 v, int r, int thickness, int color);
void ztg_draw_thick_ellipse_Vec(iVec2 v1, iVec2 v2, int thickness, int color);

void ztg_clear(int color);
void ztg_show_fps(int x, int y, int color);
#endif //ZTG_ZTG_DRAW_H
