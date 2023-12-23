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

namespace csvvalidator {
namespace data {
namespace console {

///
/// A console argument type contains a pair of < key, value >
///
typedef std::pair<std::string, std::string> Argument;

struct Parameters : public data::SettingData
{ };

///
/// @brief Container for the argument list from commandline.
/// The Argument consists a pair of < key, value >
///
struct Arguments
{
    std::string m_command; ///< The "Task" requested by the user. (This should be the first argument after program name, at index 1.)
    Parameters m_parameters;
};

} // namespace console
} // namespace data
} // namespace csvvalidator
