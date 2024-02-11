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

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#include "ZTG_Utils.h"
#include "ZTG_Draw.h"
#include "ZTG_Defines.h"
#include "ZTG_Core.h"

extern Window window;

bool ztg_mov_to(size_t x, size_t y){
    window.curr_x = x;
    window.curr_y = y;
    window.curr_idx = get_index_from_2d(x, y , window.width);

    return window.curr_idx < window.BUFFER_MAX_IDX;
}

void ztg_mask_begin(size_t x1, size_t y1, size_t x2, size_t y2, maskType mask_type){
    window.is_mask_enabled = true;
    window.mask_bounds.p1.x = x1;
    window.mask_bounds.p1.y = y1;
    window.mask_bounds.p2.x = x2;
    window.mask_bounds.p2.y = y2;
    window.mask_type = mask_type;
}

void ztg_mask_end(){
    window.is_mask_enabled = false;
}

void ztg_draw_char(short c, size_t x, size_t y, int foreground_color, int background_color){
    if(ztg_mov_to(x, y)) {
        if (window.is_mask_enabled) {
            switch (window.mask_type) {
                case INSIDE: {
                    if (x < window.mask_bounds.p1.x || x > window.mask_bounds.p2.x || y < window.mask_bounds.p1.y || y > window.mask_bounds.p2.y) {
                        if (!window.is_wrap_around_enabled) {
                            if (window.curr_x >= 0 && window.curr_x < window.width && window.curr_y >= 0 &&
                                window.curr_y < window.height) {
                                window.buffer[window.curr_idx].Char.UnicodeChar = c;
                                window.buffer[window.curr_idx].Attributes = 16 * background_color + foreground_color;
                            }
                        } else {
                            window.buffer[window.curr_idx].Char.UnicodeChar = c;
                            window.buffer[window.curr_idx].Attributes = 16 * background_color + foreground_color;
                        }
                    }
                    break;
                }
                case OUTSIDE: {
                    if (x >= window.mask_bounds.p1.x || x <= window.mask_bounds.p2.x || y >= window.mask_bounds.p1.y || y <= window.mask_bounds.p2.y) {
                        if (!window.is_wrap_around_enabled) {
                            if (window.curr_x >= 0 && window.curr_x < window.width && window.curr_y >= 0 &&
                                window.curr_y < window.height) {
                                window.buffer[window.curr_idx].Char.UnicodeChar = c;
                                window.buffer[window.curr_idx].Attributes = 16 * background_color + foreground_color;
                            }
                        } else {
                            window.buffer[window.curr_idx].Char.UnicodeChar = c;
                            window.buffer[window.curr_idx].Attributes = 16 * background_color + foreground_color;
                        }
                    }
                    break;
                }
            }
        } else {
            if (!window.is_wrap_around_enabled) {
                if (window.curr_x >= 0 && window.curr_x < window.width && window.curr_y >= 0 &&
                    window.curr_y < window.height) {
                    window.buffer[window.curr_idx].Char.UnicodeChar = c;
                    window.buffer[window.curr_idx].Attributes = 16 * background_color + foreground_color;
                }
            } else {
                window.buffer[window.curr_idx].Char.UnicodeChar = c;
                window.buffer[window.curr_idx].Attributes = 16 * background_color + foreground_color;
            }
        }
    }
}

