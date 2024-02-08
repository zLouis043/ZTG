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

#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include "ZTG_Utils.h"

int ztg_get_console_width(){
    return window.width;
}

int ztg_get_console_height(){
    return window.height;
}

Rect ztg_get_console_bounds(){
    return window.bounds;
}

float ztg_get_elapsed_time(){
    return window.elapsed_time;
}

int ztg_get_frame_count(){
    return window.iteration_number;
}

bool ztg_is_key_pressed(KeyCode Key){
    return (window.is_key_pressed && window.key_button_pressed == Key);
}

KeyCode ztg_get_key_pressed(){
    return window.key_button_pressed;
}

bool ztg_is_keyboard_pressed(){
    return (window.is_key_pressed);
}

bool ztg_is_keyboard_pressed_except(KeyCode Key){
    return (window.is_key_pressed && window.key_button_pressed != Key);
}

bool ztg_is_key_pressed_between(KeyCode Key_1, KeyCode Key_2){
    return ztg_is_key_pressed(Key_1) || ztg_is_key_pressed(Key_2);
}

bool ztg_is_mouse_button_pressed(MouseButton mb){
    return window.mButtons[mb].pressed;
}

bool ztg_is_mouse_button_released(MouseButton mb){
    return window.mButtons[mb].released;
}

bool ztg_is_mouse_button_hold(MouseButton mb){
    return window.mButtons[mb].held;
}

iVec2 ztg_get_mouse_pos(){
    iVec2 mouse_pos = {
            .x = window.mouse_pos.X,
            .y = window.mouse_pos.Y
    };
    return mouse_pos;
}

void ztg_shut_app(){
    window.is_running = false;
    SetConsoleActiveScreenBuffer(window.handles[0]);
}

bool ztg_is_app_running(){
    return window.is_running;
}

void ztg_wrap_around(bool enable){
    window.is_wrap_around_enabled = enable;
}

void ztg_old_pixel_look(bool enable){
    window.is_pixel_look_enabled = enable;
}

#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
#include <unistd.h>
#elif _WIN32
#include <process.h>
#endif

void SRAND(unsigned int _Seed){
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
    srand((_Seed * getpid());
#elif _WIN32
    srand(_Seed * _getpid());
#endif
}

int ztg_rand_range(int min, int max){
    SRAND((unsigned)time(NULL));
    return rand()%(max + 1 - min) + min;
}

inline void ztg_make_directory(const char* name) {
    CreateDirectory(name, NULL);
}

inline char* ztg_format_text(char * fmt, ...){
    char * buffer = malloc(1024 * sizeof(char));
    va_list args;
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
    int len = strlen(buffer);
    buffer[len] = 0;
    return buffer;
}

inline int ztg_get_color_from_rgb(int R, int G, int B, int Intensity){
    return (R << 2) | (G << 1) | (B << 0) | (Intensity << 3);
}

inline int ztg_get_value_from_color(Color color){
    return (color.R << 2) | (color.G << 1) | (color.B << 0) | (color.Intensity << 3);
}   

Color ztg_get_color_from_value(int color){
    return (Color){
        .R = 1 & (color >> 2),
        .G = 1 & (color >> 1),
        .B = 1 & (color >> 0),
        .Intensity = 1 & (color >> 3)
    };
}