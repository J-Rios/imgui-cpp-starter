/**
 * @file    imgui_backend.h
 * @date    2026-01-01
 * @version 1.0.0
 * @brief   Project configuration file to select ImGui Backend to use based on
 * project build definition.
 */

/*****************************************************************************/

/* Include Guard */

#pragma once

/*****************************************************************************/

/* ImGui Backend Selection */

#if defined(IMGUI_BACKEND_SDL)
    #include "backend_sdl.h"
    #define IMGUI_BACKEND BackendSDL
#elif defined(IMGUI_BACKEND_GLFW)
    #include "backend_glfw.h"
    #define IMGUI_BACKEND BackendGLFW
#else
    #error "ImGui Backend not defined"
#endif

/*****************************************************************************/