void ztg_draw_pixel(size_t x, size_t y, int color){
    
    short shade = window.is_pixel_look_enabled ? (color >> 3 & 1 ? 0x2588 : 0x2593) : ' ';
    int color_conversion =  window.is_pixel_look_enabled ? color : color << 4;

    if(ztg_mov_to(x, y)){
        if(window.is_mask_enabled){
            switch(window.mask_type) {
                case INSIDE: {
                    if (x < window.mask_bounds.p1.x || x > window.mask_bounds.p2.x || y < window.mask_bounds.p1.y || y > window.mask_bounds.p2.y) {
                        if (!window.is_wrap_around_enabled) {
                            if (window.curr_x >= 0 && window.curr_x < window.width && window.curr_y >= 0 &&
                                window.curr_y < window.height) {
                                window.buffer[window.curr_idx].Char.UnicodeChar = shade;
                                window.buffer[window.curr_idx].Attributes = color_conversion;/*color << 4 | (window.is_pixel_look_enabled ? (color | FOREGROUND_INTENSITY) : 0);*/
                            }
                        } else {
                            window.buffer[window.curr_idx].Char.UnicodeChar = shade;
                            window.buffer[window.curr_idx].Attributes = color_conversion;
                        }
                    }break;
                }
                case OUTSIDE:{
                    if (x >= window.mask_bounds.p1.x && x <= window.mask_bounds.p2.x && y >= window.mask_bounds.p1.y && y <= window.mask_bounds.p2.y) {
                        if (!window.is_wrap_around_enabled) {
                            if (window.curr_x >= 0 && window.curr_x < window.width && window.curr_y >= 0 &&
                                window.curr_y < window.height) {
                                window.buffer[window.curr_idx].Char.UnicodeChar = shade;
                                window.buffer[window.curr_idx].Attributes = color_conversion;
                            }
                        } else {
                            window.buffer[window.curr_idx].Char.UnicodeChar = shade;
                            window.buffer[window.curr_idx].Attributes = color_conversion;
                        }
                    }break;
                }
            }
        }else{
            if(!window.is_wrap_around_enabled) {
                if (window.curr_x >= 0 && window.curr_x < window.width && window.curr_y >= 0 &&
                    window.curr_y < window.height) {
                    window.buffer[window.curr_idx].Char.UnicodeChar = shade;
                    window.buffer[window.curr_idx].Attributes = color_conversion;
                }
            }else{
                window.buffer[window.curr_idx].Char.UnicodeChar = shade;
                window.buffer[window.curr_idx].Attributes = color_conversion;
            }
        }
    }
}

void ztg_draw_string(char * str, size_t x, size_t y, int foreground_color, int background_color){
    size_t str_len = strlen(str);
    short * wstring;
    memcpy(wstring, str, str_len);
    for(size_t i = 0; i < str_len; i++){
        ztg_draw_char(wstring[i], x+i, y, foreground_color, background_color);
    }
}

void ztg_render_char(struct bitmap_font font, char c, size_t x, size_t y, int color){

    int set;
    for(int dx = 0; dx < font.Width; dx++){
        for(int dy = 0; dy < font.Height; dy++){
            set = font.Bitmap[font.Index[c] * font.Height + dy] & 1 << dx;
            if(set) {
                ztg_draw_pixel(x - dx + font.Width, y + dy, color);
            }
        }
    }
}

void ztg_render_string(struct bitmap_font font, char * string, size_t x, size_t y, int color){
    size_t str_len = strlen(string);

    for(size_t i = 0; i < str_len; i++){
        ztg_render_char(font, string[i],  x + (8 * i), y, color);
    }
}

void ztg_draw_sprite(Sprite * sprite, int x, int y){
    for(size_t i = 0; i < sprite->width; i++){
        for(size_t j = 0; j < sprite->height; j++){
            ztg_draw_pixel(x + i, y + j, 
            ztg_get_value_from_color(sprite->pixels[get_index_from_2d(i, j, sprite->width)])
            );
        }
    }
}

