#include <stdio.h>
#include "entryPoint.h"

typedef struct cell{
    int width;
    int height;
    int default_color;
    int curr_color;
    bool is_empty;
}Cell;

typedef struct grid{
    int x;
    int y;
    int padding_x;
    int padding_y;
    Rect bounds;
    int cells_count_x;
    int cells_count_y;
    Cell cells[256];
}Grid;

int g_color_selected = 15;
int g_mouse_color = color_black;
int g_cell_width = 20;
int g_cell_height = 20;
int g_max_cells = 16;
Cell g_cell_states[256];
Grid g_grid = {
        .x = 60,
        .y = 50,
        .padding_x = 5,
        .padding_y = 5,
        .cells_count_x = 8,
        .cells_count_y = 8
};

bool g_is_grid_initialized = false;
bool g_is_8x8_grid = true;
bool g_is_size_updated = false;
bool g_fill_mode = false;
bool g_is_file_name_typing = false;
bool g_default_sprite_name = true;

char g_file_name[256];
int g_file_name_cur_idx = 0;

int g_tools_buttons_offset = 5;
int g_tools_buttons_width = 50;
int g_tools_buttons_height = 20;
int g_tools_buttons_start_x = 10;
int g_tools_buttons_start_y = 20;
int g_tools_buttons_idx = 0;

int g_save_pop_up_start_y = 237;
int g_save_pop_up_end_y = 217;
int g_save_time_pop_up = 100;
int g_save_timer_pop_up = 0;
int g_save_pop_up_width = 114;
int g_save_pop_up_height = 20;
int g_save_pop_up_x = 361;
int g_save_pop_up_y = 217;
bool g_saved = false;

bool g_has_changes = true;

static int draw_buttons(int buttons_count, int x, int y, int width, int height, int padding){

    int button_clicked = color_black;

    for(int i = 0; i < buttons_count; i++){
        Rect button_bounds = {
                .p1.x = x + (i * (width + padding)),
                .p1.y = y,
                .p2.x = (x + width) + (i * (width + padding)),
                .p2.y = y + height
        };
        Button button = {
                .bounds = button_bounds,
                .color_base = i+1,
                .color_hover = i+1,
                .color_pressed = color_black,
        };

        if(ztg_button(button, "", 0, 0, color_red)){
            button_clicked = i+1;
        }
    }
    return button_clicked;
}

static bool draw_cell(int x1, int y1, int width, int height, int color){

    Rect cell_r = {
            .p1.x = x1,
            .p1.y = y1,
            .p2.x = x1 + width,
            .p2.y = y1 + height
    };

    Button cell_b = {
            .bounds = cell_r,
            .color_base = color,
            .color_hover = color,
            .color_pressed = color
    };

    return ztg_button(cell_b, "", 0,0, color);
}

static void grid_init(int cell_width, int cell_height){

    g_grid.bounds.p1.x = 60;
    g_grid.bounds.p1.y = 50;
    g_grid.bounds.p2.x = g_grid.x + (g_cell_width * g_grid.cells_count_x + 2 * g_grid.padding_x);
    g_grid.bounds.p2.y = g_grid.y + (g_cell_height * g_grid.cells_count_y + 2 * g_grid.padding_y);

    for(int i = 0; i < g_grid.cells_count_x; i++){
        for(int j = 0; j < g_grid.cells_count_y; j++){
            int idx = get_index_from_2d(i, j, g_max_cells);
            g_grid.cells[idx].width = cell_width;
            g_grid.cells[idx].height = cell_height;
            if(g_is_size_updated && g_grid.cells[idx].curr_color != g_grid.cells[idx].default_color){
                g_grid.cells[idx].curr_color = g_cell_states[idx].curr_color;
                g_grid.cells[idx].is_empty = g_cell_states[idx].is_empty;
            }else {
                g_grid.cells[idx].default_color = (i + j) % 2 == 0 ? color_black : color_gray;
                g_grid.cells[idx].curr_color = g_grid.cells[idx].default_color;
                g_grid.cells[idx].is_empty = true;
            }
        }
    }
    g_is_size_updated = false;
}

