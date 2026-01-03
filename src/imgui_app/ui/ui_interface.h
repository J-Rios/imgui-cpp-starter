/**
 * @file    ui_interface.h
 * @date    2026-01-01
 * @version 1.0.0
 * @brief   User Interface class interface file.
 * @details This interface shall be used to define-implement any UI.
 */

/*****************************************************************************/

/* Include Guard */

#pragma once

/*****************************************************************************/

/* Libraries */

// None

/*****************************************************************************/

/* UI Draw Interface */

/**
 * @brief Interface of UI to draw.
 */
struct IUI
{
    /**
     * @brief Draw the UI.
     */
    virtual void draw() = 0;

    /**
     * @brief Destroy the IUI object.
     */
    virtual ~IUI() = default;
};

/*****************************************************************************/
