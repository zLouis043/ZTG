#ifndef ZTG_EXAMPLE_ZTG_OBJECTS_H
#define ZTG_EXAMPLE_ZTG_OBJECTS_H

#include "ZTG_Collisions.h"

typedef struct ztg_button{
    Rect bounds;
    int color_base;
    int color_hover;
    int color_pressed;
}Button;

extern Window window;

bool ztg_button(Button b, char * label, int padding_x, int padding_y, int label_color);

#endif //ZTG_EXAMPLE_ZTG_OBJECTS_H
