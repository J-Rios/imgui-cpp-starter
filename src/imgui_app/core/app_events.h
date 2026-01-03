/**
 * @file    app_events.h
 * @date    2026-01-01
 * @version 1.0.0
 * @brief   Application events definition file.
 * @details The Application Events defines the different events that can be
 * triggered from UI interations or application logic.
 */

/*****************************************************************************/

/* Include Guard */

#pragma once

/*****************************************************************************/

/* Libraries */

// Standard Libraries
#include <cstdint>

/*****************************************************************************/

/* Application Events */

/**
 * @brief Application Events.
 */
enum class AppEventType : int32_t
{
    NONE,
    QUIT,
    // ...

    NUM_EVENTS
};

/**
 * @brief Current application event.
 */
struct AppEvent
{
    AppEventType type;
};

/*****************************************************************************/
