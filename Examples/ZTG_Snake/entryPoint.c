#include "GameLoop.h"
#include <string.h>
#include <math.h>

typedef enum level{
    inGame,
    mainMenu,
    optionsMenu,
    pauseMenu,
    deadScreen
}Level;

Level current_level;
Level previous_level;
int current_record;
int current_score;
int lost_screen_duration;
bool new_record;
bool enable_old_graphics;

Rect continue_rect = {
        .p1.x = 150,
        .p1.y = 80,
        .p2.x = 300,
        .p2.y = 100
};

Rect enable_old_graphics_rect = {
        .p1.x = 150,
        .p1.y = 80,
        .p2.x = 300,
        .p2.y = 100
};

Rect options_rect = {
        .p1.x = 150,
        .p1.y = 105,
        .p2.x = 300,
        .p2.y = 125
};

Rect back_to_main_menu_rect = {
        .p1.x = 150,
        .p1.y = 130,
        .p2.x = 300,
        .p2.y = 155
};

Rect back_to_options_rect = {
        .p1.x = 150,
        .p1.y = 105,
        .p2.x = 300,
        .p2.y = 125
};

Rect quit_in_pause_rect = {
        .p1.x = 150,
        .p1.y = 160,
        .p2.x = 300,
        .p2.y = 185
};

Rect quit_in_menu_rect = {
        .p1.x = 150,
        .p1.y = 160,
        .p2.x = 300,
        .p2.y = 185
};

static bool continue_button(){
    Button continue_b = {
            .bounds = continue_rect,
            .color_base = C_BLACK ,
            .color_hover = C_GRAY,
            .color_pressed = C_RED
    };
    return ztg_button(continue_b, "CONTINUE", 30, 7, C_RED);
}

static bool enable_old_graphics_button(){
    Button enable_old_graphics_b = {
            .bounds = enable_old_graphics_rect,
            .color_base = C_BLACK ,
            .color_hover = C_GRAY,
            .color_pressed = C_RED
    };
    return ztg_button(enable_old_graphics_b, ztg_format_text("OLD GRAPHICS : %s", enable_old_graphics ? "ON" : "OFF"), 5, 7, enable_old_graphics ? C_CYAN : C_RED);
}

static bool options_buttons(){
    Button options_b = {
            .bounds = options_rect,
            .color_base = C_BLACK ,
            .color_hover = C_GRAY,
            .color_pressed = C_RED
    };
    return ztg_button(options_b, "OPTIONS", 30, 7, C_RED);
}

static bool back_to_main_menu_button(){
    Button back_to_main_menu_b = {
            .bounds = back_to_main_menu_rect,
            .color_base = C_BLACK ,
            .color_hover = C_GRAY,
            .color_pressed = C_RED
    };
    return ztg_button(back_to_main_menu_b, "BACK TO MENU", 20, 7, C_RED);
}

static bool back_to_options_button(){
    Button back_to_options_b = {
            .bounds = back_to_options_rect,
            .color_base = C_BLACK ,
            .color_hover = C_GRAY,
            .color_pressed = C_RED
    };
    return ztg_button(back_to_options_b, "BACK TO OPTIONS", 17, 7, C_RED);
}

static bool quit_in_pause_button(){
    Button quit_b = {
        .bounds = quit_in_pause_rect,
        .color_base = C_BLACK ,
        .color_hover = C_GRAY,
        .color_pressed = C_RED
    };
    return ztg_button(quit_b, "QUIT", 50, 7, C_RED);
}

static bool quit_in_menu_button(){
    Button quit_b = {
            .bounds = quit_in_menu_rect,
            .color_base = C_BLACK ,
            .color_hover = C_GRAY,
            .color_pressed = C_RED
    };
    return ztg_button(quit_b, "QUIT", 50, 7, C_RED);
}

void Start(){

    current_level = mainMenu;
    current_record = 0;
    new_record = true;
    enable_old_graphics = false;
    GameStart();

}

void HandleInputs(){

    if(current_level == inGame){
        GameHandleInputs();

        if(ztg_is_key_pressed(KEY_ESCAPE)){
            previous_level = current_level;
            current_level = pauseMenu;
        }

    }else if(current_level == mainMenu){
        if(ztg_is_keyboard_pressed_except(KEY_ESCAPE)){
            current_level = inGame;
        }

        if(ztg_is_key_pressed(KEY_ESCAPE)){
            previous_level = current_level;
            current_level = pauseMenu;
        }
    }else if(current_level == pauseMenu){
        if(ztg_is_key_pressed(KEY_ESCAPE)){
            current_level = previous_level;
        }
    }

}

void Update(float elapsedTime){

    if(current_level == inGame){
        if(!GameUpdate(elapsedTime)){
            current_score = snake_reset();
            current_level = deadScreen;
            new_record = current_score > current_record;

        }
    }else if(current_level == mainMenu){

        ztg_render_string(font_ib8x8u, "Snake Console Game", 140, 80, C_RED);
        ztg_render_string(font_ib8x8u, "Press any key to start", 135, 115, C_RED);
        ztg_render_string(font_ib8x8u, "Made By Luigi Inquieto", 299, 237, C_GRAY);

        if(quit_in_menu_button()){
            ztg_shut_app();
        }


    }else if(current_level == pauseMenu){

        ztg_render_string(font_ib8x8u, "PAUSE", 190, 30, C_RED);

        if(previous_level == inGame){
            if(continue_button()){
                current_level = previous_level;
            }

            if(back_to_main_menu_button()){
                current_level = mainMenu;
            }
        }

        if(options_buttons()){
            current_level = optionsMenu;
        }

        if(quit_in_pause_button()){
            ztg_shut_app();
        }

    }else if(current_level == optionsMenu){

        ztg_render_string(font_ib8x8u, "OPTIONS", 190, 30, C_RED);

        if(enable_old_graphics_button()){
            enable_old_graphics = !enable_old_graphics;
            ztg_old_pixel_look(enable_old_graphics);
            snake_enable_old_graphics(enable_old_graphics);
        }

        if(back_to_options_button()){
            current_level = pauseMenu;
        }

    }else if(current_level == deadScreen){

        lost_screen_duration++;
        ztg_render_string(font_ib8x8u, "YOU LOST", 140, 100, C_RED);
        if(new_record){
            current_record = current_score;
            ztg_render_string(font_ib8x8u, "NEW RECORD ", 140, 115, C_RED);
            ztg_render_string(font_ib8x8u, ztg_format_text("Points : %d", current_score), 229, 115, C_GRAY);
        }else {
            ztg_render_string(font_ib8x8u, ztg_format_text("Points : %d", current_score), 160, 115, C_GRAY);
        }
        if(lost_screen_duration >= 100){
            lost_screen_duration = 0;
            current_level = mainMenu;
        }
    }

    
}