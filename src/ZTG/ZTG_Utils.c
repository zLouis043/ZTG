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

#include <time.h>
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
    return window.iter;
}

bool ztg_is_key_pressed(KeyCode Key){
    return (window.isKeyPressed && window.keyButtonPressed == Key);
}

KeyCode ztg_get_key_pressed(){
    return window.keyButtonPressed;
}

bool ztg_is_keyboard_pressed(){
    return (window.isKeyPressed);
}

bool ztg_is_keyboard_pressed_except(KeyCode Key){
    return (window.isKeyPressed && window.keyButtonPressed != Key);
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
    iVec2 mousePos = {
            .x = window.mousePos.X,
            .y = window.mousePos.Y
    };
    return mousePos;
}

void ztg_shut_app(){
    window.isRunning = false;
    SetConsoleActiveScreenBuffer(window.handles[0]);
}

bool ztg_is_app_running(){
    return window.isRunning;
}

void ztg_wrap_around(bool enable){
    window.enableWrapAround = enable;
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