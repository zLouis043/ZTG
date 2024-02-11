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

#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>
//#include <locale.h>
#include <signal.h>
/*#include <io.h>
#include <fcntl.h>*/

#define UNICODE
#define _UNICODE

#include "ZTG_Core.h"
#include "ZTG_Defines.h"
#include "ZTG_Draw.h"

Window window;

void ztg_start_clock(){
    window.time_point_1 = clock();
    window.time_point_2 = clock();
}

void ztg_start_iteration(){
    window.time_point_1 = window.time_point_2;
}

void ztg_end_iteration(){
    window.time_point_2 = clock();
    window.elapsed_time = ((float)(window.time_point_2 - window.time_point_1) / CLOCKS_PER_SEC) * 1000.0f;
    window.FPS = (int)(1.0f / window.elapsed_time);

}

#ifdef _WIN32 // #A
#include <io.h> // #B
#include <fcntl.h> // #C
#else // #D
#include <locale> // #E
#endif

void ztg_init_with_file_and_line(char * filename, size_t line, char * title, short width, short height, short resolution_x, short resolution_y) {

    ztg_throw_error_if_not_with_action((width <= BUFF_MAX_WIDTH && height <= BUFF_MAX_HEIGHT),
                                       (exit(EXIT_FAILURE)),
                                       filename,
                                       line,
                                       "[ERROR] Out of bounds, max size is %dx%d (Inserted size %hux%hu).",
                                       BUFF_MAX_WIDTH, BUFF_MAX_HEIGHT,
                                       width, height);

    /*char *locale;
    locale = setlocale(LC_ALL, "");*/

    //_setmode(_fileno(stdout), _O_U16TEXT);

    /*char* a = setlocale(LC_ALL, "English");
    lollocale(a);*/

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    /*#ifdef _WIN32 // #A
    _setmode(_fileno(stdout), _O_U16TEXT); // #F
    #else // #D
        std::locale::global(std::locale("")); // #H
        std::wcout.imbue(std::locale()); // #I
    #endif*/

    window.is_running = true;
    window.iteration_number = 0;
    window.buffer_switch = true;
    window.is_mask_enabled = false;
    window.is_wrap_around_enabled = false;
    window.is_pixel_look_enabled = false;
    window.BUFFER_MAX_IDX = width * height - 1;
    window.wants_to_quit = false;

    /*!
     * Get the std inputs handle
     */
    window.handle_in = GetStdHandle(STD_INPUT_HANDLE);

    /*!
     * Get the std output handle
     */
    window.handles[0] = GetStdHandle(STD_OUTPUT_HANDLE);

    /*!
     * Create the first Console Screen Buffer used in the swap buffer
     */
    window.handles[1] = CreateConsoleScreenBuffer(
            GENERIC_WRITE,
            0,
            NULL,
            CONSOLE_TEXTMODE_BUFFER,
            NULL);

    /*!
     * Create the second Console Screen Buffer used in the swap buffer
     */
    window.handles[2] = CreateConsoleScreenBuffer(
            GENERIC_WRITE,
            0,
            NULL,
            CONSOLE_TEXTMODE_BUFFER,
            NULL);

    /*!
     * Check if every single handle has been created or got correctly
     */
    if(window.handle_in == INVALID_HANDLE_VALUE){
        system("cls");
        printf("Invalid handle_in\n");
        system("pause");
        exit(EXIT_FAILURE);
    }

    if(window.handles[1] == INVALID_HANDLE_VALUE){
        system("cls");
        printf("Invalid handle n.1\n");
        system("pause");
        exit(EXIT_FAILURE);
    }

    if(window.handles[3] == INVALID_HANDLE_VALUE){
        system("cls");
        printf("Invalid handle n.3\n");
        system("pause");
        exit(EXIT_FAILURE);
    }

    window.width = width;
    window.height = height;

    window.buffer = (CHAR_INFO*)calloc(window.width * window.height, sizeof(CHAR_INFO));

    window.title = title;
    window.buff_size_ad_coord = (COORD) {width, height};
    window.console_write_rect = (SMALL_RECT){ 0, 0, (short)(window.width - 1), (short)(window.height - 1) };
    window.bounds = (Rect){
        .p1.x = 0,
        .p1.y = 0,
        .p2.x = width,
        .p2.y = height
    };

    /*!
     * Set the resolution of the application
     */
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = resolution_x;
    cfi.dwFontSize.Y = resolution_y;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName, L"Consolas");

    /*!
     * Setup every handle size, mode and fonts
     */
    SetConsoleTitle(window.title);
    SMALL_RECT m_rectWindow = { 0, 0, 1, 1 };

    SetConsoleWindowInfo(window.handles[1], TRUE, &m_rectWindow);
    SetConsoleScreenBufferSize(window.handles[1], window.buff_size_ad_coord);
    SetConsoleWindowInfo(window.handles[1], TRUE, &window.console_write_rect);
    SetCurrentConsoleFontEx(window.handles[1],false, &cfi);
    SetConsoleMode(window.handles[1], ENABLE_WRAP_AT_EOL_OUTPUT | DISABLE_NEWLINE_AUTO_RETURN);

    SetConsoleWindowInfo(window.handles[2], TRUE, &m_rectWindow);
    SetConsoleScreenBufferSize(window.handles[2], window.buff_size_ad_coord);
    SetConsoleWindowInfo(window.handles[2], TRUE, &window.console_write_rect);
    SetCurrentConsoleFontEx(window.handles[2],false, &cfi);
    SetConsoleMode(window.handles[2], ENABLE_WRAP_AT_EOL_OUTPUT | DISABLE_NEWLINE_AUTO_RETURN);

    /*!
     * Set the modes for the Inputs Handle
     */
    SetConsoleMode(window.handle_in, ENABLE_WINDOW_INPUT|ENABLE_MOUSE_INPUT|ENABLE_EXTENDED_FLAGS);

}


