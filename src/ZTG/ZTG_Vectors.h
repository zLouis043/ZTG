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

#ifndef ZTG_VECTORS_H
#define ZTG_VECTORS_H

#include "ZTG_Defines.h"

#include <stdbool.h>

/*!
 * @struct iVec2
 * @brief Vector 2D of integers
 * @param x TYPE : (int)\n The x coordinate of the vector
 * @param y TYPE : (int)\n The y coordinate of the vector 
 */
typedef struct ztg_i_vector2{
    int x;
    int y;
}iVec2;

/*!
 * @struct fVec2
 * @brief Vector 2D of floats
 * @param x TYPE : (float)\n The x coordinate of the vector
 * @param y TYPE : (float)\n The y coordinate of the vector 
 */
typedef struct ztg_f_vector2{
    float x;
    float y;
}fVec2;

/*!
 * @struct Vec2
 * @brief Vector 2D for both integers and float 
 * @param as TYPE : (union)\n Union containing a iVec2 and a fVec2
 */
typedef struct ztg_vector2{
    union{
        iVec2 i;
        fVec2 f;
    }as;
}Vec2;

/*!
 * @brief Set the iVec2 component from a Vec2 
 */
#define VEC2_FROM_I_VEC2(v) (Vec2){ .as.i = v }

/*!
 * @brief Set the fVec2 component from a Vec2 
 */
#define VEC2_FROM_F_VEC2(v) (Vec2){ .as.f = v }

/*!
 * @brief Pass a single integer as an iVec2 with both coordinates equal to that integer 
 */
#define II_VEC2(value) (iVec2){ .x = value, .y = value }

/*!
 * @brief Pass a single float as an fVec2 with both coordinates equal to that float 
 */
#define FF_VEC2(value) (fVec2){ .x = value, .y = value }

/*!
 * @brief Pass an x and a y coordinate as a iVec2 component of a Vec2
 */
#define Vec2_as_iVec2(x, y) (Vec2){ .as.i.x = x, as.i.y = y }

/*!
 * @brief Pass an x and a y coordinate as a fVec2 component of a Vec2
 */
#define Vec2_as_fVec2(x, y) (Vec2){ .as.f.x = x, as.f.y = y }

/*!
 * @brief get the iVec2 component from a Vec2 
 */
#define IVec2_from_Vec2(v) (v).as.i

/*!
 * @brief Get the fVec2 component from a Vec2 
 */
#define FVec2_from_Vec2(v) (v).as.f


#define iVec2_null (iVec2){0}
#define fVec2_null (fVec2){0}

/*!
 * @brief Create a new iVec2 from two coordinates
 * @param x TYPE : (int) \n The x coordinate
 * @param y TYPE : (int) \n The y coordinate
 * @return A new iVec2
 */
ZTGAPI iVec2 ztg_iVec2(int x, int y);

/*!
 * @brief Sum two iVec2 vectors 
 * @param v1 TYPE : (iVec2) \n The first vector
 * @param v2 TYPE : (iVec2) \n The second vector 
 * @return TYPE : (iVec2) \n A third iVec2 that is the sum of the other two  
 */
ZTGAPI iVec2 ztg_iVec2_add(iVec2 v1, iVec2 v2);

/*!
 * @brief Subtract two iVec2 vectors 
 * @param v1 TYPE : (iVec2) \n The first vector
 * @param v2 TYPE : (iVec2) \n The second vector 
 * @return TYPE : (iVec2) \n A third iVec2 that is the difference of the other two  
 */
ZTGAPI iVec2 ztg_iVec2_sub(iVec2 v1, iVec2 v2);

/*!
 * @brief Multiply two iVec2 vectors 
 * @param v1 TYPE : (iVec2) \n The first vector
 * @param v2 TYPE : (iVec2) \n The second vector 
 * @return TYPE : (iVec2) \n A third iVec2 that is the product of the other two  
 */
ZTGAPI iVec2 ztg_iVec2_mul(iVec2 v1, iVec2 v2);

