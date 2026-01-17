/**
 * @file    ui_main.h
 * @date    2026-01-01
 * @version 1.0.0
 * @brief   Main UI class definition file.
 * @details This component defines the application main UI to be shown.
 * @note    Don't mix app logic and UI, any app logic related code shall be
 *          added to the "core" components.
 */

/*****************************************************************************/

/* Libraries */

// Class Interface
#include "ui_interface.h"

// Auxiliary Libraries
#include "app_data.h"

/*****************************************************************************/

/* Factory Simple */

/**
 * @brief Create a Main UI object.
 * @param app_context Application Context Data.
 * @param app_state Application State Data.
 * @return IUI* Created abstract UI object.
 */
IUI* CreateMainUI(AppContext& app_context, AppState& app_state);

/*****************************************************************************/

/* UI Class Definition */

/**
 * @brief Main UI to draw.
 */
class MainUI : public IUI
{
    public:

    /**
     * @brief Construct the main UI.
     * @param _context Application context data.
     * @param _state Application state data.
     */
    MainUI(AppContext& app_context, AppState& app_state) :
        context{app_context}, state{app_state} {}

    /**
     * @brief Setup the main UI.
     */
    void setup() override;

    /**
     * @brief Draw the main UI.
     * @param ctx Application data context.
     */
    void draw() override;

    /*************************************************************************/

    /* Private Attributes */

    private:

    /**
     * @brief Reference to Application Context Data.
     */
    AppContext& context;

    /**
     * @brief Reference to Application State Data.
     */
    AppState& state;

    /*************************************************************************/

    /* Private Methods */

    /**
     * @brief Add a Font to be used by the Application.
     * @param data Font data.
     * @param data_len Number of bytes of font data.
     * @param size Font text size.
     */
    ImFont* add_font(const uint8_t* data, const size_t data_len,
        const float size);

    /**
     * @brief Draw Main UI Content region.
     */
    void draw_content();

    /**
     * @brief Draw Main UI Footbar.
     */
    void draw_footbar();

    /**
     * @brief Draw the exit pop-up window.
     */
    void draw_exit_popup();

    /**
     * @brief Change UI Theme.
     */
    void change_theme();
};

/*****************************************************************************/
