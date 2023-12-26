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
/// A Parameter type contains a pair of < key, value >
///
typedef std::pair<std::string, std::string> Parameter;

///
/// @brief Container for the Parameter list as SettingData
/// The Parameter consists a pair of < key, value >
///
struct Parameters : public data::SettingData
{ };

///
/// @brief The argument list from commandline.
/// Arguments contains the command and the Parameters.
///
struct Arguments
{
    std::string m_command; ///< The command ("Task") requested by the user. (This should be the first argument after program name in the console)
    Parameters m_parameters;
};

} // namespace console
} // namespace data
} // namespace csvvalidator
