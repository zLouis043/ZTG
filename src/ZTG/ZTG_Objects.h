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

#ifndef ZTG_EXAMPLE_ZTG_OBJECTS_H
#define ZTG_EXAMPLE_ZTG_OBJECTS_H

#include "ZTG_Collisions.h"

/*!
 * struct Button
 * @brief Contains all the information for a button
 * @param bounds TYPE : (Rect)\n are the rectangular bounds of the button
 * @param color_base TYPE : (int)\n is the base color of the button
 * @param color_hover TYPE : (int)\n is the color of the button when the mouse is hovering it
 * @param color_pressed TYPE : (int)\n is the color of the button when pressed
 */
typedef struct ztg_button{
    Rect bounds;
    int color_base;
    int color_hover;
    int color_pressed;
}Button;

extern Window window;

/*!
 * @fn Create a button with a label and checks if the mouse is over it or it has been pressed
 * @param b TYPE : (Button)\n Is the Button information
 * @param label TYPE : (char *)\n is the label drawn on top of the button
 * @param padding_x TYPE : (int)\n is the distance between the upper left point x of the button and the label x
 * @param padding_y TYPE : (int)\n is the distance between the upper left point y of the button and the label y
 * @param label_color TYPE : (int)\n is the color of the label
 * @return TYPE : (bool)\n true if the button has been pressed
 */
bool ztg_button(Button b, char * label, int padding_x, int padding_y, int label_color);

#endif //ZTG_EXAMPLE_ZTG_OBJECTS_H
