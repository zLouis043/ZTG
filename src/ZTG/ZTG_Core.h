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

#ifndef ZTG_CORE_H
#define ZTG_CORE_H

#include <Windows.h>
#include <stdbool.h>
#include "ZTG_Defines.h"
#include "ZTG_Collisions.h"

#ifndef UNICODE
#error Please enable UNICODE for your compiler! VS: Project Properties -> General -> \
Character Set -> Use Unicode.
#endif

/*!
 * @struct keyState
 * @param pressed TYPE : (bool)\n Check if the specified key button has been pressed
 * @param released TYPE : (bool)\n Check if the specified key button has been released
 * @param held TYPE : (bool)\n Check if the specified key button is held
 */
typedef struct ztg_key_states{
    bool pressed;
    bool released;
    bool held;
}keyState;

typedef enum ztg_mask_type{
    INSIDE,
    OUTSIDE
}maskType;

typedef struct ztg_window Window;

/*!
 * @struct Window
 * @param title The title of the window
 * @param width The width of the window
 * @param height The height of the window
 * @param curr_x The current x position of the pixel drawn
 * @param curr_y The current y position of the pixel drawn
 * @param curr_idx The current index of the window write buffer
 * @param handles The handles used in the double buffering. The first is the STD_OUTPUT, the second and third are the alternating handles and the fourth is used to flush the output of the frame drawn
 * @param buff_size_ad_coord The size of the window in COORDS
 * @param window_coord_as_coord The coordinates of the window
 * @param console_write_rect The buffer rectangle of the console
 * @param input_record The record of every inputs given by the user
 * @param events The number of inputs given
 * @param buffer_switch The bool used to check which is the current handle buffer to flush
 * @param is_key_pressed The bool that indicates whether a keyboard key has been pressed
 * @param key_button_pressed The key pressed
 * @param mouse_old_state The old state of every mouse button
 * @param mouse_new_state The actual state of every mouse button
 * @param mButtons The buttons of the mouse and each state they are
 * @param mouse_pos The position of the mouse
 * @param time_point_1 The time when the frame is drawn
 * @param time_point_2 The time when the frame draw ended
 * @param elapsed_time The time passed to draw the frame
 * @param iteration_number The current frame number drawn
 * @param FPS The FPS of the application
 * @param BUFFER_MAX_SIZE The buffer console max size
 * @param BUFFER_MAX_IDX THe buffer index max size
 * @param is_running The bool that indicates if the application is running
 */
struct ztg_window{
    const char * title;
    CHAR_INFO * buffer;
    size_t width;
    size_t height;

    size_t curr_x;
    size_t curr_y;
    size_t curr_idx;
    HANDLE handles[4];
    HANDLE handle_in;
    COORD buff_size_ad_coord;
    Rect bounds;

    COORD window_coord_as_coord;
    SMALL_RECT console_write_rect;
    INPUT_RECORD input_record[32];
    DWORD events;
    bool buffer_switch;

    bool is_key_pressed;
    short key_button_pressed;
    short key_old_state[256];
	short key_new_state[256];
    keyState kButtons[256];
    bool mouse_old_state[5];
    bool mouse_new_state[5];
    keyState mButtons[5];
    COORD mouse_pos;

    int time_point_1;
    int time_point_2;
    float elapsed_time;
    int iteration_number;

    int FPS;
    size_t BUFFER_MAX_IDX;

    int background_color;
    bool is_mask_enabled;
    maskType mask_type;
    Rect mask_bounds;

    bool is_running;
    bool is_wrap_around_enabled;
    bool is_pixel_look_enabled;
    bool wants_to_quit;

};

/*!
 * @brief Start the timer for the elapsed time of each draw iteration
 */
ZTGAPI void ztg_start_clock();

/*!
 * @brief Indicates the time start of the drawing frame
 */
ZTGAPI void ztg_start_iteration();

/*!
 * @brief Indicates the time end of the drawing frame
 */
ZTGAPI void ztg_end_iteration();

/*!
 * @brief Init the console application
 * @param title TYPE : (char*)\n The title of the application
 * @param width TYPE : (short)\n The width of the console
 * @param height TYPE : (short)\n The height of the console
 * @param resolution_x TYPE : (short)\n The width of the character drawn in the console (Used to indicate the pixel density)
 * @param resolution_y TYPE : (short)\n The height of the character drawn in the console (Used to indicate the pixel density)
 */
#define ztg_init(title, width, height, resolution_x, resolution_y) \
           ztg_init_with_file_and_line(__FILE__, __LINE__, title, width, height, resolution_x, resolution_y)
ZTGAPI void ztg_init_with_file_and_line(char * filename, size_t line, char * title, short width, short height, short resolution_x, short resolution_y);

/*!
 * @brief Swap the buffers for every frame
 */
ZTGAPI void ztg_swap_buffer();

/*!
 * @brief Set the input state for the keyboard and mouse
 */
ZTGAPI void ztg_io();

/*!
 * @brief Close the console and set it to its original handle 
 */
ZTGAPI void ztg_close();

#endif //ZTG_CORE_H
