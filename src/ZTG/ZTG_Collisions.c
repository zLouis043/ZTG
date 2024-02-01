#include <Windows.h>
#include <stdbool.h>
#include <math.h>
#include "ZTG_Collisions.h"

bool ztg_collision_point_inside_rect(Rect rect, COORD point){
    int AX = rect.p1.x;
    int AY = rect.p1.y;
    int BX = rect.p2.x;
    int BY = rect.p2.y;
    int CX = rect.p1.x;
    int CY = rect.p2.y;

    int BAX = (BX - AX);
    int BAY = (BY - AY);
    int CAX = (CX - AX);
    int CAY = (CY - AY);


    if ((point.X - AX) * BAX + (point.Y - AY) * BAY < 0.0f) return false;
    if ((point.X - BX) * BAX + (point.Y - BY) * BAY > 0.0f) return false;
    if ((point.X - AX) * CAX + (point.Y - AY) * CAY < 0.0f) return false;
    if ((point.X - CX) * CAX + (point.Y - CY) * CAY > 0.0f) return false;
    return true;
}

bool ztg_collision_circles(Circle c1, Circle c2){
    return ztg_iVec2_distance(c1.center, c2.center) < (float)(c1.radius + c2.radius);
}
