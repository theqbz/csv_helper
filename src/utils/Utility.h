///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Utility.cpp
/// @brief Definition of constants.
///

#pragma once

#include <filesystem>
#include <iostream>
#include <map>
#include <set>
#include <string>

///
/// @brief Program logger.
/// Prints log depends on verbosity
///
/// @param[in] - p_text    : the text to print (any streamable type)
/// @param[in] - p_verbose : the verbosity (bool type)
///
#define LOG(p_text, p_verbose)   \
    do {                         \
        if (p_verbose == true) { \
            std::cout << p_text; \
        }                        \
    } while (false);

///
/// @brief Setting printer.
/// Prints the content of the data::SettingData depend on verbosity
///
/// @param[in] p_settings : the data::SettingData to print
/// @param[in] p_verbose  : the verbosity (bool type)
///
#define PRINT_SETTINGS(p_settings, p_verbose)                                                              \
    do {                                                                                                   \
        if (p_verbose == true) {                                                                           \
            if (p_settings.empty()) {                                                                      \
                std::cout << csvvalidator::utils::INDENTATION << "< empty >\n";                            \
            }                                                                                              \
            std::map<std::string, std::string>::const_iterator it = p_settings.begin();                    \
            for (; it != p_settings.end(); ++it) {                                                         \
                std::cout << csvvalidator::utils::INDENTATION << it->first << ":\t" << it->second << "\n"; \
            }                                                                                              \
        }                                                                                                  \
    } while (false);

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
const std::string INI_FILE_NAME { "csvvalidator.ini" };

///
/// @brief Extensions of csv files.
/// CsvHelper accepts files as "csv" files only with the extensions listed here
///
const std::set<std::string> CSV_EXTENSIONS { ".csv" };

///
/// @brief Possible help commands in CLI.
/// This variable used in task::TaskFactory and task::HelpTask classes.
///
const std::set<std::string> CLI_COMMANDS_HELP { "-h", "--h", "-help", "--help", "h", "help" };

///
/// @brief CLI command and task initializer text to store new setting values.
/// This variable used in task::TaskFactory class.
///
const std::string CLI_COMMANDS_CONFIG { "config" };

///
/// @brief This character indicates the beginning of a comment.
/// This vasriable used in parser::IniFile.cpp
///
const std::string INI_COMMENT_SIGNS = "#;";

///
/// @brief This character separates the keys and values in .ini files.
/// This vasriable used in parser::IniFile.cpp and task::ConfigTask.cpp
///
const std::string INI_KEY_VALUE_DELIMITER = "=";

///
/// @brief This characters are the acceptable whitespaces in .ini files.
/// This vasriable used in parser::IniFile.cpp
///
const std::string INI_WHITESPACE = " \t\n";

///
/// @brief Task initializer text if there were no command-line arguments presented.
/// This variable used in task::TaskFactory and task::HelpTask classes.
///
const std::string CLI_NO_ARGS { "NO_ARGS_HELP" };

///
/// @brief Indicates keys during the command-line argument parsing process.
/// This variable used in Console.cpp
///
const char CLI_KEY_MARKER = '-';

///
/// @brief Indicates if the Field exceeds the range, specified by the number of tags
/// This variable used in Parser.cpp
///
const std::string CSV_INVALID_LABEL = "<INVALID_LABEL>";

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

///
/// @brief Verbose command variations
///
const std::set<std::string> CLI_VERBOSE_COMMANDS { "-verbose", "--verbose" };

///
/// @brief Debug log verbosity
///
inline bool verbose { false };

///
/// @brief Program location
///
inline std::filesystem::path programPath {};

///
/// @brief Program path
///
/// @param[in] p_absolutePath : the absolute path of the executable
/// @return (void)
///
inline void setProgramPath(const std::filesystem::path& p_absolutePath)
{
    programPath = p_absolutePath;
}

///
/// @brief Get config location
///
/// @param[in] p_fileName : the name of the config file; not required
/// @return the path to the config file
///
inline const std::filesystem::path getIniLocation(const std::string& p_fileName = INI_FILE_NAME)
{
    std::filesystem::path path { utils::programPath };
    const std::filesystem::path iniPath { path.replace_filename(p_fileName) };
    LOG("Config file location = " + iniPath.string() + "\n", utils::verbose);
    return iniPath;
}

inline const bool iniFileExists(const std::filesystem::path& p_iniFilePath)
{
    const std::filesystem::file_status status { std::filesystem::status(p_iniFilePath) };
    if (status.type() != std::filesystem::file_type::regular) {
        LOG(p_iniFilePath.string() + " is not a valid file\n", utils::verbose);
        return false;
    }
    return true;
}

} // namespace utils
} // namespace csvvalidator
