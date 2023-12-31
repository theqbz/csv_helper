///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  ConsoleArguments.h
/// @brief Declaration of console::Arguments and console::Parameters
///        datastructures.
///
/// These datastructures stores the input from command-line interface.
///
#pragma once

#include "SettingData.h"

#include <string>
#include <utility>

namespace csvvalidator::data {
namespace console {

///
/// A Parameter type is a pair of < key, value >
///
typedef std::pair<std::string, std::string> Parameter;

///
/// @brief Container for the Parameter list.
///
/// Parameters are SettingData and consists a list of unique < key, value >
/// pairs.
///
struct Parameters : public data::SettingData
{ };

///
/// @brief The argument list from commandline.
///
/// Arguments contains the command and the Parameters.
///
struct Arguments
{
    std::string m_command;
    Parameters m_parameters;
};

} // namespace console
} // namespace csvvalidator::data
