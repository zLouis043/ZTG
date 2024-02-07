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

#include <stdbool.h>
#include "ZTG_Core.h"
#include "ZTG_Objects.h"
#include "ZTG_Draw.h"
#include "ZTG_Utils.h"

bool ztg_button(Button b, char * label, int padding_x, int padding_y, int label_color){

    bool is_hover = ztg_collision_point_inside_rect(b.bounds, ztg_get_mouse_pos());
    bool is_pressed = ztg_is_mouse_button_pressed(MOUSE_LEFT_BUTTON);
    bool clicked = is_hover && is_pressed;
    int curr_color = is_hover ? clicked ? b.color_pressed : b.color_hover : b.color_base;

    ztg_draw_filled_rect(b.bounds.p1.x, b.bounds.p1.y,
                         b.bounds.p2.x, b.bounds.p2.y,
                         curr_color);
    ztg_render_string(font_ib8x8u, label, b.bounds.p1.x + padding_x, b.bounds.p1.y + padding_y, label_color);

    return clicked;
}