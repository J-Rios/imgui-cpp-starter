/**
 * @file    ui_main.cpp
 * @date    2026-01-01
 * @version 1.0.0
 * @brief   Main UI implementation file.
 * @details This component defines the application main UI to be shown.
 * @note    Don't mix app logic and UI, any app logic related code shall be
 *          added to the "core" components.
 */

/*****************************************************************************/

/* Libraries */

// Class Header
#include "ui_main.h"

// Imgui Libraries
#include "imgui.h"

/*****************************************************************************/

/* Factory Simple */

IUI* CreateMainUI()
{
    static MainUI ui;
    return &ui;
}

/*****************************************************************************/

/* Public Methods */

void MainUI::draw(AppContext& ctx)
{
    ImGui::Begin("Main");

    ImGui::Text("Status: %s", ctx.status.c_str());

    if (ImGui::Button("Connect"))
    {   ctx.connect_requested = true;   }

    if (ImGui::Button("Disconnect"))
    {   ctx.disconnect_requested = true;   }

    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

    if (ImGui::Button("Exit"))
    {   ctx.running = false;   }

    ImGui::End();
}

/*****************************************************************************/

/* Private Methods */

// None

/*****************************************************************************/
