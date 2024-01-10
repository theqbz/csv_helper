///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  SettingData.h
/// @brief Declaradion of SettingData datastructure.
///
/// SettingData datastructure stores the program settings
///
#pragma once

#include <map>
#include <string>

namespace csvvalidator {
namespace data {

///
/// @brief Container for the list of the options.
///
/// SettingData consists a list of unique < key, value > pairs
///
struct SettingData : public std::map<std::string, std::string>
{ };

} // namespace data
} // namespace csvvalidator
