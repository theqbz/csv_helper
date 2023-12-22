///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Utility.cpp
/// @brief Constants definitions
///

#pragma once

#include <set>
#include <string>

///
/// @brief Default location of settings.ini file.
///
const std::string DEFAULT_INI_FILE { "settings.ini" };

///
/// @brief Task initializer text if there were no command-line arguments presented.
/// This variable used in task::TaskFactory and task::HelpTask classes.
///
const std::string NO_ARGS { "NO_ARGS_HELP" };

///
/// @brief CLI command and task initializer text to store new setting values.
/// This variable used in task::TaskFactory class.
///
const std::string SETTING_WRITER_COMMAND { "settings" };

///
/// @brief Possible help commands in CLI.
/// This variable used in task::TaskFactory and task::HelpTask classes.
///
const std::set<std::string> HELP_COMMANDS { "-h", "--h", "-help", "--help", "help" };

///
/// @brief Indicates keys during the command-line argument parsing process.
/// This variable used in Console.cpp
/// 
const char KEY_MARKER = '-';
