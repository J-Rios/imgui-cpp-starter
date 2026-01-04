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

IUI* CreateMainUI(AppContext& app_context, AppState& app_state)
{
    static MainUI ui(app_context, app_state);
    return &ui;
}

/*****************************************************************************/

/* Public Methods */

void MainUI::setup()
{
    context.io = &(ImGui::GetIO());
    context.style = &(ImGui::GetStyle());

    if (!state.font_default)
    {
        state.font_default = context.io->Fonts->AddFontDefault();
        context.io->FontDefault = state.font_default;
    }
}

void MainUI::draw()
{
    /* Main UI Window */

    // Get current FPS
    state.fps = ImGui::GetIO().Framerate;

    // Get current used Imgui style
    context.style = &(ImGui::GetStyle());

    ImGui::PushFont(state.font_default);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(context.io->DisplaySize);
    ImGui::Begin("Main", nullptr,
        //ImGuiWindowFlags_NoDecoration |  // Uncomment this to hide top bar
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize);

    // Get current window size
    state.window_width = static_cast<int>(ImGui::GetContentRegionAvail().x);
    state.window_height = static_cast<int>(ImGui::GetContentRegionAvail().y);

    draw_content();
    draw_footbar();
    draw_exit_popup();

    ImGui::End();
    ImGui::PopStyleVar();
    ImGui::PopFont();
}

/*****************************************************************************/

/* Private Methods - Draw Content */

void MainUI::draw_content()
{
    static constexpr float margin_x = 24.0f;
    static constexpr float margin_y = 16.0f;
    float spacing = (ImGui::GetStyle().ItemSpacing.x * 2.0f);

    // New Region (child)
    ImGui::BeginChild("Content", ImVec2(0, 0), false);

    // Apply Margin
    ImGui::Dummy(ImVec2(0.0f, margin_y));
    ImGui::Indent(margin_x);

    /***********************/

    // Button: Connect
    if (ImGui::Button("Connect"))
    {   state.connect_requested = true;   }

    // Button: Disconnect
    ImGui::SameLine(0.0f, spacing);
    if (ImGui::Button("Disconnect"))
    {   state.disconnect_requested = true;   }

    // Text: Status
    ImGui::Text("Status: %s", state.status.c_str());

    // Separator
    ImGui::Dummy(ImVec2(0, 10));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 10));

    // Button: Change Theme
    if (ImGui::Button("Change Theme"))
    {   change_theme();   }

    // Text: UI Theme
    ImGui::Text("UI Theme: %s", state.str_theme.c_str());

    // Separator
    ImGui::Dummy(ImVec2(0, 10));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 10));

    // Text: Window Width & Heigth
    ImGui::Text("Window Size: %d x %d",
        state.window_width, state.window_height);

    // Separator
    ImGui::Dummy(ImVec2(0, 10));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 10));

    // Text: Framerate
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

    // Separator
    ImGui::Dummy(ImVec2(0, 10));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 10));

    // Button: Exit
    if (ImGui::Button("Exit"))
    {   state.exit_request = true;   }

    /***********************/

    ImGui::Unindent(margin_x);
    ImGui::EndChild();
}

void MainUI::change_theme()
{
    using e_theme = AppState::e_theme;

    uint32_t theme = static_cast<uint32_t>(state.theme);
    theme = (theme + 1U) % state.NUM_THEMES;
    state.theme = static_cast<e_theme>(theme);

    switch(state.theme)
    {
        case e_theme::DARK:
            ImGui::StyleColorsDark();
            break;
        case e_theme::LIGHT:
            ImGui::StyleColorsLight();
            break;
        case e_theme::CLASSIC:
            ImGui::StyleColorsClassic();
            break;
        case e_theme::CUSTOM:
            ImGui::StyleColorsDark();  // Unimplemented (using Dark again)
            break;
        default:
            break;
    }
}

/*****************************************************************************/
