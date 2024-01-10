///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  IniFile.h
/// @brief Declaration of parser::IniFile class.
///

#pragma once

#include "../data/IniFile.h"

#include <iosfwd>
#include <string>

namespace csvvalidator {
namespace parser {

///
/// @brief *ini* file parser
///
class IniFile
{
public:
    ///
    /// Get the data, stored in a .ini file
    ///
    /// @param[in] p_file : the path/to/file to be parsed as string
    /// @return a ini::File datastructure, contains ini records
    ///
    static const data::ini::File parse(const std::string& p_file);

    ///
    /// Get the data, stored in a .ini file
    ///
    /// @param[in] p_file : the file to be parsed as fstream object
    /// @return a ini::File datastructure, contains ini records
    ///
    static const data::ini::File parse(std::fstream& p_file);
};

} // namespace parser
} // namespace csvvalidator