void ztg_draw_line(int x1, int y1, int x2, int y2, int color){
    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
    dx = x2 - x1; dy = y2 - y1;
    dx1 = abs(dx); dy1 = abs(dy);
    px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
    if (dy1 <= dx1)
    {
        if (dx >= 0)
        { x = x1; y = y1; xe = x2; }
        else
        { x = x2; y = y2; xe = x1;}

        ztg_draw_pixel(x, y, color);

        for (i = 0; x<xe; i++)
        {
            x = x + 1;
            if (px<0)
                px = px + 2 * dy1;
            else
            {
                if ((dx<0 && dy<0) || (dx>0 && dy>0)) y = y + 1; else y = y - 1;
                px = px + 2 * (dy1 - dx1);
            }
            ztg_draw_pixel(x, y, color);
        }
    }
    else
    {
        if (dy >= 0)
        { x = x1; y = y1; ye = y2; }
        else
        { x = x2; y = y2; ye = y1; }

        ztg_draw_pixel(x, y, color);

        for (i = 0; y<ye; i++)
        {
            y = y + 1;
            if (py <= 0)
                py = py + 2 * dx1;
            else
            {
                if ((dx<0 && dy<0) || (dx>0 && dy>0)) x = x + 1; else x = x - 1;
                py = py + 2 * (dx1 - dy1);
            }
            ztg_draw_pixel(x, y, color);
        }
    }
}

void ztg_draw_rect(int x1, int y1, int x2, int y2, int color){
    ztg_draw_line(x1, y1, x2, y1, color);
    ztg_draw_line(x1, y2, x2, y2, color);
    ztg_draw_line(x1, y1, x1, y2, color);
    ztg_draw_line(x2, y1, x2, y2, color);
}

void ztg_draw_filled_rect(int x1, int y1, int x2, int y2, int color){
    for(int x = x1; x < x2; x++){
        for(int y = y1; y < y2; y++){
            ztg_draw_pixel(x, y, color);
        }
    }
}

void ztg_draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color){
    ztg_draw_line(x1, y1, x2, y2, color);
    ztg_draw_line(x2, y2, x3, y3, color);
    ztg_draw_line(x3, y3, x1, y1, color);
}

ZTG_PRIVATE void ztg_swap(int *x, int *y){
    int * tmp = x;
    x = y;
    y = x;
}

void ztg_draw_horizontal_line_by_width(int sx, int ex, int ny, int color){
    for(int i = sx; i <= ex; i++){
        ztg_draw_pixel(i, ny, color);
    }
}

