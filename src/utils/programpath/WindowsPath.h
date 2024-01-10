///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  WindowsPath.h
/// @brief Declaration of the Windows version of Path class
///
#pragma once

#include "../../utils/Utility.h"

#include <Windows.h>
#undef min
#undef max
#include <filesystem>
#include <string>

namespace csvvalidator::utils {

///
/// @brief The program property class.
///
class Program
{
public:
    ///
    /// @brief Get the absolute path to the program.
    /// 
    /// @param (void)
    /// @return the path
    /// 
    static std::filesystem::path absolutePath()
    {
        wchar_t path[MAX_PATH] {};
        const size_t pathLength = GetModuleFileNameW(nullptr, path, MAX_PATH);
        if (pathLength < 1) {
            LOG("Error getting program path @ absolutePath() | pathLength = " + std::to_string(pathLength) + "\n", true);
        }
        std::string result {};
        result.resize(sizeof(path));
        size_t convertedSize {};
        errno_t error = wcstombs_s(&convertedSize, &result[0], result.size(), path, sizeof(path));
        if (error != 0) {
            LOG("Error converting wchar_t to string @ absolutePath() | error = " + std::to_string(error) + "\n", true);
            return {};
        }
        std::filesystem::path programPath { result };
        programPath.remove_filename();
        LOG("Program path = " + programPath.string() + "\n", utils::verbose)
        return programPath;
    }
};

} // namespace csvvalidator::utils
