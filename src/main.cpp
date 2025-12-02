
/*****************************************************************************/

/* Libraries */

// Standard Libraries
#include <iostream>

// Auxiliary Libraries
#include "version_info.h"

// Dear Imgui demo
#include "imgui_demo.h"

/*****************************************************************************/

/* Main Function */

int main(int argc, char* argv[])
{
    using std::printf;
    (void)(argc);
    (void)(argv);

    printf("%s\n", PROJECT_TITLE);

    imgui_demo();

    return 0;
}

/*****************************************************************************/
