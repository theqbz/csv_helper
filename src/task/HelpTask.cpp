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

bool HelpTask::run()
{
    if (m_request.empty()) {
        printFullHelp();
        return true;
    }
    if (m_request == NO_ARGS) {
        printShortHelp();
        return true;
    }
    if (m_request == SETTING_WRITER_COMMAND) {
        printSettingWriterHelp();
        return true;
    }
    return false;
}

void HelpTask::printShortHelp() const
{
    std::cout << "No file presented.\n"
              << "To parse a file start the program with a filename:\n\n"
              << "\t>  ./csv_validator.exe  path/to/file.csv  [settings]\n\n"
              << "To get help, use the  -help  flag!\n\n";
}

void HelpTask::printFullHelp() const
{
    std::cout //
        << "\n"
        << "\tThis program can analyze the provided .csv files, seeking for errors.\n"
        << "\tIt can detect Records that occur more than once and if a Record\n"
        << "\tcontains more or less Fileds than the number of Labels. (The Analyzer\n"
        << "\tidentifies Label list in the first non empty row of the file!)\n"
        << "\n"
        << "\tTo parse a file start the program with a filename:\n"
        << "\n"
        << "\t\t>  csv_validator.exe  path/to/file.csv  [settings]\n"
        << "\n"
        << "\tSettings:\n"
        << "\n"
        << "\t-delimiter (char) - default value: \";\" (the delimiter between Fields in .csv file)\n"
        << "\n"
        << "\t-emptyLines (string) [ skip | error | leave ] - default value: \"skip\" (defines what to do with empty lines)\n"
        << "\n"
        << "\t-emptyFields (char) - default value: \".\" (placeholder for empty values; <empty>: skip empty values)\n"
        << "\n"
        << "\t-label (string) [ top | inline ] - default value: \"top\" (defines where to put the labels)\n"
        << "\n"
        << "\t-errorLines (int) - default value: \"0\" (the number of lines around errors; -1: all lines)\n"
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

} // namespace task
} // namespace csvvalidator
