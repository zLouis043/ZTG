#ifndef ZTG_EXAMPLE_ZTG_COLLISIONS_H
#define ZTG_EXAMPLE_ZTG_COLLISIONS_H

#include "ZTG_Defines.h"
#include "ZTG_Vectors.h"

typedef struct ztg_rect{
    iVec2 p1;
    iVec2 p2;
}Rect;

typedef struct ztg_circle{
    iVec2 center;
    float radius;
}Circle;

bool ztg_collision_point_inside_rect(Rect rect, Coord point);
bool ztg_collision_circles(Circle c1, Circle c2);

#endif //ZTG_EXAMPLE_ZTG_COLLISIONS_H