int g_flood_fill_iteration = 0;
int g_flood_fill_limit = 300;

static void fill_color(int x, int y, int new_color, int old_color){

    if(g_flood_fill_iteration > g_flood_fill_limit) return;
    g_flood_fill_iteration++;

    if(x >= g_grid.cells_count_x ||
     x < 0 ||
     y >= g_grid.cells_count_y ||
     y < 0) return;

    int idx = get_index_from_2d(x, y, g_max_cells);

    if(g_grid.cells[idx].curr_color == old_color || g_grid.cells[idx].is_empty) {
        g_grid.cells[idx].curr_color = new_color;
        g_grid.cells[idx].is_empty = false;

        fill_color(x + 1, y, new_color, old_color);
        fill_color(x - 1, y, new_color, old_color);
        fill_color(x, y + 1, new_color, old_color);
        fill_color(x, y - 1, new_color, old_color);
    }

}

static void set_cell_color(int x, int y, int new_color){

        int idx = get_index_from_2d(x, y, g_max_cells);
        g_grid.cells[idx].curr_color = new_color == 0 ? g_grid.cells[idx].default_color : new_color;
        g_grid.cells[idx].is_empty = new_color == 0 ? true : false;

}

static void grid_draw(){

    ztg_draw_filled_rect(g_grid.bounds.p1.x, g_grid.bounds.p1.y,
                         g_grid.bounds.p2.x, g_grid.bounds.p2.y,
                         color_white);

    int start_x = g_grid.x + g_grid.padding_x;
    int start_y = g_grid.y + g_grid.padding_y;

    for(int i = 0; i < g_grid.cells_count_x; i++) {
        for (int j = 0; j < g_grid.cells_count_y; j++) {
            int idx = get_index_from_2d(j, i, g_max_cells);
            if(draw_cell(start_x + (i * g_grid.cells[idx].width),
                      start_y + (j * g_grid.cells[idx].height),
                      g_grid.cells[idx].width,
                      g_grid.cells[idx].height,
                      g_grid.cells[idx].curr_color)){
                g_has_changes = true;
                if(g_fill_mode){
                    g_flood_fill_iteration = 0;
                    g_flood_fill_limit = g_fill_mode ? 600 : 300;
                    fill_color(j, i, g_mouse_color, g_grid.cells[idx].curr_color);
                }else{
                    set_cell_color(j, i, g_mouse_color);
                }
            }
        }
    }
}

static void erase_mode_button(){

    g_tools_buttons_idx = 0;

    Rect erase_r = {
            .p1.x = g_tools_buttons_start_x + (g_tools_buttons_idx * g_tools_buttons_width) + (g_tools_buttons_idx * g_tools_buttons_offset),
            .p1.y = g_tools_buttons_start_y,
            .p2.x = (g_tools_buttons_start_x + g_tools_buttons_width) + (g_tools_buttons_idx * g_tools_buttons_width) + (g_tools_buttons_idx * g_tools_buttons_offset),
            .p2.y = g_tools_buttons_start_y + g_tools_buttons_height
    };

    Button erase_b = {
            .bounds = erase_r,
            .color_base = color_gray,
            .color_hover = color_white,
            .color_pressed = color_blue
    };

    if(ztg_button(erase_b, "Erase", 5, 5, color_black)){
        g_mouse_color = 0;
        g_fill_mode = false;
    }
}

static bool reset_button(){
    g_tools_buttons_idx++;

    Rect reset_r = {
            .p1.x = g_tools_buttons_start_x + (g_tools_buttons_idx * g_tools_buttons_width) + (g_tools_buttons_idx * g_tools_buttons_offset),
            .p1.y = g_tools_buttons_start_y,
            .p2.x = (g_tools_buttons_start_x + g_tools_buttons_width) + (g_tools_buttons_idx * g_tools_buttons_width) + (g_tools_buttons_idx * g_tools_buttons_offset),
            .p2.y = g_tools_buttons_start_y + g_tools_buttons_height
    };

    Button reset_b = {
            .bounds = reset_r,
            .color_base = color_gray,
            .color_hover = color_white,
            .color_pressed = color_blue
    };

    return ztg_button(reset_b, "Reset", 5, 5, color_black);
}

