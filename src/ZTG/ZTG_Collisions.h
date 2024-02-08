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

#ifndef ZTG_COLLISIONS_H
#define ZTG_COLLISIONS_H

#include "ZTG_Defines.h"
#include "ZTG_Vectors.h"

/*!
 * @struct Rect
 * @brief Contains the two opposite vertices of a rectangle
 * @param p1 TYPE : (iVec2)\n Is the upper-left point of the rectangle
 * @param p2 TYPE : (iVec2)\n Is the lower-right point of the rectangle
 */
typedef struct ztg_rect{
    iVec2 p1;
    iVec2 p2;
}Rect;

/*!
 * @struct Circle
 * @brief Contains the center point and the radius of a circle
 * @param center TYPE : (iVec2)\n Is the center of the circle
 * @param radius TYPE : (float)\n Is the radius of the circle
 */
typedef struct ztg_circle{
    iVec2 center;
    float radius;
}Circle;

/*!
 * @brief Check if two circles collide with each other
 * @param c1 TYPE : (Circle)\n
 * @param c2 TYPE : (Circle)\n
 * @return TYPE : (bool)\n True if the circles collide otherwise it returns false
 */
ZTGAPI bool ztg_collision_circles(Circle c1, Circle c2);

/*!
 * @brief Check if a point is inside of a rectangle
 * @param rect TYPE : (Rect)\n
 * @param point TYPE : (iVec2)\n
 * @return TYPE : (bool)\n True if the point is inside and false if not
 */
ZTGAPI bool ztg_collision_point_inside_rect(Rect rect, iVec2 point);

/*!
 * @brief Check if a circle is inside Rectangular Bounds
 * @param rect TYPE : (Rect)\n
 * @param c TYPE : (Circle)\n
 * @return TYPE : (bool)\n True if the circle is inside and false if not
 */
ZTGAPI bool ztg_collision_circle_inside_rect(Rect rect, Circle c);

/*!
 * @brief Check if a point is inside the Console Window bounds
 * @param point TYPE : (iVec2)\n
 * @return TYPE : (bool)\n True if the point is inside and false if not
 */
ZTGAPI bool ztg_is_point_in_window_bounds(iVec2 point);


/*!
 * @brief Check if a circle is inside the Console Window bounds
 * @param c TYPE : (Circle)\n
 * @return TYPE : (bool)\n True if the point is inside and false if not
 */
ZTGAPI bool ztg_is_circle_in_window_bounds(Circle c);


#endif //ZTG_COLLISIONS_H
