///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  ProgramPath.h
/// @brief Cover header for WindowsPath.h and LinuxPath.h headers
///

#pragma once

#ifdef _WIN32
#include "WindowsPath.h"
#endif // _WIN32

#ifdef __linux__
#include "LinuxPath.h"
#endif // __linux__
