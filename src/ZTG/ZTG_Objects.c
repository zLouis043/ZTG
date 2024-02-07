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