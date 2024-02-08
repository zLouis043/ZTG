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

#ifndef ZTG_ZTG_CORE_H
#define ZTG_ZTG_CORE_H

#include <Windows.h>
#include <stdbool.h>
#include "ZTG_Defines.h"
#include "ZTG_Collisions.h"

#ifndef UNICODE
#error Please enable UNICODE for your compiler! VS: Project Properties -> General -> \
Character Set -> Use Unicode.
#endif

/*!
 * @struct mouseButtons
 * @param pressed TYPE : (bool)\n Check if the specified mouse button has been pressed
 * @param released TYPE : (bool)\n Check if the specified mouse button has been released
 * @param held TYPE : (bool)\n Check if the specified mouse button is held
 */
typedef struct ztg_mouseButtons{
    bool pressed;
    bool released;
    bool held;
}mouseButtons;

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
 * @param coordBufSize The size of the window in COORDS
 * @param coordBufCoord The coordinates of the window
 * @param srctWriteRect The buffer rectangle of the console
 * @param inputRecord The record of every inputs given by the user
 * @param events The number of inputs given
 * @param buffer_switch The bool used to check which is the current handle buffer to flush
 * @param isKeyPressed The bool that indicates whether a keyboard key has been pressed
 * @param keyButtonPressed The key pressed
 * @param mouse_old_state The old state of every mouse button
 * @param mouse_new_state The actual state of every mouse button
 * @param mButtons The buttons of the mouse and each state they are
 * @param mousePos The position of the mouse
 * @param time_point_1 The time when the frame is drawn
 * @param time_point_2 The time when the frame draw ended
 * @param elapsed_time The time passed to draw the frame
 * @param iter The current frame number drawn
 * @param FPS The FPS of the application
 * @param BUFFER_MAX_SIZE The buffer console max size
 * @param BUFFER_MAX_IDX THe buffer index max size
 * @param isRunning The bool that indicates if the application is running
 */
struct ztg_window{
    const char * title;
    CHAR_INFO  buffer[BUFF_MAX_WIDTH * BUFF_MAX_HEIGHT];
    size_t width;
    size_t height;

    size_t curr_x;
    size_t curr_y;
    size_t curr_idx;
    HANDLE handles[4];
    HANDLE handle_in;
    COORD coordBufSize;
    Rect bounds;

    COORD coordBufCoord;
    SMALL_RECT srctWriteRect;
    INPUT_RECORD inputRecord[128];
    DWORD events;
    bool buffer_switch;

    bool isKeyPressed;
    WORD keyButtonPressed;
    bool mouse_old_state[5];
    bool mouse_new_state[5];
    mouseButtons mButtons[5];
    COORD mousePos;

    int time_point_1;
    int time_point_2;
    float elapsed_time;
    int iter;

    int FPS;
    size_t BUFFER_MAX_IDX;

    int background_color;
    bool isMaskOn;
    maskType mask_type;
    size_t mask_x1, mask_y1, mask_x2, mask_y2;

    bool isRunning;
    bool enableWrapAround;
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

#endif //ZTG_ZTG_CORE_H
