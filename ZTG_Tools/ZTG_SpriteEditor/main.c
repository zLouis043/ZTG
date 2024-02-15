#include "entryPoint.h"

#define ZFLAGS_IMPLEMENTATION
#include "src/zflags.h"

char ** save_file_name;
char ** load_file_name;

void run(){
    /*Check if the app is running*/

    Start();

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

    save_file_name = zflag_str("save-as", "The name of the saved sprite", "new_sprite");
    load_file_name = zflag_str("load-from", "Load a sprite from memory to modify.", "default");

    if (!zflag_parse(argc, argv)) {
        exit(1);
    }

    zflag_print_flags(stdout);

    /*Init the console with a Title, width, height, the resolution on the x axis and y axis*/
    ztg_init("Sprite Editor", 480, 250, 2, 2);

    if(strcmp(*load_file_name, "default") != 0){
        load_sprite_from_memory(*load_file_name);
        set_save_name_from_file(*load_file_name);
    }

    ztg_setup_callbacks(Start, HandleInputs, Update, NULL);

    ztg_run();
}
