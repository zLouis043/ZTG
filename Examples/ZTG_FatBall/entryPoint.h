#ifndef ZTG_EXAMPLE_ENTRYPOINT_H
#define ZTG_EXAMPLE_ENTRYPOINT_H

#include "../../src/ZTG/ZTG.h"

typedef struct ztg_object{
    union{
        Rect as_rect;
        Circle as_circle;
    }bounds;
    enum{
        RECTANGLE,
        CIRCLE
    }bounds_t;
    float speed;
    int color;
}Object;

typedef enum ztg_dir{
    UP,
    DOWN,
    LEFT,
    RIGHT
}Direction;

typedef enum ztg_level{
    MAIN_MENU,
    PAUSE,
    IN_GAME,
    DEAD
}Level;

typedef struct ztg_stats{
    Direction dir;
    int points;
    int high_score;
    Level curr_level;
}Statistics;

Statistics player_stats = {
        .dir = 0,
        .points = 0,
        .high_score = 0,
        .curr_level = MAIN_MENU
};

Object player = {
        .bounds.as_circle.center.x = 100,
        .bounds.as_circle.center.y = 100,
        .bounds.as_circle.radius = 5.0f,
        .bounds_t = CIRCLE,
        .speed = 0.2f,
        .color = color_red
};

Object point = {
        .bounds.as_circle.radius = 3.0f,
        .bounds_t = CIRCLE,
        .color = color_green
};

Rect continue_rect = {
        .p1.x = 150,
        .p1.y = 80,
        .p2.x = 300,
        .p2.y = 100
};

Rect back_to_main_menu_rect = {
        .p1.x = 150,
        .p1.y = 105,
        .p2.x = 300,
        .p2.y = 125
};

Rect quit_in_pause_rect = {
        .p1.x = 150,
        .p1.y = 130,
        .p2.x = 300,
        .p2.y = 155
};

Rect quit_in_menu_rect = {
        .p1.x = 150,
        .p1.y = 160,
        .p2.x = 300,
        .p2.y = 185
};

float game_increment = 0.01f;
int lost_screen_duration = 0;
float delta_get_point = 0.0f;
float timer_get_point = 0.5f;
bool gen_new_point = true;
bool new_record = true;
bool show_commands = false;

char points_str[256];

#endif //ZTG_EXAMPLE_ENTRYPOINT_H
