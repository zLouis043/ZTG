#include <stdio.h>
#include "entryPoint.h"

static void points_to_string(){
    sprintf(points_str, "Points : %d", player_stats.points);
}

static void draw_commands(){
    if(show_commands) {
        ztg_render_string(font_ib8x8u, "Use WASD to move the ball", 5, 237, color_gray);
        ztg_render_string(font_ib8x8u, "Press 'Q' to exit", 339, 5, color_gray);
        ztg_render_string(font_ib8x8u, "Press ESC to pause", 331, 18, color_gray);
    }else {
        ztg_render_string(font_ib8x8u, "Press 'C' to show the commands", 5, 237, color_gray);
    }
}

static void check_if_lost() {
    if(!ztg_is_circle_in_bounds(player.bounds.as_circle, ztg_get_console_bounds())){
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
            ztg_draw_filled_circle_Vec(obj.bounds.as_circle.center, (int)obj.bounds.as_circle.radius, obj.color);
        }
    }
}

static bool continue_button(){
    Button continue_b = {
            .bounds = continue_rect,
            .color_base = color_black,
            .color_hover = color_gray,
            .color_pressed = color_red
    };
    return ztg_button(continue_b, "CONTINUE", 30, 7, color_red);
}

static bool back_to_main_menu_button(){
    Button back_to_main_menu_b = {
            .bounds = back_to_main_menu_rect,
            .color_base = color_black,
            .color_hover = color_gray,
            .color_pressed = color_red
    };
    return ztg_button(back_to_main_menu_b, "BACK TO MENU", 20, 7, color_red);
}

static bool quit_in_pause_button(){
    Button quit_b = {
        .bounds = quit_in_pause_rect,
        .color_base = color_black,
        .color_hover = color_gray,
        .color_pressed = color_red
    };
    return ztg_button(quit_b, "QUIT", 50, 7, color_red);
}

static bool quit_in_menu_button(){
    Button quit_b = {
            .bounds = quit_in_menu_rect,
            .color_base = color_black,
            .color_hover = color_gray,
            .color_pressed = color_red
    };
    return ztg_button(quit_b, "QUIT", 50, 7, color_red);
}

static void level_pause(){
    ztg_render_string(font_ib8x8u, "PAUSE", 190, 30, color_red);
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
    ztg_render_string(font_ib8x8u, "YOU LOST", 140, 100, color_red);
    if(new_record){
        player_stats.high_score = player_stats.points;
        sprintf(points_str, "Points : %d", player_stats.points);
        ztg_render_string(font_ib8x8u, "NEW RECORD ", 140, 115, color_red);
        ztg_render_string(font_ib8x8u, points_str, 229, 115, color_gray);
    }else {
        points_to_string();
        ztg_render_string(font_ib8x8u, points_str, 160, 115, color_gray);
    }
    if(lost_screen_duration >= 300){
        lost_screen_duration = 0;
        player_stats.points = 0;
        player_stats.curr_level = MAIN_MENU;
    }
}

static void level_in_game(float elapsedTime){
    check_if_lost();
    points_to_string();
    ztg_show_fps(5, 5, color_red);
    ztg_render_string(font_ib8x8u, points_str, 339, 5, color_green);
    create_new_point();
    player_movement(elapsedTime);
    collide_with_point();
    draw_obj(point);
    draw_obj(player);
}



static void level_main_menu(){
    ztg_render_string(font_ib8x8u, "FatBall Console Game", 140, 80, color_red);
    ztg_render_string(font_ib8x8u, "Press any key to start", 135, 115, color_red);
    ztg_render_string(font_ib8x8u, "Made By Luigi Inquieto", 299, 237, color_gray);
    if(quit_in_menu_button()) ztg_shut_app();
    draw_commands();
}

/*!
 * @attention Function Needed for the engine to work properly
 * @brief Handles the user inputs
 */
void HandleInputs(){

    if(ztg_is_key_pressed_between(KEY_W, KEY_UP))player_stats.dir = UP;
    if(ztg_is_key_pressed_between(KEY_S, KEY_DOWN)) player_stats.dir = DOWN;
    if(ztg_is_key_pressed_between(KEY_A, KEY_LEFT)) player_stats.dir = LEFT;
    if(ztg_is_key_pressed_between(KEY_D, KEY_RIGHT)) player_stats.dir = RIGHT;
    if(ztg_is_key_pressed(KEY_C)) show_commands = !show_commands;
    if(ztg_is_keyboard_pressed_except(KEY_C) && ztg_is_keyboard_pressed_except(KEY_P)){
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

/*!
 * @attention Function Needed for the engine to work properly
 * @brief Updates the frame buffer to render
 */
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