void ztg_swap_buffer(){

    /*!
     *  Set the current handle buffer to flush
     */
    window.handles[3] = window.buffer_switch ? window.handles[1] : window.handles[2];

    /*!
     * Write the drawn buffer to the current handle buffer
     */
    WriteConsoleOutputW(
            window.handles[3], //! Current handle buffer
            window.buffer,        //! Buffer drawn
            window.buff_size_ad_coord,     //! Size of the console
            window.window_coord_as_coord,    //! Coordinates of the console
            &window.console_write_rect);   //! Rectangle defined of the console

    if (!SetConsoleActiveScreenBuffer(window.handles[3])) { //! Set the current handle buffer as the active console buffer
        exit(EXIT_FAILURE); //! Exit if fail
    }

    window.iteration_number++; //! Increment the iteration
}

/*!
 * @brief The function that sets the state of the mouse and keys of the keyboard with the inputs given by the user
 */
void ztg_io(){

    for (int i = 0; i < 256; i++){
        window.key_new_state[i] = GetAsyncKeyState(i);

        window.kButtons[i].pressed = false;
        window.kButtons[i].released = false;

        if (window.key_new_state[i] != window.key_old_state[i])
        {
            if (window.key_new_state[i] & 0x8000)
            {
                window.kButtons[i].pressed = !window.kButtons[i].held;
                window.kButtons[i].held = true;
            }
            else
            {
                window.kButtons[i].released = true;
                window.kButtons[i].held = false;
            }
        }

        window.key_old_state[i] = window.key_new_state[i];
    }

    GetNumberOfConsoleInputEvents(window.handle_in, &window.events);
    if (window.events > 0){
        ReadConsoleInput(window.handle_in, window.input_record, window.events, &window.events);
    }

    window.is_key_pressed = false;
    for(int i = 0; i < window.events; i++) {
        switch (window.input_record[i].EventType) {
            case KEY_EVENT: {
                window.is_key_pressed = window.input_record[i].Event.KeyEvent.bKeyDown;
                if(window.key_button_pressed != window.input_record[i].Event.KeyEvent.wVirtualKeyCode) {
                    window.key_button_pressed = window.input_record[i].Event.KeyEvent.wVirtualKeyCode;
                }
            }
            case MOUSE_EVENT: {
                //SetConsoleCursorPosition(window.handles[3],window.mouse_pos);
                switch (window.input_record[i].Event.MouseEvent.dwEventFlags){
                    case 0:{
                        for (int m = 0; m < 5; m++){
                            window.mouse_new_state[m] = (window.input_record[i].Event.MouseEvent.dwButtonState & (1 << m)) > 0;
                        }
                    }break;
                    case MOUSE_MOVED:{                    
                        window.mouse_pos.X = window.input_record[i].Event.MouseEvent.dwMousePosition.X;
                        window.mouse_pos.Y = window.input_record[i].Event.MouseEvent.dwMousePosition.Y;
                    }
                    default: break;
                }

                for (int m = 0; m < 5; m++){
                    window.mButtons[m].pressed = false;
                    window.mButtons[m].released = false;

                    if (window.mouse_new_state[m] != window.mouse_old_state[m])
                    {
                        if (window.mouse_new_state[m]){
                            window.mButtons[m].pressed = true;
                            window.mButtons[m].held = true;
                        }else{
                            window.mButtons[m].released = true;
                            window.mButtons[m].held = false;
                        }
                    }

                    window.mouse_old_state[m] = window.mouse_new_state[m];
                }

            }break;
            case WINDOW_BUFFER_SIZE_EVENT:
                SetConsoleScreenBufferSize(window.handles[3], window.buff_size_ad_coord);
                SetConsoleWindowInfo(window.handles[3], TRUE, &window.console_write_rect);
                break;

        }
    }
    //FlushConsoleInputBuffer(window.handle_in);
}

/*!
 * @brief Close the console and set it to its original handle 
 */
void ztg_close(){
    SetConsoleActiveScreenBuffer(window.handles[0]);
    free(window.buffer);
}
