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
static std::string aboutHelp();

bool HelpTask::run()
{
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
    std::cout << "No file or command presented.\n"
              << aboutProgram()
              << aboutStart()
              << aboutHelp()
              << "\n";
}

void HelpTask::printFullHelp() const
{
    std::cout //
        << aboutStart()
        << "\n"
        << utils::INDENTATION + "Settings:\n"
        << "\n"
        << utils::INDENTATION + "-delimiter (char)  -  default value: \";\" (the delimiter between Fields in .csv file)\n"
        << "\n"
        << utils::INDENTATION + "-emptyLines (string) [ skip | error | leave ]  -  default value: \"skip\" (defines what to do with empty lines)\n"
        << "\n"
        << utils::INDENTATION + "-emptyFields (char)  -  default value: \".\" (placeholder for empty values; <empty>: skip empty values)\n"
        << "\n"
        << utils::INDENTATION + "-label (string) [ top | inline ]  -  default value: \"top\" (defines where to print the labels)\n"
        << "\n"
        << utils::INDENTATION + "-errorLines (int)  -  default value: \"0\" (the number of lines around errors; -1: all lines)\n"
        << "\n"
        << utils::INDENTATION + "-errorLevel (string) [ all | error ]  -  default value: \"error\" (defines the verbosity of the error log)\n"
        << "\n";
}

void HelpTask::printSettingWriterHelp() const
{
    std::cout << "\n"
              << "Setting writer help... soon.\n"
              << "\n";
    // TODO:
    // Write the setting writer instructions
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
        + utils::INDENTATION + "To parse a file start the program with a filename or a path:\n"
                               "\n"
        + utils::INDENTATION + "\t>  csv_validator.exe  path/to/file  [settings]\n";
}

static std::string aboutHelp()
{
    return "\n"
        + utils::INDENTATION + "To get help, use the  help  command!\n";
}

} // namespace task
} // namespace csvvalidator
