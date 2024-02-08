##
![LOGO](https://github.com/zLouis043/ZTG/blob/main/src/ZTG/resources/ztg_logo.png)
##
![CMAKE](https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white)
![USED LANGUAGE](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![PLATFORM](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![TERMINAL](https://img.shields.io/badge/windows%20terminal-4D4D4D?style=for-the-badge&logo=windows%20terminal&logoColor=white)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![GitHub last commit (branch)](https://img.shields.io/github/last-commit/zLouis043/ZTG/main)

## USAGE 

Compile the library as a static library and include it in your own project include the file ZTG.h

```c

#include "ZTG.H"

```

## Example 

```c

#include "entryPoint.h"

int main(void){
    /*Init the console with a Title, width, height, the resolution on the x axis and y axis*/
    ztg_init("Example Window", 480, 250, 2, 2);

    /*Start the console clock*/
    ztg_start_clock();
    
    /*Check if the app is running*/
    while (ztg_is_app_running()) {

        /*Start the frame iteration*/
        ztg_start_iteration();

        /*Get the inputs from the user*/
        ztg_io();
        /*Handle the inputs received*/
        /*With a custom function or in this while loop*/
        // Example : HandleInputs();

        /*Clear the background*/
        ztg_clear(C_BLACK );
        /*Update the frame passing the elapsed time*/
        /*With a custom function or in this while loop*/
        // Example : Update(ztg_get_elapsed_time());
        /*Swap the console buffers*/
        ztg_swap_buffer();
        
        /*End the frame iteration*/
        ztg_end_iteration();
    }

    /*Sets the console to its original handle*/
    ztg_close();

    return 0;
}

```
