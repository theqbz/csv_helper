///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  IniFile.h
/// @brief Definition of the datastructure to descibe and store records from
///        a .ini file
///

#pragma once

#include "SettingData.h"

#include <map>
#include <string>
#include <utility>
#include <vector>

namespace csvhelper::utils::parser::data {
namespace ini {

///
/// An ini record type contains a pair of < key, value >
///
typedef std::pair<std::string, std::string> Record;

///
/// @brief Container for the records (rows) of an .ini file.
/// A Record consists a pair of < key, value >
///
struct Records : public SettingData
{ };

///
/// @brief Container for a whole .csv file
///
struct File
{
    std::string m_fileName;
    Records m_content;
};

} // namespace ini
} // namespace csvhelper::utils::parser::data