void ztg_draw_filled_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color){

    int t1x, t2x, y, minx, maxx, t1xp, t2xp;
    bool changed1 = false;
    bool changed2 = false;
    int signx1, signx2, dx1, dy1, dx2, dy2;
    int e1, e2;
    // Sort vertices
    if (y1>y2) { ztg_swap(&y1, &y2); ztg_swap(&x1, &x2); }
    if (y1>y3) { ztg_swap(&y1, &y3); ztg_swap(&x1, &x3); }
    if (y2>y3) { ztg_swap(&y2, &y3); ztg_swap(&x2, &x3); }

    t1x = t2x = x1; y = y1;   // Starting points
    dx1 = (int)(x2 - x1); if (dx1<0) { dx1 = -dx1; signx1 = -1; }
    else signx1 = 1;
    dy1 = (int)(y2 - y1);

    dx2 = (int)(x3 - x1); if (dx2<0) { dx2 = -dx2; signx2 = -1; }
    else signx2 = 1;
    dy2 = (int)(y3 - y1);

    if (dy1 > dx1) {   // swap values
        ztg_swap(&dx1, &dy1);
        changed1 = true;
    }
    if (dy2 > dx2) {   // swap values
        ztg_swap(&dy2, &dx2);
        changed2 = true;
    }

    e2 = (int)(dx2 >> 1);
    // Flat top, just process the second half
    if (y1 == y2) goto next;
    e1 = (int)(dx1 >> 1);

    for (int i = 0; i < dx1;) {
        t1xp = 0; t2xp = 0;
        if (t1x<t2x) { minx = t1x; maxx = t2x; }
        else { minx = t2x; maxx = t1x; }
        // process first line until y value is about to change
        while (i<dx1) {
            i++;
            e1 += dy1;
            while (e1 >= dx1) {
                e1 -= dx1;
                if (changed1) t1xp = signx1;//t1x += signx1;
                else          goto next1;
            }
            if (changed1) break;
            else t1x += signx1;
        }
        // Move line
        next1:
        // process second line until y value is about to change
        while (1) {
            e2 += dy2;
            while (e2 >= dx2) {
                e2 -= dx2;
                if (changed2) t2xp = signx2;//t2x += signx2;
                else          goto next2;
            }
            if (changed2)     break;
            else              t2x += signx2;
        }
        next2:
        if (minx>t1x) minx = t1x; if (minx>t2x) minx = t2x;
        if (maxx<t1x) maxx = t1x; if (maxx<t2x) maxx = t2x;
        ztg_draw_horizontal_line_by_width(minx, maxx, y, color);    // Draw line from min to max points found on the y
        // Now increase y
        if (!changed1) t1x += signx1;
        t1x += t1xp;
        if (!changed2) t2x += signx2;
        t2x += t2xp;
        y += 1;
        if (y == y2) break;

    }
    next:
    // Second half
    dx1 = (int)(x3 - x2); if (dx1<0) { dx1 = -dx1; signx1 = -1; }
    else signx1 = 1;
    dy1 = (int)(y3 - y2);
    t1x = x2;

    if (dy1 > dx1) {   // swap values
        ztg_swap(&dy1, &dx1);
        changed1 = true;
    }
    else changed1 = false;

    e1 = (int)(dx1 >> 1);

    for (int i = 0; i <= dx1; i++) {
        t1xp = 0; t2xp = 0;
        if (t1x<t2x) { minx = t1x; maxx = t2x; }
        else { minx = t2x; maxx = t1x; }
        // process first line until y value is about to change
        while (i<dx1) {
            e1 += dy1;
            while (e1 >= dx1) {
                e1 -= dx1;
                if (changed1) { t1xp = signx1; break; }//t1x += signx1;
                else          goto next3;
            }
            if (changed1) break;
            else   	   	  t1x += signx1;
            if (i<dx1) i++;
        }
        next3:
        // process second line until y value is about to change
        while (t2x != x3) {
            e2 += dy2;
            while (e2 >= dx2) {
                e2 -= dx2;
                if (changed2) t2xp = signx2;
                else          goto next4;
            }
            if (changed2)     break;
            else              t2x += signx2;
        }
        next4:

        if (minx>t1x) minx = t1x; if (minx>t2x) minx = t2x;
        if (maxx<t1x) maxx = t1x; if (maxx<t2x) maxx = t2x;
        ztg_draw_horizontal_line_by_width(minx, maxx, y, color);
        if (!changed1) t1x += signx1;
        t1x += t1xp;
        if (!changed2) t2x += signx2;
        t2x += t2xp;
        y += 1;
        if (y>y3) return;
    }
}

void ztg_draw_circle(int xc, int yc, int r, int color){
    int x = 0;
    int y = r;
    int p = 3 - 2 * r;
    if (!r) return;

    while (y >= x) // only formulate 1/8 of circle
    {
        ztg_draw_pixel(xc - x, yc - y, color);//upper left left
        ztg_draw_pixel(xc - y, yc - x, color);//upper upper left
        ztg_draw_pixel(xc + y, yc - x, color);//upper upper right
        ztg_draw_pixel(xc + x, yc - y, color);//upper right right
        ztg_draw_pixel(xc - x, yc + y, color);//lower left left
        ztg_draw_pixel(xc - y, yc + x, color);//lower lower left
        ztg_draw_pixel(xc + y, yc + x, color);//lower lower right
        ztg_draw_pixel(xc + x, yc + y, color);//lower right right
        if (p < 0) p += 4 * x++ + 6;
        else p += 4 * (x++ - y--) + 10;
    }
}

void ztg_draw_filled_circle(int xc, int yc, int r, int color){
    // Taken from wikipedia
    int x = 0;
    int y = r;
    int p = 3 - 2 * r;
    if (!r) return;

    while (y >= x)
    {
        // Modified to draw scan-lines instead of edges
        ztg_draw_horizontal_line_by_width(xc - x, xc + x, yc - y, color);
        ztg_draw_horizontal_line_by_width(xc - y, xc + y, yc - x, color);
        ztg_draw_horizontal_line_by_width(xc - x, xc + x, yc + y, color);
        ztg_draw_horizontal_line_by_width(xc - y, xc + y, yc + x, color);
        if (p < 0) p += 4 * x++ + 6;
        else p += 4 * (x++ - y--) + 10;
    }
};

