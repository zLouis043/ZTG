#include "GameLoop.h"

#include <string.h>
#include <math.h>

#define ARRAY_LEN(x) (sizeof(x) / sizeof(x[0]))

#define DEBUG 1

#define TILE_WIDTH 15
#define TILE_HEIGHT 15
#define TILE_BASE_COLOR C_BLACK
 
#define TILES_X_COUNT 28
#define TILES_Y_COUNT 14
#define TILES_COUNT TILES_X_COUNT * TILES_Y_COUNT

#define FRUIT_COLOR C_RED
#define SNAKE_TOP_COLOR C_DARK_YELLOW  
#define SNAKE_BOTTOM_COLOR C_DARK_GREEN
#define SNAKE_TAIL_COLOR C_GREEN

typedef struct tile{
    bool has_snake;
}Tile;

typedef struct grid{
    Tile tiles[TILES_X_COUNT][TILES_Y_COUNT];
}Grid;
typedef struct snake_tile SnakeTile;

struct snake_tile{
    fVec2 pos;
    SnakeTile * next;
};

fVec2 s_dir = { 0.1f, 0.0f };

bool g_new_fruit;
iVec2 g_start_grid_coord = {30, 30};
fVec2 g_snake_start_pos = { 3.0f, 3.0f};
iVec2 g_fruit_pos;
Grid g_grid;
SnakeTile * head;
SnakeTile * tail;
float speed = .1f;
int score;
bool g_debug_mode = false;
bool old_graphics = false;


static void snake_init(){
    SnakeTile * new = malloc(sizeof(SnakeTile));
    new->next = NULL;
    new->pos = g_snake_start_pos;

    head = new;
    tail = new;
}

int snake_reset(){
    SnakeTile * track = head;
    SnakeTile * temp;

    while(track != NULL){
        temp = track;
        track = track->next;
        free(temp);
    }

    int curr_score = score;

    GameStart();
    score = 0;

    return curr_score;
}

static void push_tail(){

    SnakeTile * new = malloc(sizeof(SnakeTile));
    new->pos.x = tail->pos.x - abs(s_dir.x);
    new->pos.y = tail->pos.y - abs(s_dir.y);

    new->next = NULL;
    tail->next = new;

    tail = new;

}

static void check_fruit_got(){
    if(!old_graphics){
        if( fabs(head->pos.x - g_fruit_pos.x + s_dir.x) < 1.f &&
            fabs(head->pos.y - g_fruit_pos.y + s_dir.y) < 1.f){
                g_new_fruit = true;
                push_tail();
                push_tail();
                score++;
        }
    }else{
        if( (int)head->pos.x == g_fruit_pos.x &&
            (int)head->pos.y == g_fruit_pos.y){
                g_new_fruit = true;
                push_tail();
                push_tail();
                score++;
        }
    }
}

static void fruit_gen(){
    if (g_new_fruit) {
        g_fruit_pos.x = ztg_rand_range(0, TILES_X_COUNT - 1);
        g_fruit_pos.y = ztg_rand_range(0, TILES_Y_COUNT - 1);
        g_new_fruit = false;
    }
}

static void fruit_draw(){
    if(!old_graphics){

        ztg_draw_filled_circle( (g_start_grid_coord.x + TILE_WIDTH + (g_fruit_pos.x * TILE_WIDTH)) - TILE_WIDTH / 2,
                                (g_start_grid_coord.y + TILE_HEIGHT + (g_fruit_pos.y * TILE_HEIGHT)) - TILE_HEIGHT / 2,
                                6, 
                                C_DARK_RED);

        ztg_draw_filled_circle( (g_start_grid_coord.x + TILE_WIDTH + (g_fruit_pos.x * TILE_WIDTH)) - TILE_WIDTH / 2,
                                (g_start_grid_coord.y + TILE_HEIGHT + (g_fruit_pos.y * TILE_HEIGHT)) - TILE_HEIGHT / 2,
                                4, 
                                FRUIT_COLOR);
        
    }else {
        ztg_draw_filled_rect(   g_start_grid_coord.x + (g_fruit_pos.x * TILE_WIDTH),
                                g_start_grid_coord.y + (g_fruit_pos.y * TILE_HEIGHT),
                                g_start_grid_coord.x + TILE_WIDTH + (g_fruit_pos.x * TILE_WIDTH),
                                g_start_grid_coord.y + TILE_HEIGHT + (g_fruit_pos.y * TILE_HEIGHT),
                                FRUIT_COLOR); 
    }
}

static void snake_move(){

    fVec2 prev_pos;
    prev_pos.x = head->pos.x;
    prev_pos.y = head->pos.y;

    if((int)(head->pos.y - speed) < 0){

        head->pos.y = TILES_Y_COUNT - 1;

    }else if((int)(head->pos.y + speed) >= TILES_Y_COUNT){

        head->pos.y = 0;

    }else if((int)(head->pos.x - speed) < 0){

            head->pos.x = TILES_X_COUNT - 1;

    }else if((int)(head->pos.x + speed) >= TILES_X_COUNT){

        head->pos.x = 0;

    }else {

        head->pos.y += s_dir.y;
        head->pos.x += s_dir.x;

    }

    SnakeTile * track = head;

    if(track->next != NULL){
        track = track->next;
    }

    while(track != NULL){

            fVec2 save_pos;
            save_pos.x = track->pos.x;
            save_pos.y = track->pos.y;

            track->pos.x = prev_pos.x;
            track->pos.y = prev_pos.y;

            track = track->next;

            prev_pos = save_pos;
        }
}

