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

#ifndef ZTUI_ZTG_VECTORS_H
#define ZTUI_ZTG_VECTORS_H

#include <stdbool.h>

typedef struct ztg_i_vector2{
    int x;
    int y;
}iVec2;

typedef struct ztg_f_vector2{
    float x;
    float y;
}fVec2;

typedef struct ztg_vector2{
    union{
        iVec2 i;
        fVec2 f;
    }as;
}Vec2;

#define VEC2_FROM_I_VEC2(v) (Vec2){ .as.i = v }
#define VEC2_FROM_F_VEC2(v) (Vec2){ .as.f = v }

#define II_VEC2(value) (iVec2){ .x = value, .y = value }
#define FF_VEC2(value) (fVec2){ .x = value, .y = value }

#define Vec2_as_iVec2(x, y) (Vec2){ .as.i.x = x, as.i.y = y }
#define Vec2_as_fVec2(x, y) (Vec2){ .as.f.x = x, as.f.y = y }

#define IVec2_from_Vec2(v) (v).as.i
#define FVec2_from_Vec2(v) (v).as.f

#define iVec2_null (iVec2){0}
#define fVec2_null (fVec2){0}

iVec2 ztg_iVec2(int x, int y);

iVec2 ztg_iVec2_add(iVec2 v1, iVec2 v2);
iVec2 ztg_iVec2_sub(iVec2 v1, iVec2 v2);
iVec2 ztg_iVec2_mul(iVec2 v1, iVec2 v2);
iVec2 ztg_iVec2_div(iVec2 v1, iVec2 v2);

fVec2 ztg_iVec2_normalized(iVec2 v);

iVec2 ztg_iVec2_proj_v1_on_v2(iVec2 v1, iVec2 v2);

bool ztg_iVec2_are_equal(iVec2 v1, iVec2 v2);
bool ztg_iVec2_are_orthogonal(iVec2 v1, iVec2 v2);

float ztg_iVec2_dot(iVec2 v1, iVec2 v2);
float ztg_iVec2_magnitude(iVec2 v);
float ztg_iVec2_distance(iVec2 v1, iVec2 v2);
float ztg_iVec2_scalar_proj_v1_on_v2(iVec2 v1, iVec2 v2);

fVec2 ztg_fVec2(float x, float y);

fVec2 ztg_fVec2_add(fVec2 v1, fVec2 v2);
fVec2 ztg_fVec2_sub(fVec2 v1, fVec2 v2);
fVec2 ztg_fVec2_mul(fVec2 v1, fVec2 v2);
fVec2 ztg_fVec2_div(fVec2 v1, fVec2 v2);

fVec2 ztg_fVec2_normalized(fVec2 v);
void ztg_fVec2_normalize(fVec2 * v);

fVec2 ztg_fVec2_proj_v1_on_v2(fVec2 v1, fVec2 v2);

bool ztg_fVec2_are_equal(fVec2 v1, fVec2 v2);
bool ztg_fVec2_are_orthogonal(fVec2 v1, fVec2 v2);

float ztg_fVec2_dot(fVec2 v1, fVec2 v2);
float ztg_fVec2_magnitude(fVec2 v);
float ztg_fVec2_distance(fVec2 v1, fVec2 v2);
float ztg_fVec2_scalar_proj_v1_on_v2(fVec2 v1, fVec2 v2);

#endif //ZTUI_ZTG_VECTORS_H