void ztg_draw_ellipse(int x0, int y0, int x1, int y1, int color){
    int a = abs (x1 - x0);
    int b = abs (y1 - y0);
    int b1 = b & 1;
    long dx = 4 * (1 - a) * b * b;
    int dy = 4 * (b1 + 1) * a * a;
    long err = dx + dy + b1 * a * a, e2;

    if (x0 > x1) {
        x0 = x1;
        x1 += a;
    }
    if (y0 > y1) y0 = y1;
    y0 += (b + 1) / 2;
    y1 = y0-b1;
    a *= 8 * a; b1 = 8 * b * b;
    do{
        ztg_draw_pixel(x1, y0, color);
        ztg_draw_pixel(x0, y0, color);
        ztg_draw_pixel(x0, y1, color);
        ztg_draw_pixel(x1, y1, color);
        e2 = 2 * err;
        if (e2 >= dx)
        {
            x0++;
            x1--;
            err += dx += b1;
        }
        if (e2 <= dy)
        {
            y0++;
            y1--;
            err += dy += a;
        }
    } while (x0 <= x1);
    while (y0-y1 < b){
        ztg_draw_pixel(x0-1, y0, color);
        ztg_draw_pixel(x1+1, y0++, color);
        ztg_draw_pixel(x0-1, y1, color);
        ztg_draw_pixel(x1+1, y1--, color);
    }
}

void ztg_draw_filled_ellipse(int x0, int y0, int x1, int y1, int color){

    int width = abs(x1-x0);
    int height = abs(y1-y0);
    int cx = (x1+x0)/2;
    int cy = (y1+y0)/2;

    for(int i = 0; i < width; i++){
        int dx = i - width / 2;
        int x = cx + dx;

        int h = (int)round(height * sqrt(width * width / 4.0 - dx * dx) / width);
        for(int dy = 1; dy <= h; dy++){
            ztg_draw_pixel(x, cy + dy, color);
            ztg_draw_pixel(x, cy - dy, color);
        }

        if( h >= 0){
            ztg_draw_pixel(x, cy, color);
        }
    }

}

void ztg_draw_thick_line(int x1, int y1, int x2, int y2, int thickness, int color){
    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
    dx = x2 - x1; dy = y2 - y1;
    dx1 = abs(dx); dy1 = abs(dy);
    px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
    if (dy1 <= dx1)
    {
        if (dx >= 0)
        { x = x1; y = y1; xe = x2; }
        else
        { x = x2; y = y2; xe = x1;}

        ztg_draw_circle(x, y, thickness, color);
        ztg_draw_pixel(x, y, color);
        for (i = 0; x<xe; i++)
        {
            x = x + 1;
            if (px<0)
                px = px + 2 * dy1;
            else
            {
                if ((dx<0 && dy<0) || (dx>0 && dy>0)) y = y + 1; else y = y - 1;
                px = px + 2 * (dy1 - dx1);
            }
            ztg_draw_circle(x, y, thickness, color);
            ztg_draw_pixel(x, y, color);
        }
    }
    else
    {
        if (dy >= 0)
        { x = x1; y = y1; ye = y2; }
        else
        { x = x2; y = y2; ye = y1; }

        ztg_draw_circle(x, y, thickness, color);
        ztg_draw_pixel(x, y, color);

        for (i = 0; y<ye; i++)
        {
            y = y + 1;
            if (py <= 0)
                py = py + 2 * dx1;
            else
            {
                if ((dx<0 && dy<0) || (dx>0 && dy>0)) x = x + 1; else x = x - 1;
                py = py + 2 * (dx1 - dy1);
            }
            ztg_draw_circle(x, y, thickness, color);
            ztg_draw_pixel(x, y, color);

        }
    }
}

