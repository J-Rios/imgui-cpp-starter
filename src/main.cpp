/**
 * @file    main.cpp
 * @author  Jose Miguel Rios Rubio <jrios.github@gmail.com>
 * @date    2025-12-03
 * @version 1.0.0
 * @brief   Dear Imgui project main file.
 */

/*****************************************************************************/

/* Libraries */

// Standard Libraries
#include <cstring>
#include <iostream>

// Auxiliary Libraries
#include "imgui_app.h"
#include "imgui_demo.h"
#include "version_info.h"

/*****************************************************************************/

/* Main Function */

int main(int argc, char* argv[])
{
    (void)(argc);
    (void)(argv);

    std::printf("%s\n", PROJECT_TITLE);

    if (argc > 1)
    {
        std::string run_demo(argv[1]);
        if (run_demo == "--demo")
        {
            std::printf("Running Imgui Demo App\n");
            imgui_demo();
            return 0;
        }
    }

    std::printf("Running Imgui User App\n");
    imgui_app();

    return 0;
}

/*****************************************************************************/
