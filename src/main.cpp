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
#include "app.h"
#include "imgui_demo.h"
#include "project_info.h"

/*****************************************************************************/

/* Main Function */

int main(int argc, char* argv[])
{
    (void)(argc);
    (void)(argv);
    int return_code = 0;
    bool run_demo = false;

    std::printf("%s\n", project_info.PROJECT_TITLE);

    // Handle Input Arguments
    if (argc > 1)
    {
        std::string arg_run_demo(argv[1]);
        if (arg_run_demo == "--demo")
        {   run_demo = true;   }
    }

    // Run App or Demo
    if (run_demo)
    {
        std::printf("Running Imgui Demo App\n");
        imgui_demo();
    }
    else
    {
        std::printf("Running Imgui User App\n");
        static App app(project_info);
        return_code = app.run();
    }

    return return_code;
}

/*****************************************************************************/
