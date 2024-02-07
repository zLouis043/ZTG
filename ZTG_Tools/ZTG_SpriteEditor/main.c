#include "entryPoint.h"

#define ZFLAGS_IMPLEMENTATION
#include "src/zflags.h"

char ** save_file_name;
char ** load_file_name;

int main(int argc, char ** argv){

    ztg_init("Sprite Editor", 480, 250, 2, 2);

    save_file_name = zflag_str("save-as", "The name of the saved sprite", "new_sprite");

    if (!zflag_parse(argc, argv)) {
        exit(1);
    }

    ztg_run();
}
