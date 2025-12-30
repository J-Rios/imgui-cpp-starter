/**
 * @file    version_info.cpp
 * @author  Jose Miguel Rios Rubio <jrios.github@gmail.com>
 * @date    2025-12-03
 * @version 1.0.0
 * @brief   Project version information file to be populate from build system.
 */

/*****************************************************************************/

/* Libraries */

// Header Interface
#include "version_info.h"

/*****************************************************************************/

/* Project Version Information */

const char* const PROJECT_NAME = __PRJ_NAME__;
const char* const PROJECT_VERSION = __PRJ_VERSION__;
const char* const BUILD_TYPE = __BUILD_TYPE__;
const char* const BUILD_DATE = __DATE__;
const char* const BUILD_TIME = __TIME__;

const bool VERSION_DEV = __VERSION_DEV__;
const int VERSION_X = __VERSION_X__;
const int VERSION_Y = __VERSION_Y__;
const int VERSION_Z = __VERSION_Z__;

const char* const PROJECT_TITLE =
    __PRJ_NAME__ " " __PRJ_VERSION__ " (" __DATE__ " - " __TIME__ ")";

/*****************************************************************************/
