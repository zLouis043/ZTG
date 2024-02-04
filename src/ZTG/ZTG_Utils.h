#ifndef ZTG_ZTG_UTILS_H
#define ZTG_ZTG_UTILS_H

#include "ZTG_Core.h"

extern Window window;

int ztg_get_console_width();
int ztg_get_console_height();
float ztg_get_elapsed_time();
int ztg_get_frame_count();
bool ztg_is_key_pressed(KeyCode Key);
WORD ztg_get_key_pressed();
bool ztg_is_keyboard_pressed();
bool ztg_is_keyboard_pressed_except(KeyCode Key);
bool ztg_is_key_pressed_between(KeyCode Key_1, KeyCode Key_2);
bool ztg_is_mouse_button_pressed(MouseButton mb);
bool ztg_is_mouse_button_released(MouseButton mb);
bool ztg_is_mouse_button_hold(MouseButton mb);
COORD ztg_get_mouse_pos();
void ztg_shut_app();
void ztg_wrap_around(bool enable);
int ztg_rand_range(int min, int max);

#endif //ZTG_ZTG_UTILS_H
