///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  HelpTask.cpp
/// @brief Definition of HelpTask class
///

#include "HelpTask.h"
#include "../utils/Utility.h"

#include <iostream>
#include <string>

namespace csvvalidator {
namespace task {

static std::string aboutProgram();
static std::string aboutStart();
static std::string aboutSettings();
static std::string aboutConfig();
static std::string aboutHelp();

bool HelpTask::run()
{
    DEBUG_LOG("HelpTask running\n", utils::verbose);
    if (m_request.empty()) {
        printFullHelp();
        return true;
    }
    if (m_request == utils::NO_ARGS) {
        printShortHelp();
        return true;
    }
    if (m_request == utils::CONFIG_COMMAND) {
        printSettingWriterHelp();
        return true;
    }
    return false;
}

void HelpTask::printShortHelp() const
{
    DEBUG_LOG("Printing short help\n\n", utils::verbose);
    std::cout << "No file or command presented.\n"
              << aboutProgram()
              << aboutStart()
              << "\n"
              << aboutConfig()
              << aboutHelp()
              << "\n";
}

void HelpTask::printFullHelp() const
{
    DEBUG_LOG("Printing full help\n\n", utils::verbose);
    std::cout //
        << aboutStart()
        << aboutSettings()
        << "\n"
        << aboutConfig()
        << aboutHelp()
        << "\n";
}

void HelpTask::printSettingWriterHelp() const
{
    DEBUG_LOG("Printing config writer help\n\n", utils::verbose);
    std::cout << "\n"
              << utils::INDENTATION + "The program can permanently store user's own settings in an .ini file.\n"
              << utils::INDENTATION + "To use this function start the program with the  config  command and\n"
              << utils::INDENTATION + "provide the settings to be store:\n"
              << "\n"
              << utils::INDENTATION + "\t> csv_validator.exe  config  [arguments: setting's name and value]\n"
              << "\n"
              << utils::INDENTATION + "Multiple arguments can be specified.\n"
              << utils::INDENTATION + "The  config  command with no arguments creates a new .ini file with\n"
              << utils::INDENTATION + "the default settings (or overwrites the existing one).\n"
              << aboutSettings()
              << "\n";
}

std::string aboutProgram()
{
    return "\n"
        + utils::INDENTATION + "This program can analyze the provided csv files, seeking for errors.\n"
        + utils::INDENTATION + "It can detect Records that occur more than once and if a Record\n"
        + utils::INDENTATION + "contains more or less Fileds than the number of Labels. (The Analyzer\n"
        + utils::INDENTATION + "identifies Label list in the first non empty row of the file!)\n";
}

std::string aboutStart()
{
    return "\n"
        + utils::INDENTATION + "To parse a file, start the program with a filename or a path:\n"
                               "\n"
        + utils::INDENTATION + "\t>  csv_validator.exe  path/to/file  [settings]\n";
}

std::string aboutSettings()
{
    return "\n"
        + utils::INDENTATION + "Settings:\n"
        + "\n"
        + utils::INDENTATION + "-delimiter (char)  -  default value: \";\" (the delimiter between Fields in .csv file)\n"
        + "\n"
        + utils::INDENTATION + "-emptyLines (string) [ skip | error | leave ]  -  default value: \"skip\" (defines what to do with empty lines)\n"
        + "\n"
        + utils::INDENTATION + "-emptyFields (char)  -  default value: \".\" (placeholder for empty values; <empty>: skip empty values)\n"
        + "\n"
        + utils::INDENTATION + "-label (string) [ top | inline ]  -  default value: \"top\" (defines where to print the labels)\n"
        + "\n"
        + utils::INDENTATION + "-errorLines (int)  -  default value: \"0\" (the number of lines around errors; -1: all lines)\n"
        + "\n"
        + utils::INDENTATION + "-errorLevel (string) [ all | error ]  -  default value: \"error\" (defines the verbosity of the error log)\n"
        + "\n";
}

std::string aboutConfig()
{
    return "\n"
        + utils::INDENTATION + "To store user's settings permanently, use the  config  command!\n"
        + "\n";
}

std::string aboutHelp()
{
    return "\n"
        + utils::INDENTATION + "To get help, use the  help  command!\n"
        + "\n";
}

} // namespace task
} // namespace csvvalidator
