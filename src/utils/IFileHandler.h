///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  IFileHandler.h
/// @brief Interface declaration of the FileHandler class
///

#pragma once

#include <iosfwd>
#include <string>

namespace csvvalidator {
namespace utils {

///
/// @brief Interface for FileHandler class
///
class IFileHandler
{
public:
    IFileHandler()          = default;
    virtual ~IFileHandler() = default;

    ///
    /// Get a reference to the file.
    ///
    /// @param (void)
    /// @return a reference to the file
    ///
    virtual std::fstream& get() = 0;

    ///
    /// Get the name of the file
    /// 
    /// @param (void)
    /// @return the name of the file
    /// 
    virtual const std::string fileName() const = 0;
};

} // namespace utils
} // namespace csvvalidator
