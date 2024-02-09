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

#ifndef ZTG_ZTG_DEFINES_H
#define ZTG_ZTG_DEFINES_H

#include <Windows.h>

#define ZTG_PRIVATE static  
#define ZTGAPI 

#define UNICODE

#define BUFF_MAX_WIDTH 640
#define BUFF_MAX_HEIGHT 340

/*!
 * @typedef Shades
 * @param VERY_DARK 
 * @param DARK
 * @param NORMAL
 * @param LIGHT
 */
typedef enum ztg_shades{
    VERY_DARK = '#',
    DARK = 'o',
    NORMAL = '^',
    LIGHT = '_',
}Shades;  

#define SHADE_VERY_DARK 1 << 7
#define SHADE_DARK 1 << 6
#define SHADE_NORMAL 1 << 5
#define SHADE_LIGHT 1 << 4

#define C_BLACK		    0

#define C_VERY_DARK_BLUE     SHADE_VERY_DARK | FOREGROUND_BLUE	
#define C_VERY_DARK_GREEN    SHADE_VERY_DARK | FOREGROUND_GREEN
#define C_VERY_DARK_CYAN     SHADE_VERY_DARK | FOREGROUND_BLUE | FOREGROUND_GREEN
#define C_VERY_DARK_RED      SHADE_VERY_DARK | FOREGROUND_RED
#define C_VERY_DARK_MAGENTA  SHADE_VERY_DARK | FOREGROUND_RED | FOREGROUND_BLUE
#define C_VERY_DARK_YELLOW   SHADE_VERY_DARK | FOREGROUND_RED | FOREGROUND_GREEN
#define C_VERY_DARK_GRAY     SHADE_VERY_DARK | FOREGROUND_INTENSITY

#define C_DARK_BLUE     SHADE_DARK | FOREGROUND_BLUE	
#define C_DARK_GREEN    SHADE_DARK | FOREGROUND_GREEN
#define C_DARK_CYAN     SHADE_DARK | FOREGROUND_BLUE | FOREGROUND_GREEN
#define C_DARK_RED      SHADE_DARK | FOREGROUND_RED
#define C_DARK_MAGENTA  SHADE_DARK | FOREGROUND_RED | FOREGROUND_BLUE
#define C_DARK_YELLOW   SHADE_DARK | FOREGROUND_RED | FOREGROUND_GREEN
#define C_DARK_GRAY     SHADE_DARK | FOREGROUND_INTENSITY

#define C_GRAY      SHADE_NORMAL | C_DARK_BLUE | C_DARK_GREEN | C_DARK_RED
#define C_BLUE	    SHADE_NORMAL | C_DARK_GRAY | C_DARK_BLUE	
#define C_GREEN	    SHADE_NORMAL | C_DARK_GRAY | C_DARK_GREEN	
#define C_CYAN	    SHADE_NORMAL | C_DARK_GRAY | C_DARK_CYAN
#define C_RED	    SHADE_NORMAL | C_DARK_GRAY | C_DARK_RED
#define C_MAGENTA	SHADE_NORMAL | C_DARK_GRAY | C_DARK_MAGENTA
#define C_YELLOW	SHADE_NORMAL | C_DARK_GRAY | C_DARK_YELLOW

#define C_LIGHT_GRAY    SHADE_LIGHT | C_DARK_BLUE | C_DARK_GREEN | C_DARK_RED
#define C_LIGHT_BLUE	SHADE_LIGHT | C_DARK_GRAY | C_DARK_BLUE	
#define C_LIGHT_GREEN	SHADE_LIGHT | C_DARK_GRAY | C_DARK_GREEN	
#define C_LIGHT_CYAN	SHADE_LIGHT | C_DARK_GRAY | C_DARK_CYAN
#define C_LIGHT_RED	    SHADE_LIGHT | C_DARK_GRAY | C_DARK_RED
#define C_LIGHT_MAGENTA	SHADE_LIGHT | C_DARK_GRAY | C_DARK_MAGENTA
#define C_LIGHT_YELLOW	SHADE_LIGHT | C_DARK_GRAY | C_DARK_YELLOW
#define C_WHITE		    SHADE_LIGHT | C_DARK_GRAY | C_LIGHT_GRAY

