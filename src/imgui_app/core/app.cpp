/**
 * @file    app.cpp
 * @date    2026-01-01
 * @version 1.0.0
 * @brief   Application main orchestrator class implementation file.
 * @details This component shall contains the application logic.
 * @note    Don't mix app logic and UI, any UI related code shall be added to
 *          "ui" components.
 */

/*****************************************************************************/

/* Libraries */

// Class Header
#include "app.h"

// Imgui Libraries
#include "imgui.h"
#include "imgui_backend.h"

/*****************************************************************************/

/* Public Methods */

App::App(const char* app_name)
:
    name_app{app_name}
{
    extern IUI* CreateMainUI();

    backend = std::make_unique<IMGUI_BACKEND>();
    ui = CreateMainUI();
}

int App::run()
{
    //static constexpr int window_width_min = 640U;
    //static constexpr int window_heigth_min = 380U;

    setup_ui();

    while (context.running)
    {
        context.update_logic();
        handle_events();
        draw_ui();
    }

    close_ui();

    return 0;
}

/*****************************************************************************/

/* Private Methods - UI */

void App::setup_ui()
{
    backend->init(name_app);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
}

void App::draw_ui()
{
    backend->new_frame();
    ImGui::NewFrame();
    ui->draw(context);
    backend->render();
}

void App::close_ui()
{
    backend->shutdown();
    ImGui::DestroyContext();
}

/*****************************************************************************/

/* Private Methods - Handle Events */

void App::handle_events()
{
    backend->poll_events();

    AppEvent ev;
    while (backend->pop_event(ev))
    {
        if (ev.type == AppEventType::QUIT)
        {   context.running = false;   }
    }
}

/*****************************************************************************/
