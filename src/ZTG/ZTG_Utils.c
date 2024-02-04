#include <time.h>
#include "ZTG_Utils.h"

int ztg_get_console_width(){
    return window.width;
}

int ztg_get_console_height(){
    return window.height;
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

WORD ztg_get_key_pressed(){
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

COORD ztg_get_mouse_pos(){
    return window.mousePos;
}

void ztg_shut_app(){
    window.isRunning = false;
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