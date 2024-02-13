#include "entryPoint.h"

int main(void){
    /*Init the console with a Title, width, height, the resolution on the x axis and y axis*/
    ztg_init(ztg_format_text("%s", "Snake"), 480, 250, 2, 2);

    ztg_wrap_around(true);

    Start();

    /*Start the console clock*/
    ztg_start_clock();
    
    /*Check if the app is running*/
    while (ztg_is_app_running()) {

        /*Start the frame iteration*/
        ztg_start_iteration();

        /*Get the inputs from the user*/
        ztg_io();
        /*Handle the inputs received*/
        HandleInputs();

        /*Clear the background*/
        ztg_clear(C_BLACK);
        /*Update the frame passing the elapsed time*/
        Update(ztg_get_elapsed_time());
        /*Swap the console buffers*/
        ztg_swap_buffer();
        
        /*End the frame iteration*/
        ztg_end_iteration();

        ztg_set_console_title(ztg_format_text("Snake | FPS: %3.12f", (1.0f / (window.elapsed_time)) * 1000.0f));
    }

    /*Sets the console to its original handle*/
    ztg_close();

    return 0;
}
