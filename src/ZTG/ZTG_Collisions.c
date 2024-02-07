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

#include <Windows.h>
#include <stdbool.h>
#include <math.h>
#include "ZTG_Collisions.h"
#include "ZTG_Utils.h"

bool ztg_collision_point_inside_rect(Rect rect, iVec2 point){
    return (point.x < rect.p2.x &&
            point.x > rect.p1.x &&
            point.y < rect.p2.y &&
            point.y > rect.p1.y);
}

bool ztg_collision_circles(Circle c1, Circle c2){
    return ztg_iVec2_distance(c1.center, c2.center) < (float)(c1.radius + c2.radius);
}

bool ztg_is_point_in_window_bounds(iVec2 point){
    return ((float)point.x < (float)ztg_get_console_width() &&
       (float)point.x > 0 &&
       (float)point.y < (float)ztg_get_console_height() &&
       (float)point.y  > 0);
}

bool ztg_is_circle_in_bounds(Circle c, Rect bounds){
    return ((float)c.center.x + c.radius < (float)ztg_get_console_width() &&
    (float)c.center.x - c.radius > 0 &&
    (float)c.center.y + c.radius < (float)ztg_get_console_height() &&
    (float)c.center.y - c.radius > 0);
}