/*!
 * @brief Divide two iVec2 vectors 
 * @param v1 TYPE : (iVec2) \n The first vector
 * @param v2 TYPE : (iVec2) \n The second vector 
 * @return TYPE : (iVec2) \n A third iVec2 that is the division of the other two  
 */
ZTGAPI iVec2 ztg_iVec2_div(iVec2 v1, iVec2 v2);

/*!
 * @brief Get the orthogonal vector of the given vector
 * @param v TYPE : (iVec2) \n
 * @param TYPE : (iVec2) \n The orthogonal vector
 */
ZTGAPI iVec2 ztg_iVec2_orthogonal(iVec2 v);

/*!
 * @brief Get the normalized version of the vector
 * @param v TYPE : (iVec2) \n The vector to normalize
 * @param TYPE : (fVec2) \n The normalized vector
 */
ZTGAPI fVec2 ztg_iVec2_normalized(iVec2 v);

/*!
 * @brief Check if two iVec2 vectors are equal
 * @param v1 TYPE : (iVec2) \n
 * @param v2 TYPE : (iVec2) \n
 * @return TYPE : (bool) \n True if they are equal otherwise false 
 */
ZTGAPI bool ztg_iVec2_are_equal(iVec2 v1, iVec2 v2);

/*!
 * @brief Check if two iVec2 vectors are orthogonal
 * @param v1 TYPE : (iVec2) \n
 * @param v2 TYPE : (iVec2) \n
 * @return TYPE : (bool) \n True if they are orthogonal otherwise false 
 */
ZTGAPI bool ztg_iVec2_are_orthogonal(iVec2 v1, iVec2 v2);

/*!
 * @brief Get the dot product of two iVec2 vectors
 * @param v1 TYPE : (iVec2) \n
 * @param v2 TYPE : (iVec2) \n
 * @return TYPE : (float) \n The dot product between the given vectors 
 */
ZTGAPI float ztg_iVec2_dot(iVec2 v1, iVec2 v2);

/*!
 * @brief Get the magnitude of a vector 
 * @param v TYPE : (iVec2) \n
 * @return TYPE : (float) \n The magnitude of the given vector 
 */
ZTGAPI float ztg_iVec2_magnitude(iVec2 v);

/*!
 * @brief Get the distance between two vectors 
 * @param v1 TYPE : (iVec2) \n
 * @param v2 TYPE : (iVec2) \n 
 * @return TYPE : (float) \n The distance between the given vectors 
 */
ZTGAPI float ztg_iVec2_distance(iVec2 v1, iVec2 v2);

/*!
 * @brief Get the scalar factor of the projection of v1 on v2
 * @param v1 TYPE : (iVec2) \n 
 * @param v2 TYPE : (iVec2) \n
 * @return TYPE : (float) \n The scalar factor of the projection of v1 on v2s 
 */
ZTGAPI float ztg_iVec2_scalar_proj_v1_on_v2(iVec2 v1, iVec2 v2);

/*!
 * @brief Create a new fVec2 from two coordinates
 * @param x TYPE : (int) \n The x coordinate
 * @param y TYPE : (int) \n The y coordinate
 * @return a new fVec2
 */
ZTGAPI fVec2 ztg_fVec2(float x, float y);

/*!
 * @brief Sum two iVec2 vectors 
 * @param v1 TYPE : (iVec2) \n The first vector
 * @param v2 TYPE : (iVec2) \n The second vector 
 * @return TYPE : (iVec2) \n A third iVec2 that is the sum of the other two  
 */
ZTGAPI fVec2 ztg_fVec2_add(fVec2 v1, fVec2 v2);

/*!
 * @brief Subtract two iVec2 vectors 
 * @param v1 TYPE : (iVec2) \n The first vector
 * @param v2 TYPE : (iVec2) \n The second vector 
 * @return TYPE : (iVec2) \n A third iVec2 that is the difference of the other two  
 */
ZTGAPI fVec2 ztg_fVec2_sub(fVec2 v1, fVec2 v2);