void ztg_draw_thick_rect(int x1, int y1, int x2, int y2, int thickness, int color){
    ztg_draw_thick_line(x1, y1, x2, y1, thickness, color);
    ztg_draw_thick_line(x1, y2, x2, y2, thickness, color);
    ztg_draw_thick_line(x1, y1, x1, y2, thickness, color);
    ztg_draw_thick_line(x2, y1, x2, y2, thickness, color);
}

void ztg_draw_thick_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int thickness, int color){
    ztg_draw_thick_line(x1, y1, x2, y2, thickness, color);
    ztg_draw_thick_line(x2, y2, x3, y3, thickness, color);
    ztg_draw_thick_line(x3, y3, x1, y1, thickness, color);
}

void ztg_draw_thick_circle(int xc, int yc, int r, int thickness, int color){
    int x = 0;
    int y = r;
    int p = 3 - 2 * r;
    if (!r) return;

    while (y >= x) // only formulate 1/8 of circle
    {
        ztg_draw_pixel(xc - x, yc - y, color);//upper left left
        ztg_draw_pixel(xc - y, yc - x, color);//upper upper left
        ztg_draw_pixel(xc + y, yc - x, color);//upper upper right
        ztg_draw_pixel(xc + x, yc - y, color);//upper right right
        ztg_draw_pixel(xc - x, yc + y, color);//lower left left
        ztg_draw_pixel(xc - y, yc + x, color);//lower lower left
        ztg_draw_pixel(xc + y, yc + x, color);//lower lower right
        ztg_draw_pixel(xc + x, yc + y, color);//lower right right
        ztg_draw_circle(xc - x, yc - y, thickness, color);//upper left left
        ztg_draw_circle(xc - y, yc - x, thickness, color);//upper upper left
        ztg_draw_circle(xc + y, yc - x, thickness, color);//upper upper right
        ztg_draw_circle(xc + x, yc - y, thickness, color);//upper right right
        ztg_draw_circle(xc - x, yc + y, thickness, color);//lower left left
        ztg_draw_circle(xc - y, yc + x, thickness, color);//lower lower left
        ztg_draw_circle(xc + y, yc + x, thickness, color);//lower lower right
        ztg_draw_circle(xc + x, yc + y, thickness, color);//lower right right
        if (p < 0) p += 4 * x++ + 6;
        else p += 4 * (x++ - y--) + 10;
    }
}

void ztg_draw_thick_ellipse(int x0, int y0, int x1, int y1, int thickness, int color){
    int width = abs(x1-x0);
    int height = abs(y1-y0);
    int cx = (x1+x0)/2;
    int cy = (y1+y0)/2;

    for(int i = 0; i < width; i++){
        int dx = i - width / 2;
        int x = cx + dx;

        int h = (int)round(height * sqrt(width * width / 4.0 - dx * dx) / width);
        for(int dy = 1; dy <= h; dy++){
            ztg_draw_pixel(x, cy + dy, color);
            ztg_draw_pixel(x, cy - dy, color);
            ztg_draw_circle(x, cy + dy, thickness, color);
            ztg_draw_circle(x, cy - dy, thickness, color);
        }

        if( h >= 0){
            ztg_draw_pixel(x, cy, color);
            ztg_draw_circle(x, cy, thickness, color);
        }
    }
}

#define ztg_mov_to_Vec(v) \
        ztg_mov_to_in_buffer_file_line(__FILE__, __LINE__, (v.x), (v.y))

void ztg_draw_char_Vec(short c, iVec2 v, int foreground_color, int background_color){
    ztg_draw_char(c, v.x, v.y, foreground_color, background_color);
}

void ztg_mask_begin_Vec(iVec2 v1, iVec2 v2, maskType mask_type){
    window.is_mask_enabled = true;
    window.mask_bounds.p1.x = v1.x;
    window.mask_bounds.p1.y = v1.y;
    window.mask_bounds.p2.x = v2.x;
    window.mask_bounds.p2.y = v2.y;
    window.mask_type = mask_type;
}

