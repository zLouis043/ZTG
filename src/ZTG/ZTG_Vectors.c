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

#include <math.h>
#include "ZTG_Vectors.h"

iVec2 ztg_iVec2(int x, int y){
    return (iVec2){
        .x = x,
        .y = y
    };
}

iVec2 ztg_iVec2_add(iVec2 v1, iVec2 v2){
    return (iVec2){
        .x = v1.x + v2.x,
        .y = v1.y + v2.y
    };
}

iVec2 ztg_iVec2_sub(iVec2 v1, iVec2 v2){
    return (iVec2){
            .x = v1.x - v2.x,
            .y = v1.y - v2.y
    };
}

iVec2 ztg_iVec2_mul(iVec2 v1, iVec2 v2){
    return (iVec2){
            .x = v1.x * v2.x,
            .y = v1.y * v2.y
    };
}

iVec2 ztg_iVec2_div(iVec2 v1, iVec2 v2){
    return (iVec2){
            .x = v1.x / v2.x,
            .y = v1.y / v2.y
    };
}

fVec2 ztg_iVec2_normalized(iVec2 v){

    float mag = ztg_iVec2_magnitude(v);

    return (fVec2){
        .x = (float)v.x / mag,
        .y = (float)v.y / mag
    };
}


iVec2 ztg_iVec2_proj_v1_on_v2(iVec2 v1, iVec2 v2){

    if(ztg_iVec2_are_orthogonal(v1, v2)){
        return (iVec2){
            .x = 0,
            .y = 0
        };
    }

    float scalar_proj = ztg_iVec2_scalar_proj_v1_on_v2(v1, v2);

    return (iVec2){
        .x = v2.x * (int)scalar_proj,
        .y = v2.y * (int)scalar_proj
    };

}

bool ztg_iVec2_are_equal(iVec2 v1, iVec2 v2){
    return (v1.x == v2.x && v1.y == v2.y);
}

bool ztg_iVec2_are_orthogonal(iVec2 v1, iVec2 v2){
    return ztg_iVec2_dot(v1, v2) == 0;
}

float ztg_iVec2_dot(iVec2 v1, iVec2 v2){
    return (float)(v1.x * v2.x + v1.y * v2.y);
}

float ztg_iVec2_magnitude(iVec2 v){
    return sqrtf((float)(v.x * v.x) + (float)(v.y * v.y));
}

float ztg_iVec2_distance(iVec2 v1, iVec2 v2){
    return sqrtf((float)((v2.x - v1.x) * (v2.x - v1.x)) + (float)((v2.y - v1.y) * (v2.y - v1.y)));
}

float ztg_iVec2_scalar_proj_v1_on_v2(iVec2 v1, iVec2 v2){
    if(ztg_iVec2_are_orthogonal(v1, v2)) return 0.0f;
    return ztg_iVec2_dot(v1, v2) / powf(ztg_iVec2_magnitude(v2), 2.0f);
}

fVec2 ztg_fVec2(float x, float y){
    return (fVec2){
            .x = x,
            .y = y
    };
}

fVec2 ztg_fVec2_add(fVec2 v1, fVec2 v2){
    return (fVec2){
            .x = v1.x + v2.x,
            .y = v1.y + v2.y
    };
}

fVec2 ztg_fVec2_sub(fVec2 v1, fVec2 v2){
    return (fVec2){
            .x = v1.x + v2.x,
            .y = v1.y + v2.y
    };
}

fVec2 ztg_fVec2_mul(fVec2 v1, fVec2 v2){
    return (fVec2){
            .x = v1.x + v2.x,
            .y = v1.y + v2.y
    };
}

fVec2 ztg_fVec2_div(fVec2 v1, fVec2 v2){
    return (fVec2){
            .x = v1.x + v2.x,
            .y = v1.y + v2.y
    };
}

fVec2 ztg_fVec2_normalized(fVec2 v){
    float mag = ztg_fVec2_magnitude(v);

    return (fVec2){
            .x = (float)v.x / mag,
            .y = (float)v.y / mag
    };
}

void ztg_fVec2_normalize(fVec2 * v){
    float mag = ztg_fVec2_magnitude(*v);
    v->x /= mag;
    v->y /= mag;
}

fVec2 ztg_fVec2_proj_v1_on_v2(fVec2 v1, fVec2 v2){
    if(ztg_fVec2_are_orthogonal(v1, v2)){
        return (fVec2){
                .x = 0,
                .y = 0
        };
    }

    float scalar_proj = ztg_fVec2_scalar_proj_v1_on_v2(v1, v2);

    return (fVec2){
            .x = v2.x * scalar_proj,
            .y = v2.y * scalar_proj
    };
}

bool ztg_fVec2_are_equal(fVec2 v1, fVec2 v2){
    return (v1.x == v2.x && v1.y == v2.y);
}

bool ztg_fVec2_are_orthogonal(fVec2 v1, fVec2 v2){
    return ztg_fVec2_dot(v1, v2) == 0;
}

float ztg_fVec2_dot(fVec2 v1, fVec2 v2){
    return (v1.x * v2.x + v1.y * v2.y);
}

float ztg_fVec2_magnitude(fVec2 v){
    return sqrtf((float)(v.x * v.x) + (float)(v.y * v.y));
}

float ztg_fVec2_distance(fVec2 v1, fVec2 v2){
    return sqrtf(((v2.x - v1.x) * (v2.x - v1.x)) + ((v2.y - v1.y) * (v2.y - v1.y)));
}

float ztg_fVec2_scalar_proj_v1_on_v2(fVec2 v1, fVec2 v2){
    if(ztg_fVec2_are_orthogonal(v1, v2)) return 0.0f;
    return ztg_fVec2_dot(v1, v2) / powf(ztg_fVec2_magnitude(v2), 2.0f);
}