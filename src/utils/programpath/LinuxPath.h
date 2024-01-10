///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  LinuxPath.h
/// @brief Declaration of the Linux version of Path class
///
#pragma once

#include "../../utils/Utility.h"

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
    /// INCOMPLETE FUNCTION!
    /// 
    /// @param (void)
    /// @return the path
    /// 
    static std::filesystem::path absolutePath()
    {
        std::filesystem::path programPath {};
        return programPath;
    }
};

} // namespace csvvalidator::utils