void ztg_draw_pixel_Vec(iVec2 v, int color){
    ztg_draw_pixel(v.x, v.y, color);
}

void ztg_draw_string_Vec(char * str, iVec2 v, int foreground_color, int background_color){
    ztg_draw_string(str, v.x, v.y, foreground_color, background_color);
}

void ztg_render_char_Vec(struct bitmap_font font, char c, iVec2 v, int color){
    ztg_render_char(font, c, v.x, v.y, color);
}

void ztg_render_string_Vec(struct bitmap_font font, char * string, iVec2 v, int color){
    ztg_render_string(font, string, v.x, v.y, color);
}

void ztg_draw_line_Vec(iVec2 v1, iVec2 v2, int color){
    ztg_draw_line(v1.x, v1.y, v2.x, v2.y, color);
}

void ztg_draw_rect_Vec(iVec2 v1, iVec2 v2, int color){
    ztg_draw_rect(v1.x, v1.y, v2.x, v2.y, color);
}

void ztg_draw_filled_rect_Vec(iVec2 v1, iVec2 v2, int color){
    ztg_draw_filled_rect(v1.x, v1.y, v2.x, v2.y, color);
}

void ztg_draw_triangle_Vec(iVec2 v1, iVec2 v2, iVec2 v3, int color){
    ztg_draw_triangle(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y, color);
}

void ztg_draw_filled_triangle_Vec(iVec2 v1, iVec2 v2, iVec2 v3, int color){
    ztg_draw_filled_triangle(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y, color);
}

void ztg_draw_circle_Vec(iVec2 v, int r, int color){
    ztg_draw_circle(v.x, v.y, r, color);
}

void ztg_draw_filled_circle_Vec(iVec2 v, int r, int color){
    ztg_draw_filled_circle(v.x, v.y, r, color);
};

void ztg_draw_ellipse_Vec(iVec2 v1, iVec2 v2, int color){
    ztg_draw_ellipse(v1.x, v1.y, v2.x, v2.y, color);
}

void ztg_draw_filled_ellipse_Vec(iVec2 v1, iVec2 v2, int color){
    ztg_draw_filled_ellipse(v1.x, v1.y, v2.x, v2.y, color);
}

void ztg_draw_thick_line_Vec(iVec2 v1, iVec2 v2, int thickness, int color){
    ztg_draw_thick_line(v1.x, v1.y, v2.x, v2.y, thickness, color);
}

void ztg_draw_thick_rect_Vec(iVec2 v1, iVec2 v2, int thickness, int color){
    ztg_draw_thick_rect(v1.x, v1.y, v2.x, v2.y, thickness, color);
}

void ztg_draw_thick_triangle_Vec(iVec2 v1, iVec2 v2, iVec2 v3, int thickness, int color){
    ztg_draw_thick_triangle(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y, thickness, color);
}

void ztg_draw_thick_circle_Vec(iVec2 v, int r, int thickness, int color){
    ztg_draw_thick_circle(v.x, v.y, r, thickness, color);
}

void ztg_draw_thick_ellipse_Vec(iVec2 v1, iVec2 v2, int thickness, int color){
    ztg_draw_thick_ellipse(v1.x, v1.y, v2.x, v2.y, thickness, color);
}

void ztg_clear(int color){

    window.background_color = color;
    for(size_t idx = 0; idx < window.width * window.height; idx++){
        window.buffer[idx].Attributes = color << 4;
    }
}

void ztg_show_fps(int x, int y, int color){
    ztg_render_string(font_ib8x8u, "FPS:", x, y, color);
    ztg_render_string(font_ib8x8u, ztg_format_text("%3.2f fps", (1.0f / (window.elapsed_time)) * 1000.0f), x + (font_ib8x8u.Width * 6), y, C_GRAY);
}