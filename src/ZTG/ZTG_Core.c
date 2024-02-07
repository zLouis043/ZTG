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
#include <locale.h>
#include <signal.h>

#include "ZTG_Core.h"
#include "ZTG_Defines.h"
#include "ZTG_Draw.h"

Window window;

void ztg_start_iteration(){
    window.time_point_1 = clock();
    window.time_point_2 = clock();
}

void ztg_end_iteration(){
    window.time_point_2 = clock();
    window.elapsed_time = ((float)(window.time_point_2 - window.time_point_1) / CLOCKS_PER_SEC) * 1000.0f;
    window.FPS = (int)(1.0f / window.elapsed_time);
    window.time_point_1 = window.time_point_2;
}

void ztg_init_with_file_and_line(char * filename, size_t line, char * title, short width, short height, short resolution_x, short resolution_y) {

    ztg_throw_error_if_not_with_action((width <= BUFF_MAX_WIDTH && height <= BUFF_MAX_HEIGHT),
                                       (exit(EXIT_FAILURE)),
                                       filename,
                                       line,
                                       "[ERROR] Out of bounds, max size is %dx%d (Inserted size %hux%hu).",
                                       BUFF_MAX_WIDTH, BUFF_MAX_HEIGHT,
                                       width, height);

    char *locale;
    locale = setlocale(LC_ALL, "");
    window.isRunning = true;
    window.iter = 0;
    window.buffer_switch = true;
    window.isMaskOn = false;
    window.enableWrapAround = false;
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
    window.title = title;
    window.coordBufSize = (COORD) {width, height};
    window.srctWriteRect = (SMALL_RECT){ 0, 0, (short)(window.width - 1), (short)(window.height - 1) };
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
    SetConsoleMode(window.handles[1], ENABLE_WRAP_AT_EOL_OUTPUT | DISABLE_NEWLINE_AUTO_RETURN);
    SetConsoleScreenBufferSize(window.handles[1], window.coordBufSize);
    SetConsoleWindowInfo(window.handles[1], TRUE, &window.srctWriteRect);
    SetCurrentConsoleFontEx(window.handles[1],false, &cfi);
    SetConsoleMode(window.handles[1], ENABLE_WRAP_AT_EOL_OUTPUT | DISABLE_NEWLINE_AUTO_RETURN);
    SetConsoleScreenBufferSize(window.handles[2], window.coordBufSize);
    SetConsoleWindowInfo(window.handles[2], TRUE, &window.srctWriteRect);
    SetCurrentConsoleFontEx(window.handles[2],false, &cfi);
    SetConsoleMode(window.handles[2], ENABLE_WRAP_AT_EOL_OUTPUT | DISABLE_NEWLINE_AUTO_RETURN);

    /*!
     * Set the modes for the Inputs Handle
     */
    SetConsoleMode(window.handle_in, ENABLE_ECHO_INPUT|ENABLE_LINE_INPUT|ENABLE_MOUSE_INPUT|ENABLE_EXTENDED_FLAGS);

}

void ztg_swap_buffer(){

    /*!
     *  Set the current handle buffer to flush
     */
    window.handles[3] = window.buffer_switch ? window.handles[1] : window.handles[2];

    /*!
     * Write the drawn buffer to the current handle buffer
     */
    WriteConsoleOutput(
            window.handles[3], //! Current handle buffer
            window.buffer,        //! Buffer drawn
            window.coordBufSize,     //! Size of the console
            window.coordBufCoord,    //! Coordinates of the console
            &window.srctWriteRect);   //! Rectangle defined of the console

    ztg_end_iteration(); //! End the iteration

    if (!SetConsoleActiveScreenBuffer(window.handles[3])) { //! Set the current handle buffer as the active console buffer
        exit(EXIT_FAILURE); //! Exit if fail
    }

    window.iter++; //! Increment the iteration
}

/*!
 * @fn The Update function where is defined the frame composition. This function is defined by the programmer
 * @param elapsedTime The time passed during the frame composition
 */
extern void Update(float elapsedTime);

/*!
 * @fn The function that handles the inputs given by the user. This function is defined by the programmer
 */
extern void HandleInputs();

/*!
 * @fn The function that sets the state of the mouse and keys of the keyboard with the inputs given by the user
 */
void ztg_set_input_state(){

    ReadConsoleInput(window.handle_in, window.inputRecord, 128, &window.events);
    window.isKeyPressed = false;
    for(int i = 0; i < window.events; i++) {
        switch (window.inputRecord[i].EventType) {
            case KEY_EVENT: {
                window.isKeyPressed = window.inputRecord[i].Event.KeyEvent.bKeyDown;
                if(window.keyButtonPressed != window.inputRecord[i].Event.KeyEvent.wVirtualKeyCode) {
                    window.keyButtonPressed = window.inputRecord[i].Event.KeyEvent.wVirtualKeyCode;
                }
            }break;
            case MOUSE_EVENT: {
                switch (window.inputRecord[i].Event.MouseEvent.dwEventFlags){
                    case 0:{
                        for (int m = 0; m < 5; m++){
                            window.mouse_new_state[m] = (window.inputRecord[i].Event.MouseEvent.dwButtonState & (1 << m)) > 0;
                        }
                    }break;
                    case MOUSE_EVENT:{
                        SetConsoleCursorPosition(window.handles[3],window.mousePos);
                    }
                    case MOUSE_MOVED:{
                        window.mousePos.X = window.inputRecord[i].Event.MouseEvent.dwMousePosition.X;
                        window.mousePos.Y = window.inputRecord[i].Event.MouseEvent.dwMousePosition.Y;
                    }break;
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
                SetConsoleScreenBufferSize(window.handles[3], window.coordBufSize);
                SetConsoleWindowInfo(window.handles[3], TRUE, &window.srctWriteRect);
                break;

        }
    }
    FlushConsoleInputBuffer(window.handle_in);
}

/*!
 * @fn The function that reads the user-inputs, update the mouse and keyboard state and than run the HandleInputs function defined by the programmer
 */
void ztg_handle_inputs(){
    ztg_set_input_state();
    HandleInputs();
}

/*!
 * @fn The function wrapper for the Update function
 */
void ztg_update(){
    Update(window.elapsed_time);
}

/*!
 * @fn The function containing the application loop
 */
void ztg_run(){
    while (window.isRunning) {
        ztg_handle_inputs();
        ztg_clear(color_black);
        ztg_update();
        ztg_swap_buffer();
    }
    SetConsoleActiveScreenBuffer(window.handles[0]);
}