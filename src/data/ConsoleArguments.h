///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  ConsoleArguments.h
/// @brief Definition of the datastructure of command line arguments
///

#pragma once

#include "SettingData.h"

#include <string>
#include <utility>

namespace csvvalidator::data {
namespace console {

///
/// A console argument type contains a pair of < key, value >
///
typedef std::pair<std::string, std::string> Argument;

///
/// @brief Container for the argument list from commandline.
/// The Argument consists a pair of < key, value >
///
struct Arguments : public SettingData
{
    std::string m_command; ///< The "Task" requested by the user. (This should be the first argument after program name, at index 1.)
};

} // namespace console
} // namespace csvvalidator::data
