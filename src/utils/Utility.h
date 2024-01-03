///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Utility.cpp
/// @brief Definition of global constants and macros.
///
/// Storage for magic numbers and values for either single and multiple use
///

#pragma once

#include <filesystem>
#include <iostream>
#include <map>
#include <set>
#include <string>

///
/// @brief Program logger.
///
/// Prints program log, depending on verbosity.
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
///
/// Prints the content of the data::SettingData, depending on verbosity
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
///
/// These default settings can be overridden by the permanent settings, stored
/// by the user in the config file and the command-line arguments, specified
/// when starting the program.
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
/// @brief Default name of the program config file.
///
/// This file stores the permanent user defined settings, which can temporary
/// owervritten with the command-line arguments, specified when starting the
/// propgram.
///
const std::string INI_FILE_NAME { "csvvalidator.ini" };

///
/// @brief Extensions of csv files.
///
/// This set of strings can be accepted as the extension of a "csv" file.
///
const std::set<std::string> CSV_EXTENSIONS { ".csv" };

///
/// @brief CSV field out of bound sign.
///
/// This text indicates if a csv::Field is exceeds the range, defined by the
/// number of csv::Labels.
///
const std::string CSV_INVALID_LABEL = "<INVALID_LABEL>";

///
/// @brief CLI help commands.
///
/// This set of strings can be accepted as *help command* from command-line
/// interface.
///
const std::set<std::string> CLI_COMMANDS_HELP { "-h", "--h", "-help", "--help", "h", "help" };

///
/// @brief CLI config commands.
///
/// This set of string can be accepted as *config command* from command-line
/// interface.
///
const std::set<std::string> CLI_COMMANDS_CONFIG { "config" };

///
/// @brief CLI verbose command.
///
/// This set of strings can be accepted as *verbose command* from command-line
/// interface.
///
const std::set<std::string> CLI_VERBOSE_COMMANDS { "-verbose", "--verbose" };

///
/// @brief CLI no arguments sign
///
/// Task initializer text if there were no command-line arguments presented.
///
const std::string CLI_NO_ARGS { "NO_ARGS_HELP" };

///
/// @brief CLI key marker
///
/// This character indicates the keys during the command-line argument parsing
/// process.
///
const char CLI_KEY_MARKER = '-';

///
/// @brief Display header prompt sign.
///
/// This string signs the label's line in the prompt of a display::Row (if the
/// labels are on top of the csv content).
///
const std::string DISPLAY_ROMPT_HEADER_SIGN { "H" };

///
/// @brief Display neutral prompt sign.
///
/// This string signs the neutral state of csv::Records in the prompt of a
/// display::Row
///
const std::string DISPLAY_PROMPT_NEUTRAL_SIGN { " " };

///
/// @brief Display error prompt sign.
///
/// This string signs the error state of csv::Records in the prompt of a
/// display::Row
///
const std::string DISPLAY_PROMPT_ERROR_SIGN { "*" };

///
/// @brief Display duplicated prompt sign.
///
/// This string signs the duplicated state of csv::Records in the prompt of a
/// display::Row
///
const std::string DISPLAY_PROMPT_DUPLICATED_SIGN { "+" };

///
/// @brief Display prompt closing sing.
///
/// This string closes the promt of a display::Row.
///
const std::string DISPLAY_PROMT_CLOSE_SIGN { ">" };

///
/// @brief INI comment signs.
///
/// This characters can indicate the beginning of a comment in the .ini files.
///
const std::string INI_COMMENT_SIGNS = "#;";

///
/// @brief INI key-value delimiter.
///
/// This characters separates the keys and values in the .ini files.
///
const std::string INI_KEY_VALUE_DELIMITER = "=";

///
/// @brief INI whitespaces.
///
/// This characters are the acceptable whitespaces in .ini files.
///
const std::string INI_WHITESPACE = " \t\n";

///
/// @brief Cosole output indentation.
///
const std::string INDENTATION { "  " };

///
/// @brief Yes answers.
///
/// This set of strings can be accepted as *yes* answer during user
/// communication.
///
const std::set<std::string> YES_ANSWERS { "y", "Y", "yes", "Yes", "YES", "1", "i", "I", "true" };

///
/// @brief No answers
///
/// This set of strings can be accepted as *no* answer during user
/// communication.
///
const std::set<std::string> NO_ANSWERS { "n", "N", "no", "No", "NO", "0", "false" };

///
/// @brief Debug log verbosity.
///
inline bool verbose { false };

///
/// @brief The location of the config file.
///
inline std::filesystem::path configPath {};

///
/// @brief Set the path to the config file.
///
/// @param[in] p_absolutePath : the absolute path of the config file location.
/// @return (void)
///
inline void setConfigPath(const std::filesystem::path& p_absolutePath)
{
    configPath = p_absolutePath;
}

///
/// @brief Get config location.
///
/// @param[in] p_fileName : the name of the config file; not required
/// @return the path to the config file
///
inline const std::filesystem::path getIniLocation(const std::string& p_fileName = INI_FILE_NAME)
{
    std::filesystem::path path { utils::configPath };
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
