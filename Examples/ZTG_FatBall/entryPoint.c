#include <stdio.h>
#include "entryPoint.h"

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
        .color = C_LIGHT_RED
};

Object point = {
        .bounds.as_circle.radius = 3.0f,
        .bounds_t = CIRCLE,
        .color = C_LIGHT_GREEN
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

static void points_to_string(){
    sprintf(points_str, "Points : %d", player_stats.points);
}

static void draw_commands(){
    if(show_commands) {
        ztg_render_string(font_ib8x8u, "Use WASD to move the ball", 5, 237, C_LIGHT_GRAY);
        ztg_render_string(font_ib8x8u, "Press 'Q' to exit", 339, 5, C_LIGHT_GRAY);
        ztg_render_string(font_ib8x8u, "Press ESC to pause", 331, 18, C_LIGHT_GRAY);
    }else {
        ztg_render_string(font_ib8x8u, "Press 'C' to show the commands", 5, 237, C_LIGHT_GRAY);
    }
}

static void check_if_lost() {
    if(!ztg_is_circle_in_window_bounds(player.bounds.as_circle)){
        player_stats.curr_level = DEAD;
        gen_new_point = true;
        player.bounds.as_circle.center.x = 100;
        player.bounds.as_circle.center.y = 100;
        player.bounds.as_circle.radius = 5;
        player.speed = 0.2f;
        new_record = player_stats.points > player_stats.high_score;
    }
}

static void player_movement(float elapsedTime){
    switch (player_stats.dir) {
        case UP:
            player.bounds.as_circle.center.y -= (int) (player.speed * elapsedTime);
            break;
        case DOWN:
            player.bounds.as_circle.center.y += (int) (player.speed * elapsedTime);
            break;
        case LEFT:
            player.bounds.as_circle.center.x -= (int) (player.speed * elapsedTime);
            break;
        case RIGHT:
            player.bounds.as_circle.center.x += (int) (player.speed * elapsedTime);
            break;
        default: break;
    }
}

static void create_new_point(){
    if (gen_new_point) {
        point.bounds.as_circle.center.x = ztg_rand_range(50, ztg_get_console_width()-50);
        point.bounds.as_circle.center.y = ztg_rand_range(50, ztg_get_console_height() - 50);
        gen_new_point = false;
    }
}

static void collide_with_point(){
    Circle point_c = {
            .center.x = point.bounds.as_circle.center.x,
            .center.y = point.bounds.as_circle.center.y,
            .radius = point.bounds.as_circle.radius
    };
    Circle player_c = {
            .center.x = player.bounds.as_circle.center.x,
            .center.y = player.bounds.as_circle.center.y,
            .radius = player.bounds.as_circle.radius
    };
    bool got_a_point = ztg_collision_circles(player_c, point_c);
    if(got_a_point && delta_get_point >= timer_get_point){
        gen_new_point = true;
        player_stats.points++;
        player.bounds.as_circle.radius += (game_increment * 50);
        player.speed += (game_increment / 10);
        delta_get_point = 0.0f;
    }else if(got_a_point){
        delta_get_point += 0.25f;
    }
}

static void draw_obj(Object obj){
    switch(obj.bounds_t){
        case RECTANGLE:{
            ztg_draw_filled_rect_Vec(obj.bounds.as_rect.p1, obj.bounds.as_rect.p2, obj.color);
        }
        case CIRCLE:{
            ztg_draw_filled_circle_Vec(obj.bounds.as_circle.center, (int)obj.bounds.as_circle.radius, 
            ztg_get_value_from_color(ztg_get_color_from_value(obj.color)));
        }
    }
}

static bool continue_button(){
    Button continue_b = {
            .bounds = continue_rect,
            .color_base = C_BLACK ,
            .color_hover = C_LIGHT_GRAY,
            .color_pressed = C_LIGHT_RED
    };
    return ztg_button(continue_b, "CONTINUE", 30, 7, C_LIGHT_RED);
}

static bool back_to_main_menu_button(){
    Button back_to_main_menu_b = {
            .bounds = back_to_main_menu_rect,
            .color_base = C_BLACK ,
            .color_hover = C_LIGHT_GRAY,
            .color_pressed = C_LIGHT_RED
    };
    return ztg_button(back_to_main_menu_b, "BACK TO MENU", 20, 7, C_LIGHT_RED);
}

static bool quit_in_pause_button(){
    Button quit_b = {
        .bounds = quit_in_pause_rect,
        .color_base = C_BLACK ,
        .color_hover = C_LIGHT_GRAY,
        .color_pressed = C_LIGHT_RED
    };
    return ztg_button(quit_b, "QUIT", 50, 7, C_LIGHT_RED);
}

static bool quit_in_menu_button(){
    Button quit_b = {
            .bounds = quit_in_menu_rect,
            .color_base = C_BLACK ,
            .color_hover = C_LIGHT_GRAY,
            .color_pressed = C_LIGHT_RED
    };
    return ztg_button(quit_b, "QUIT", 50, 7, C_LIGHT_RED);
}

static void level_pause(){
    ztg_render_string(font_ib8x8u, "PAUSE", 190, 30, C_LIGHT_RED);
    if(continue_button()){
        player_stats.curr_level = IN_GAME;
    }
    if(back_to_main_menu_button()){
        player_stats.points = 0;
        player_stats.curr_level = MAIN_MENU;
    }
    if(quit_in_pause_button()){
        ztg_shut_app();
    }
    draw_commands();
}

static void level_lost(){
    points_to_string();
    lost_screen_duration++;
    ztg_render_string(font_ib8x8u, "YOU LOST", 140, 100, C_LIGHT_RED);
    if(new_record){
        player_stats.high_score = player_stats.points;
        sprintf(points_str, "Points : %d", player_stats.points);
        ztg_render_string(font_ib8x8u, "NEW RECORD ", 140, 115, C_LIGHT_RED);
        ztg_render_string(font_ib8x8u, points_str, 229, 115, C_LIGHT_GRAY);
    }else {
        points_to_string();
        ztg_render_string(font_ib8x8u, points_str, 160, 115, C_LIGHT_GRAY);
    }
    if(lost_screen_duration >= 100){
        lost_screen_duration = 0;
        player_stats.points = 0;
        player_stats.curr_level = MAIN_MENU;
    }
}

static void level_in_game(float elapsedTime){
    check_if_lost();
    points_to_string();
    ztg_show_fps(5, 5, C_LIGHT_RED);
    ztg_render_string(font_ib8x8u, points_str, 339, 5, C_LIGHT_GREEN);
    create_new_point();
    player_movement(elapsedTime);
    collide_with_point();
    draw_obj(point);
    draw_obj(player);
}



static void level_main_menu(){
    ztg_render_string(font_ib8x8u, "FatBall Console Game", 140, 80, C_LIGHT_RED);
    ztg_render_string(font_ib8x8u, "Press any key to start", 135, 115, C_LIGHT_RED);
    ztg_render_string(font_ib8x8u, "Made By Luigi Inquieto", 299, 237, C_LIGHT_GRAY);
    if(quit_in_menu_button()) ztg_shut_app();
    draw_commands();
}

void HandleInputs(){

    if(ztg_is_key_pressed_between(KEY_W, KEY_UP))player_stats.dir = UP;
    if(ztg_is_key_pressed_between(KEY_S, KEY_DOWN)) player_stats.dir = DOWN;
    if(ztg_is_key_pressed_between(KEY_A, KEY_LEFT)) player_stats.dir = LEFT;
    if(ztg_is_key_pressed_between(KEY_D, KEY_RIGHT)) player_stats.dir = RIGHT;
    if(ztg_is_key_pressed(KEY_C)) show_commands = !show_commands;
    if(ztg_is_keyboard_pressed_except(KEY_C) && ztg_is_keyboard_pressed_except(KEY_ESCAPE)){
        if(player_stats.curr_level == MAIN_MENU){
            player_stats.curr_level = IN_GAME;
            player.bounds.as_circle.center.x = ztg_rand_range(20, ztg_get_console_width()-20);
            player.bounds.as_circle.center.y = ztg_rand_range(20, ztg_get_console_height() - 20);
        }
    }
    if(ztg_is_key_pressed(KEY_ESCAPE)){
        if(player_stats.curr_level != MAIN_MENU) {
            if (player_stats.curr_level == IN_GAME) {
                player_stats.curr_level = PAUSE;
            } else if (player_stats.curr_level == PAUSE) {
                player_stats.curr_level = IN_GAME;
            }
        }
    }
}

void Update(float elapsedTime) {
    if(player_stats.curr_level == DEAD){
        level_lost();
    }else if(player_stats.curr_level == PAUSE){
        level_pause();
    }else if(player_stats.curr_level == IN_GAME) {
        level_in_game(elapsedTime);
    }else if(player_stats.curr_level == MAIN_MENU){
        level_main_menu();
    }
}