#define KEY_0 '0'
#define KEY_1 '1'
#define KEY_2 '2'
#define KEY_3 '3'
#define KEY_4 '4'
#define KEY_5 '5'
#define KEY_6 '6'
#define KEY_7 '7'
#define KEY_8 '8'
#define KEY_9 '9'

#define KEY_A 'A'
#define KEY_B 'B'
#define KEY_C 'C'
#define KEY_D 'D'
#define KEY_E 'E'
#define KEY_F 'F'
#define KEY_G 'G'
#define KEY_H 'H'
#define KEY_I 'I'
#define KEY_J 'J'
#define KEY_K 'K'
#define KEY_L 'L'
#define KEY_M 'M'
#define KEY_N 'N'
#define KEY_O 'O'
#define KEY_P 'P'
#define KEY_Q 'Q'
#define KEY_R 'R'
#define KEY_S 'S'
#define KEY_T 'T'
#define KEY_U 'U'
#define KEY_V 'V'
#define KEY_W 'W'
#define KEY_X 'X'
#define KEY_Y 'Y'
#define KEY_Z 'Z'

#define KEY_BACKSPACE VK_BACK
#define KEY_TAB VK_TAB
#define KEY_RETURN VK_RETURN
#define KEY_SHIFT VK_SHIFT
#define KEY_ALT VK_MENU
#define KEY_BLOCK_MAIUSC VK_CAPITAL
#define KEY_ESCAPE VK_ESCAPE

#define KEY_UP VK_UP
#define KEY_RIGHT VK_RIGHT
#define KEY_LEFT VK_LEFT
#define KEY_DOWN VK_DOWN

#define KEY_INSERT VK_INSERT
#define KEY_DELETE VK_DELETE

#define KEY_PLUS VK_OEM_PLUS
#define KEY_MINUS VK_OEM_MINUS
#define KEY_STAR VK_MULTIPLY
#define KEY_SLASH VK_DIVIDE
#define KEY_PERIOD VK_OEM_PERIOD
#define KEY_COMMA VK_OEM_COMMA

#define KEY_F1 VK_F1
#define KEY_F2 VK_F2
#define KEY_F3 VK_F3
#define KEY_F4 VK_F4
#define KEY_F5 VK_F5
#define KEY_F6 VK_F6
#define KEY_F7 VK_F7
#define KEY_F8 VK_F8
#define KEY_F9 VK_F9
#define KEY_F10 VK_F10
#define KEY_F11 VK_F11
#define KEY_F12 VK_F12
#define KEY_F13 VK_F13
#define KEY_F14 VK_F14
#define KEY_F15 VK_F15
#define KEY_F16 VK_F16
#define KEY_F17 VK_F17
#define KEY_F18 VK_F18
#define KEY_F19 VK_F19
#define KEY_F20 VK_F20
#define KEY_F21 VK_F21
#define KEY_F22 VK_F22
#define KEY_F23 VK_F23
#define KEY_F24 VK_F24

#define KEY_L_SHIFT VK_LSHIFT
#define KEY_R_SHIFT VK_RSHIFT
#define KEY_L_CONTROL VK_LCONTROL
#define KEY_R_CONTROL VK_RCONTROL
#define KEY_L_ALT VK_LMENU
#define KEY_R_ALT VK_RMENU

#define MOUSE_LEFT_BUTTON 0
#define MOUSE_RIGHT_BUTTON 1
#define MOUSE_SCROLL_WHEEL 2

typedef WORD KeyCode;
typedef int MouseButton;
typedef COORD Coord;

typedef struct ztg_color{
    int R;
    int G;
    int B;
    int Intensity;
    int Shade;
}Color;

#define get_index_from_2d(x, y, width) ((y) * (width) + (x))

#define ztg_throw_error_if_not(condition, filename, line, message, ...) \
    if(condition){                                             \
    }else{                                                          \
        fprintf(stderr, message, __VA_ARGS__);                  \
        fprintf(stderr, "\n\tIn %s:%zu.", filename, line);                                                        \\
    }

#define ztg_throw_error_if_not_with_action(condition, action, filename, line, message, ...) \
    if(condition){                                             \
    }else{                                                          \
        fprintf(stderr, message, __VA_ARGS__);                  \
        fprintf(stderr, "\n\tIn %s:%zu.", filename, line);                                                        \
        do{                                                             \
          system("pause");                                                                              \
          (action);                                                                     \
        }while(0) ;                                                               \
    }


#endif //ZTG_ZTG_DEFINES_H