static bool snake_check_crash(){

    SnakeTile * track = head;

    if(track->next != NULL){
        track = track->next;
    }

    while(track != NULL){
        if( fabs(head->pos.x - track->pos.x) < 0.0000001f &&
            fabs(head->pos.y - track->pos.y) < 0.0000001f){
                return true;
        }
        track = track->next;
    }

}

static void snake_draw(){

    SnakeTile * track = head;

    SnakeTile * track_2 = head;
    if(!old_graphics){
        while(track != NULL){

            ztg_draw_filled_rect(   g_start_grid_coord.x + (track->pos.x * TILE_WIDTH),
                                        g_start_grid_coord.y + (track->pos.y * TILE_HEIGHT),
                                        g_start_grid_coord.x + TILE_WIDTH + (track->pos.x * TILE_WIDTH),
                                        g_start_grid_coord.y + TILE_HEIGHT + (track->pos.y * TILE_HEIGHT),
                                        SNAKE_TAIL_COLOR);

            track = track->next;

        }

        while(track_2 != NULL){

            ztg_draw_filled_rect(       g_start_grid_coord.x + (track_2->pos.x * TILE_WIDTH) + 5,
                                        g_start_grid_coord.y + (track_2->pos.y * TILE_HEIGHT) + 5,
                                        g_start_grid_coord.x + TILE_WIDTH + (track_2->pos.x * TILE_WIDTH) - 5,
                                        g_start_grid_coord.y + TILE_HEIGHT + (track_2->pos.y * TILE_HEIGHT) - 5,
                                        SNAKE_BOTTOM_COLOR);

            track_2 = track_2->next;

        }

        ztg_draw_filled_rect(   g_start_grid_coord.x + (head->pos.x * TILE_WIDTH) - 2,
                                        g_start_grid_coord.y + (head->pos.y * TILE_HEIGHT) - 2,
                                        g_start_grid_coord.x + TILE_WIDTH + (head->pos.x * TILE_WIDTH) + 2,
                                        g_start_grid_coord.y + TILE_HEIGHT + (head->pos.y * TILE_HEIGHT) + 2,
                                        SNAKE_TAIL_COLOR);

        ztg_draw_filled_rect(   g_start_grid_coord.x + (head->pos.x * TILE_WIDTH) + 3,
                                        g_start_grid_coord.y + (head->pos.y * TILE_HEIGHT) +3,
                                        g_start_grid_coord.x + TILE_WIDTH + (head->pos.x * TILE_WIDTH) - 3, 
                                        g_start_grid_coord.y + TILE_HEIGHT + (head->pos.y * TILE_HEIGHT) - 3,
                                        SNAKE_TOP_COLOR);
    }else{
        while(track != NULL){

            ztg_draw_filled_rect(   g_start_grid_coord.x + ((int)track->pos.x * TILE_WIDTH),
                                        g_start_grid_coord.y + ((int)track->pos.y * TILE_HEIGHT),
                                        g_start_grid_coord.x + TILE_WIDTH + ((int)track->pos.x * TILE_WIDTH),
                                        g_start_grid_coord.y + TILE_HEIGHT + ((int)track->pos.y * TILE_HEIGHT),
                                        SNAKE_TAIL_COLOR);

            track = track->next;

        }
    }
}

static void snake_draw_debug(){

    if(g_debug_mode && DEBUG){

        SnakeTile * track = head;

        while(track != NULL){

            ztg_draw_rect(   g_start_grid_coord.x + ((int)track->pos.x * TILE_WIDTH),
                                    g_start_grid_coord.y + ((int)track->pos.y * TILE_HEIGHT),
                                    g_start_grid_coord.x + TILE_WIDTH + ((int)track->pos.x * TILE_WIDTH),
                                    g_start_grid_coord.y + TILE_HEIGHT + ((int)track->pos.y * TILE_HEIGHT),
                                    C_RED);

            track = track->next;

        }

    }
}

void GameStart(){
    g_new_fruit = true;
    score = 0;
    snake_init();
    push_tail();
    push_tail();
}

void GameHandleInputs(){

    if(ztg_is_key_pressed_between(KEY_W, KEY_UP)){
        s_dir.x = 0;
        s_dir.y = -speed;
    }

    if(ztg_is_key_pressed_between(KEY_S, KEY_DOWN)){
        s_dir.x = 0;
        s_dir.y = speed;
    }

    if(ztg_is_key_pressed_between(KEY_D, KEY_RIGHT)){
        s_dir.x = speed;
        s_dir.y = 0;
    }

    if(ztg_is_key_pressed_between(KEY_A, KEY_LEFT)){
        s_dir.x = -speed;
        s_dir.y = 0;
    }

    if(ztg_is_key_pressed(KEY_M)){
        g_debug_mode = !g_debug_mode;
    }

}

bool GameUpdate(float elapsedTime){

    snake_move();
    snake_draw();
    snake_draw_debug();
    if(snake_check_crash()) return false;
    check_fruit_got();
    fruit_gen();
    fruit_draw();

    ztg_render_string(font_ib8x8u, ztg_format_text("Points : %d", score), 5, 5, C_YELLOW);

    return true;
    
}


void snake_enable_old_graphics(bool enable){
    old_graphics = enable;
}