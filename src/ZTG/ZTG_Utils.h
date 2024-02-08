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

#ifndef ZTG_ZTG_UTILS_H
#define ZTG_ZTG_UTILS_H

#include "ZTG_Defines.h"
#include "ZTG_Vectors.h"
#include "ZTG_Core.h"

extern Window window;
/*!
 * @brief Get the console width
 * @return The console width
 */
ZTGAPI int ztg_get_console_width();

/*!
 * @brief Get the console height
 * @return The console height
 */
ZTGAPI int ztg_get_console_height();

/*!
 * @brief Allow the drawn geometries to wrap around the console on the x-axis
 * @param enable TYPE : (bool)\n Set the wrap around on or off\n (Default value of wrap around is false)
 */
ZTGAPI void ztg_wrap_around(bool enable);

/*!
 * @brief Get the Console Rectangular Bounds
 * @return The console rectangular bounds
 */
ZTGAPI Rect ztg_get_console_bounds();

/*!
 * @brief Get the elapsed time to draw a frame
 * @return The elapsed time to draw a frame
 */
ZTGAPI float ztg_get_elapsed_time();

/*!
 * @brief Get the current frame count drawn from the start of the application
 * @return The current frame count drawn from the start of the application
 */
ZTGAPI int ztg_get_frame_count();

/*!
 * @brief Check if the key is pressed
 * @param Key TYPE : (KeyCode : WORD)\n The key to check
 * @return TYPE : (bool)\n True if the key was pressed otherwise false
 */
ZTGAPI bool ztg_is_key_pressed(KeyCode Key);

/*!
 * @brief Get the last pressed key
 * @return Key TYPE : (KeyCode : WORD)\n The last pressed key
 */
ZTGAPI KeyCode ztg_get_key_pressed();

/*!
 * @brief Check if any key on the keyboard has been pressed
 * @return TYPE : (bool)\n True if any key has been pressed otherwise false
 */
ZTGAPI bool ztg_is_keyboard_pressed();

/*!
 * @brief Check if any key on the keyboard except one has been pressed
 * @param Key TYPE : (KeyCode : WORD)\n The exception key
 * @return TYPE : (bool)\n True if any key except one has been pressed otherwise false
 */
ZTGAPI bool ztg_is_keyboard_pressed_except(KeyCode Key);

/*!
 * @brief Check if any key on the keyboard except two has been pressed
 * @param Key_1 TYPE : (KeyCode : WORD)\n The first exception key
 * @param Key_2 TYPE : (KeyCode : WORD)\n The second exception key
 * @return TYPE : (bool)\n True if any key except two has been pressed otherwise false
 */
ZTGAPI bool ztg_is_key_pressed_between(KeyCode Key_1, KeyCode Key_2);

/*!
 * @brief Check if the given mouse button has been pressed
 * @param mb TYPE : (MouseButton : int)\n The given mouse button
 * @return TYPE : (bool)\n True it has been pressed otherwise false
 */
ZTGAPI bool ztg_is_mouse_button_pressed(MouseButton mb);

/*!
 * @brief Check if the given mouse button has been released
 * @param mb TYPE : (MouseButton : int)\n The given mouse button
 * @return TYPE : (bool)\n True it has been released otherwise false
 */
ZTGAPI bool ztg_is_mouse_button_released(MouseButton mb);

/*!
 * @brief Check if the given mouse button has been held
 * @param mb TYPE : (MouseButton : int)\n The given mouse button
 * @return TYPE : (bool)\n True it has been held otherwise false
 */
ZTGAPI bool ztg_is_mouse_button_hold(MouseButton mb);

/*!
 * @brief Get the current mouse position in the console boundaries
 * @return TYPE : (iVec2)\n The current mouse position in the console boundaries
 */
ZTGAPI iVec2 ztg_get_mouse_pos();

/*!
 * @brief Close the application
 */
ZTGAPI void ztg_shut_app();

/*!
 * @brief Check if the console is still running 
 */
ZTGAPI bool ztg_is_app_running();

/*!
 * @brief Get an int in a defined range and returns it
 * @param min TYPE : (int)\n The minimum value
 * @param max TYPE : (int)\n The maximum value
 * @return TYPE : (bool)\n The random value in range
 */
ZTGAPI int ztg_rand_range(int min, int max);

/*!
 * @brief Create a new directory from the current bin directory
 * @param name TYPE : (const char *)\n The name of the directory
 */
ZTGAPI void ztg_make_directory(const char* name);

#endif //ZTG_ZTG_UTILS_H