static bool fill_mode_button(){

    g_tools_buttons_idx++;

    Rect fill_r = {
            .p1.x = g_tools_buttons_start_x + (g_tools_buttons_idx * g_tools_buttons_width) + (g_tools_buttons_idx * g_tools_buttons_offset),
            .p1.y = g_tools_buttons_start_y,
            .p2.x = (g_tools_buttons_start_x + g_tools_buttons_width) + (g_tools_buttons_idx * g_tools_buttons_width) + (g_tools_buttons_idx * g_tools_buttons_offset),
            .p2.y = g_tools_buttons_start_y + g_tools_buttons_height
    };

    Button fill_b = {
            .bounds = fill_r,
            .color_base = color_gray,
            .color_hover = color_white,
            .color_pressed = color_blue
    };

    if(ztg_button(fill_b, "Fill", 5, 5, color_black)){
        g_fill_mode = true;
    }
}

static bool paint_mode_button(){

    g_tools_buttons_idx++;

    Rect paint_r = {
            .p1.x = g_tools_buttons_start_x + (g_tools_buttons_idx * g_tools_buttons_width) + (g_tools_buttons_idx * g_tools_buttons_offset),
            .p1.y = g_tools_buttons_start_y,
            .p2.x = (g_tools_buttons_start_x + g_tools_buttons_width) + (g_tools_buttons_idx * g_tools_buttons_width) + (g_tools_buttons_idx * g_tools_buttons_offset),
            .p2.y = g_tools_buttons_start_y + g_tools_buttons_height
    };

    Button paint_b = {
            .bounds = paint_r,
            .color_base = color_gray,
            .color_hover = color_white,
            .color_pressed = color_blue
    };

    if(ztg_button(paint_b, "Paint", 5, 5, color_black)){
        g_fill_mode = false;
    }
}

static bool change_canvas_size_button(){

    ztg_render_string(font_ib8x8u, "Canvas Size: ", g_tools_buttons_start_x + g_tools_buttons_width + 200, g_grid.y + 5, color_white);

    Rect canvas_size_r = {
            .p1.x = g_tools_buttons_start_x + 350,
            .p1.y = g_grid.y,
            .p2.x = g_tools_buttons_start_x + g_tools_buttons_width + 350,
            .p2.y = g_grid.y + 20
    };

    Button canvas_size_b = {
            .bounds = canvas_size_r,
            .color_base = color_black,
            .color_hover = color_gray,
            .color_pressed = color_blue
    };

    char * label= g_is_8x8_grid ? " 8x8" : "16x16";

    return ztg_button(canvas_size_b, label, 5, 5, color_white);
}

static bool set_name_button(){

    ztg_render_string(font_ib8x8u, "File name:", g_tools_buttons_start_x + g_tools_buttons_width + 200, g_grid.y + 30, color_white);

    Rect set_name_r = {
            .p1.x = g_tools_buttons_start_x + 330,
            .p1.y = g_grid.y + 22,
            .p2.x = g_tools_buttons_start_x + g_tools_buttons_width + 390,
            .p2.y = g_grid.y + 42
    };

    Button set_name_b = {
            .bounds = set_name_r,
            .color_base = color_black,
            .color_hover = color_gray,
            .color_pressed = color_blue
    };

    if(g_default_sprite_name){
        return ztg_button(set_name_b, *save_file_name, 5, 5, color_white);
    }else {
        return ztg_button(set_name_b, g_file_name, 5, 5, color_white);
    }
}

static bool save_button(){

    Rect save_r = {
            .p1.x = g_tools_buttons_start_x + 280,
            .p1.y = g_grid.y + 57,
            .p2.x = g_tools_buttons_start_x + g_tools_buttons_width + 313,
            .p2.y = g_grid.y + 77
    };

    Button save_b = {
            .bounds = save_r,
            .color_base = color_black,
            .color_hover = color_gray,
            .color_pressed = color_blue
    };

    return ztg_button(save_b, "Save file", 5, 5, color_white);
}

