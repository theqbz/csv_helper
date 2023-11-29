///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  IIniFile.h
/// @brief Interface declaration of IniFile class
///

#pragma once

#include "../utils/datastructure/IniData.h"

namespace csvhelper {
namespace parser {

///
/// @brief Interface for IniFile handler class
///
class IIniFile
{
public:
    IIniFile()          = default;
    virtual ~IIniFile() = default;

    ///
    /// Get the data, stored in a .ini file
    ///
    /// @param (void)
    /// @return a ini::File datastructure, contains ini records
    ///
    virtual inline const csvhelper::utils::ini::File get() const = 0;
};

} // namespace parser
} // namespace csvhelper
