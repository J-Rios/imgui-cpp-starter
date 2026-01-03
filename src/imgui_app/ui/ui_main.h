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

/*****************************************************************************/

/* Factory Simple */

/**
 * @brief Create a Main UI object.
 * @return IUI* Created abstract UI object.
 */
IUI* CreateMainUI();

/*****************************************************************************/

/* UI Class Definition */

/**
 * @brief Main UI to draw.
 */
class MainUI : public IUI
{
    public:

    /**
     * @brief Draw the main UI.
     * @param ctx Application data context.
     */
    void draw(AppContext& ctx) override;
};

/*****************************************************************************/
