///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  IniData.h
/// @brief Definition of the datastructure to descibe and store records from
///        a .ini file
///

#pragma once

#include <map>
#include <string>
#include <utility>
#include <vector>

namespace csvhelper::utils {
namespace ini {

///
/// An ini record type contains a pair of < key, value >
///
typedef std::pair<std::string, std::string> Record;

///
/// @brief Container for the records (rows) of an .ini file.
/// A Record consists a pair of < key, value >
///
struct Records : public std::map<std::string, std::string>
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
} // namespace csvhelper::utils
