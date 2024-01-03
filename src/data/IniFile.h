///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  IniFile.h
/// @brief Declarations of ini::File and ini::Records datastructures.
///
/// These datastructures descibes the structure of an *ini file* and stores
/// data from the file.
///
#pragma once

#include "SettingData.h"

#include <string>
#include <utility>

namespace csvvalidator::data {
namespace ini {

///
/// An ini record type is a pair of < key, value >
///
typedef std::pair<std::string, std::string> Record;

///
/// @brief Container for the records (rows) of an .ini file.
///
/// Records are SettingData and consists a list of unique < key, value > pairs.
///
struct Records : public SettingData
{ };

///
/// @brief Container for a whole .ini file
///
struct File
{
    std::string m_fileName;
    Records m_content;
};

} // namespace ini
} // namespace csvvalidator::data
