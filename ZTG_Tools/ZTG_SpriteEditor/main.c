#include "entryPoint.h"

#define ZFLAGS_IMPLEMENTATION
#include "src/zflags.h"

char ** save_file_name;
char ** load_file_name;

void run(){
    /*Check if the app is running*/
    while (ztg_is_app_running()) {

        /*Start the frame iteration*/
        ztg_start_iteration();

        /*Get the inputs from the user*/
        ztg_io();
        /*Handle the inputs received*/
        HandleInputs();

        /*Clear the background*/
        ztg_clear(C_BLACK );
        /*Update the frame passing the elapsed time*/
        Update(ztg_get_elapsed_time());
        /*Swap the console buffers*/
        ztg_swap_buffer();
        
        /*End the frame iteration*/
        ztg_end_iteration();

        ztg_set_console_title(ztg_format_text("Sprite Editor | FPS: %3.12f", (1.0f / (window.elapsed_time)) * 1000.0f));
    }
}

int main(int argc, char ** argv){
     /*Init the console with a Title, width, height, the resolution on the x axis and y axis*/
    ztg_init("Sprite Editor", 480, 250, 2, 2);

    save_file_name = zflag_str("save-as", "The name of the saved sprite", "new_sprite");

    if (!zflag_parse(argc, argv)) {
        exit(1);
    }

    /*Start the console clock*/
    ztg_start_clock();

    Start();

    run();

    ztg_close();
}
