///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  IniFile.h
/// @brief Definition of parsed .ini file handler class
///

#pragma once

#include "../IFileHandler.h"
#include "data/IniFile.h"

namespace csvhelper::utils {
namespace parser {

///
/// @brief Parse data from .ini file
///
class IniFile
{
public:
    ///
    /// Get the data, stored in a .ini file
    ///
    /// @param (void)
    /// @return a ini::File datastructure, contains ini records
    ///
    static inline const data::ini::File parse(utils::IFileHandler& p_file)
    {
        return read(p_file.get());
    }

    ///
    /// Create a ini::File data from a .ini file.
    /// Parse the file line by line and store the records. (If it find a second
    /// record with the same key, the first occurrence will be stored.)
    ///
    /// @param[in] - p_iniFile : a filestream contains the .ini file
    /// @return a File, contains the records of the .ini file
    ///
    static const data::ini::File read(std::fstream& p_iniFile);

    ///
    /// Read record from a line of a .ini file
    ///
    /// @param[in] - p_line : the line of the file
    /// @return a Record, contains a < key, value > pair
    ///
    static const data::ini::Record line(const std::string& p_line);

    ///
    /// Trim whitespaces from both ends of the text
    ///
    /// @param[in] - p_text : the text to trim
    /// @return the trimmed text
    ///
    static const std::string trim(const std::string& p_text);
};

} // namespace parser
} // namespace csvhelper::utils