static inline void make_directory(const char* name) {
    CreateDirectory(name, NULL);
}

static void save(){

    char file_name[512];

    make_directory("Sprites");

    memset(file_name, 0, 256);
    strcat(file_name, "Sprites/");
    if(g_default_sprite_name) {
        strcat(file_name, *save_file_name);
    }else{
        strcat(file_name, g_file_name);
    }
    strcat(file_name, ".zsprt");

    FILE * fp = fopen(file_name, "w+");

    if(!fp){
        exit(1);
    }

    fprintf(fp, "%d %d\n", g_grid.cells_count_x, g_grid.cells_count_y);

    for(size_t i = 0; i < g_grid.cells_count_y; i++){
        for(size_t j = 0; j < g_grid.cells_count_x; j++){
            int idx = get_index_from_2d(i, j, 16);
            if(g_grid.cells[idx].is_empty){
                fprintf(fp, "17");
            }else {
                fprintf(fp, "%d", g_grid.cells[idx].curr_color);
            }
            fprintf(fp, " ");
        }
        fprintf(fp, "\n");
    }

    fclose(fp);

    g_has_changes = false;
}

static void draw_mode(){
    ztg_render_string(font_ib8x8u, "Mode: ", 5,237, color_gray);
    if(g_fill_mode){
        ztg_render_string(font_ib8x8u, "FILL", 54,237, color_blue);
    }else if(g_mouse_color == 0){
        ztg_render_string(font_ib8x8u, "ERASE", 54,237, color_blue);
    }else{
        ztg_render_string(font_ib8x8u, "DRAW", 54,237, color_blue);
    }
}

static void draw_saved_popup(){
    if(g_save_timer_pop_up < g_save_time_pop_up && g_saved) {

        if(g_save_timer_pop_up > g_save_time_pop_up / 2){
            if(g_save_pop_up_y < g_save_pop_up_start_y + 20){
                g_save_pop_up_y += 7;
            }else{
                g_save_pop_up_y = g_save_pop_up_start_y + 20;
            }
        }else {
            if (g_save_pop_up_y > g_save_pop_up_end_y + 1) {
                g_save_pop_up_y -= 7;
            } else {
                g_save_pop_up_y = g_save_pop_up_end_y;
            }
        }

        ztg_draw_filled_rect(g_save_pop_up_x, g_save_pop_up_y,
                             g_save_pop_up_x + g_save_pop_up_width,
                             g_save_pop_up_y + g_save_pop_up_height,
                             color_red);
        ztg_render_string(font_ib8x8u, "Sprite Saved", g_save_pop_up_x + 5, g_save_pop_up_y + 5, color_white);
        g_save_timer_pop_up++;
        g_save_pop_up_y++;
    }else{
        g_save_pop_up_y = g_save_pop_up_start_y;
        g_save_timer_pop_up = 0;
        g_saved = false;
    }
}

bool g_wants_to_quit = false;

