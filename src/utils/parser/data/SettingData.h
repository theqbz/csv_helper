///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  SettingData.h
/// @brief Definition of the datastructure to transport settings data
///

#pragma once

#include <map>
#include <string>

namespace csvhelper::utils::parser {
namespace data {

///
/// @brief Container for the list of the options.
/// SettingData consists a list of unique < key, value > pairs
///
struct SettingData : public std::map<std::string, std::string>
{ };

} // namespace data
} // namespace csvhelper::utils::parser