/*!
 * @brief Multiply two iVec2 vectors 
 * @param v1 TYPE : (iVec2) \n The first vector
 * @param v2 TYPE : (iVec2) \n The second vector 
 * @return TYPE : (iVec2) \n A third iVec2 that is the product of the other two  
 */
ZTGAPI fVec2 ztg_fVec2_mul(fVec2 v1, fVec2 v2);

/*!
 * @brief Divide two iVec2 vectors 
 * @param v1 TYPE : (iVec2) \n The first vector
 * @param v2 TYPE : (iVec2) \n The second vector 
 * @return TYPE : (iVec2) \n A third iVec2 that is the division of the other two  
 */
ZTGAPI fVec2 ztg_fVec2_div(fVec2 v1, fVec2 v2);

/*!
 * @brief Get the orthogonal vector of the given vector
 * @param v TYPE : (fVec2) \n
 * @param TYPE : (fVec2) \n The orthogonal vector
 */
ZTGAPI fVec2 ztg_fVec2_orthogonal(fVec2 v);

/*!
 * @brief Get the normalized version of the vector
 * @param v TYPE : (fVec2) \n The vector to normalize
 * @param TYPE : (fVec2) \n The normalized vector
 */
ZTGAPI fVec2 ztg_fVec2_normalized(fVec2 v);

/*!
 * @brief Normalize a given fVec2 vector
 * @param v TYPE : (iVec2) \n The vector to normalize
 */
ZTGAPI void ztg_fVec2_normalize(fVec2 * v);

/*!
 * @brief Get the the projection vector of v1 on v2
 * @param v1 TYPE : (fVec2) \n 
 * @param v2 TYPE : (fVec2) \n
 * @return TYPE : (fVec2) \n The projection vector of v1 on v2s 
 */
ZTGAPI fVec2 ztg_fVec2_proj_v1_on_v2(fVec2 v1, fVec2 v2);

/*!
 * @brief Check if two iVec2 vectors are equal
 * @param v1 TYPE : (iVec2) \n
 * @param v2 TYPE : (iVec2) \n
 * @return TYPE : (bool) \n True if they are equal otherwise false 
 */
ZTGAPI bool ztg_fVec2_are_equal(fVec2 v1, fVec2 v2);

/*!
 * @brief Check if two iVec2 vectors are orthogonal
 * @param v1 TYPE : (iVec2) \n
 * @param v2 TYPE : (iVec2) \n
 * @return TYPE : (bool) \n True if they are orthogonal otherwise false 
 */
ZTGAPI bool ztg_fVec2_are_orthogonal(fVec2 v1, fVec2 v2);

/*!
 * @brief Get the dot product of two fVec2 vectors
 * @param v1 TYPE : (fVec2) \n
 * @param v2 TYPE : (fVec2) \n
 * @return TYPE : (float) \n The dot product between the given vectors 
 */
ZTGAPI float ztg_fVec2_dot(fVec2 v1, fVec2 v2);

/*!
 * @brief Get the magnitude of a vector 
 * @param v TYPE : (fVec2) \n
 * @return TYPE : (float) \n The magnitude of the given vector 
 */
ZTGAPI float ztg_fVec2_magnitude(fVec2 v);

/*!
 * @brief Get the distance between two vectors 
 * @param v1 TYPE : (fVec2) \n
 * @param v2 TYPE : (fVec2) \n 
 * @return TYPE : (float) \n The distance between the given vectors 
 */
ZTGAPI float ztg_fVec2_distance(fVec2 v1, fVec2 v2);

/*!
 * @brief Get the scalar factor of the projection of v1 on v2
 * @param v1 TYPE : (fVec2) \n 
 * @param v2 TYPE : (fVec2) \n
 * @return TYPE : (float) \n The scalar factor of the projection of v1 on v2s 
 */
ZTGAPI float ztg_fVec2_scalar_proj_v1_on_v2(fVec2 v1, fVec2 v2);

#endif //ZTG_VECTORS_H
