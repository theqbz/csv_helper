///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Utility.cpp
/// @brief Definition of constants.
///

#pragma once

#include <map>
#include <set>
#include <string>

namespace csvvalidator {
namespace utils {

///
/// @brief Built-in default settings of the program.
/// These default settings can be overridden by the permanent settings, stored
/// by the user in the .ini file and the command-line arguments, specified when
/// starting the program
///
inline const std::map<std::string, std::string> DEFAULT_SETTINGS {
    { "delimiter", ";" },
    { "errorLines", "0" },
    { "labels", "top" },
    { "emptyFields", "_" },
    { "emptyLines", "skip" },
    { "table", "false" },
    { "diffMode", "off" },
    { "errorLevel", "all" }
};

///
/// @brief Default location and name of the "csvvalidator.ini" file.
/// This file stores the permanent user defined settings, which can temporary
/// owervritten with the command-line arguments, specified when starting the
/// propgram
///
const std::string INI_FILE { "csvvalidator.ini" };

///
/// @brief Extensions of csv files.
/// CsvHelper accepts files as "csv" files only with the extensions listed here
///
const std::set<std::string> CSV_EXTENSIONS { ".csv" };

///
/// @brief Possible help commands in CLI.
/// This variable used in task::TaskFactory and task::HelpTask classes.
///
const std::set<std::string> HELP_COMMANDS { "-h", "--h", "-help", "--help", "h", "help" };

///
/// @brief CLI command and task initializer text to store new setting values.
/// This variable used in task::TaskFactory class.
///
const std::string CONFIG_COMMAND { "config" };

///
/// @brief This character indicates the beginning of a comment.
/// This vasriable used in parser::IniFile.cpp
///
const std::string COMMENT_SIGNS = "#;";

///
/// @brief This character separates the keys and values in .ini files.
/// This vasriable used in parser::IniFile.cpp and task::ConfigTask.cpp
///
const std::string KEY_VALUE_DELIMITER = "=";

///
/// @brief This characters are the acceptable whitespaces in .ini files.
/// This vasriable used in parser::IniFile.cpp
///
const std::string WHITESPACE = " \t\n";

///
/// @brief Task initializer text if there were no command-line arguments presented.
/// This variable used in task::TaskFactory and task::HelpTask classes.
///
const std::string NO_ARGS { "NO_ARGS_HELP" };

///
/// @brief Indicates keys during the command-line argument parsing process.
/// This variable used in Console.cpp
///
const char KEY_MARKER = '-';

///
/// @brief Indicates if the Field exceeds the range, specified by the number of tags
/// This variable used in Parser.cpp
///
const std::string INVALID_LABEL = "<INVALID_LABEL>";

///
/// @brief Sets the intendation for command-line output
/// This variable used in HelpTask.cpp
///
const std::string INDENTATION { "  " };

///
/// @brief Yes answers
///
const std::set<std::string> YES_ANSWERS { "y", "Y", "yes", "Yes", "YES", "1", "i", "I", "true" };

///
/// @brief No answers
///
const std::set<std::string> NO_ANSWERS { "n", "N", "no", "No", "NO", "0", "false" };

} // namespace utils
} // namespace csvvalidator

#define PRINT_SETTINGS(settings)                                                  \
    do {                                                                          \
        std::cout << "\nsettings:\n";                                             \
        std::map<std::string, std::string>::const_iterator it = settings.begin(); \
        for (; it != settings.end(); ++it) {                                      \
            std::cout << it->first << " : " << it->second << "\n";                \
        }                                                                         \
        std::cout << "\n";                                                        \
    } while (false);