static void save_before_exit(){

    int save_before_quit_width = 220;
    int save_before_quit_height = 100;
    int save_before_quit_x = ztg_get_console_width() / 2 - save_before_quit_width / 2;
    int save_before_quit_y = ztg_get_console_height() / 2 - save_before_quit_height / 2;

    if(g_has_changes && g_wants_to_quit){
        ztg_draw_filled_rect(save_before_quit_x, save_before_quit_y,
                             save_before_quit_x + save_before_quit_width,
                             save_before_quit_y + save_before_quit_height,
                             color_black);
        ztg_render_string(font_ib8x8u, "There are unsaved changes.", save_before_quit_x + 5, save_before_quit_y + 5, color_white);
        ztg_render_string(font_ib8x8u, "Are you sure you want to", save_before_quit_x + 5, save_before_quit_y + 5 + 13, color_white);
        ztg_render_string(font_ib8x8u, "quit?", save_before_quit_x + 5, save_before_quit_y + 5 + 13 + 13, color_white);

        Rect yes_r = {
                .p1.x = save_before_quit_x + 5,
                .p1.y = save_before_quit_y + save_before_quit_height - 35,
                .p2.x = save_before_quit_x + 40,
                .p2.y = save_before_quit_y + save_before_quit_height - 15
        };

        Button yes_b = {
                .bounds = yes_r,
                .color_base = color_dark_red,
                .color_hover = color_red,
                .color_pressed = color_black
        };

        if(ztg_button(yes_b, "YES", 5, 5, color_white)){
            ztg_shut_app();
        }

        Rect no_r = {
                .p1.x = save_before_quit_x + save_before_quit_width - 40,
                .p1.y = save_before_quit_y + save_before_quit_height - 35,
                .p2.x = save_before_quit_x + save_before_quit_width - 5,
                .p2.y = save_before_quit_y + save_before_quit_height - 15
        };

        Button no_b = {
                .bounds = no_r,
                .color_base = color_dark_blue,
                .color_hover = color_blue,
                .color_pressed = color_black
        };

        if(ztg_button(no_b, "NO", 5, 5, color_white)){
            g_wants_to_quit = false;
        }
    }else if(g_wants_to_quit){
        ztg_shut_app();
    }
}

void Update(float elapsedTime){

    ztg_render_string(font_ib8x8u, "COLORS: ", 5, 5, color_white);

    g_color_selected = draw_buttons(15, 69, 5, 10, 10, 5);

    if(g_color_selected > 0){
        g_mouse_color = g_color_selected;
    }

    if(!g_is_grid_initialized){
        grid_init(g_cell_width ,g_cell_height);
        g_is_grid_initialized = true;
    }

    erase_mode_button();
    fill_mode_button();
    paint_mode_button();

    if(reset_button()){
        g_is_grid_initialized = false;
    }

    if(change_canvas_size_button()){
        g_is_8x8_grid = !g_is_8x8_grid;
        g_grid.cells_count_x = g_is_8x8_grid ? 8 : 16;
        g_grid.cells_count_y = g_is_8x8_grid ? 8 : 16;
        g_cell_width = g_is_8x8_grid ? 20 : 10;
        g_cell_height = g_is_8x8_grid ? 20 : 10;
        g_is_grid_initialized = false;
        g_is_size_updated = true;

        for(size_t i = 0; i < 16; i++){
            for(size_t j = 0; j < 16; j++){
                size_t idx = get_index_from_2d(j, i, g_max_cells);
                g_cell_states[idx].curr_color = g_grid.cells[idx].curr_color;
                g_cell_states[idx].is_empty = g_grid.cells[idx].is_empty;
            }
        }
    }

    if(set_name_button()){
        g_default_sprite_name = false;
        g_is_file_name_typing = true;
    }

    if(save_button()){
        g_saved = true;
        save();
    }

    draw_saved_popup();

    grid_draw();
    draw_mode();

    save_before_exit();

    iVec2 mousePos = ztg_get_mouse_pos();
    ztg_draw_filled_circle(mousePos.x, mousePos.y, 2, g_mouse_color);

}

static bool is_valid_char(KeyCode kc){
    return ((kc >= '0' && kc <= '9') ||
            (kc >= 'A' && kc <= 'Z'));
}

void HandleInputs(){

    if(ztg_is_key_pressed(KEY_ESCAPE) || (ztg_is_key_pressed(KEY_Q) && !g_is_file_name_typing)){
        g_wants_to_quit = true;
    }

    if(g_is_file_name_typing && ztg_is_keyboard_pressed()){
        if(is_valid_char(ztg_get_key_pressed()) && g_file_name_cur_idx < 13){
            g_file_name[g_file_name_cur_idx] = (char)ztg_get_key_pressed();
            g_file_name_cur_idx++;
        }else if(ztg_is_key_pressed(KEY_BACKSPACE) && g_file_name_cur_idx >= 0){
            g_file_name[g_file_name_cur_idx] = 0;
            g_file_name_cur_idx--;
        }else if(ztg_is_key_pressed(KEY_RETURN)){
            g_is_file_name_typing = false;
            g_file_name[g_file_name_cur_idx] = 0;
        }
    }
}
