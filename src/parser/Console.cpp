///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Console.cpp
/// @brief Functions for console parser
///

#include "Console.h"
#include "../data/ConsoleArguments.h"
#include "../utils/Utility.h"

#include <iostream>
#include <set>
#include <string>
#include <vector>

namespace csvvalidator {
namespace parser {

typedef std::vector<std::string> StrVec;

static inline bool hasKey(const data::console::Argument& p_argument);
static inline bool isKey(const std::string& p_text);
//static void findHelp(data::console::Arguments p_arguments);
[[noreturn]] static void printHelp();

const data::console::Arguments Console::parse(const int p_argc,
                                              const char* const p_argv[])
{
    StrVec rawData = Console::convert(p_argc, p_argv);
    data::console::Arguments arguments {};
    arguments.m_command    = getCommand(&rawData);
    arguments.m_parameters = Console::createParameters(rawData);
    //findHelp(arguments);
    return arguments;
}

const data::console::Parameters Console::createParameters(const StrVec& p_rawData)
{
    data::console::Parameters arguments {};
    StrVec::const_iterator it = p_rawData.begin();
    while (it < p_rawData.end()) {
        data::console::Argument argument {};
        bool argumentDone = false;
        while (it < p_rawData.end() && !argumentDone) {
            if (!hasKey(argument)) {
                argument.first = *it;
                if (!isKey(*it)) {
                    argumentDone = true;
                }
                ++it;
            } else {
                if (!isKey(*it)) {
                    argument.second = *it;
                    ++it;
                }
                argumentDone = true;
            }
        }
        const auto [iterator, success] = arguments.insert(argument);
        if (!success) {
            std::cout << "An error with argument: " << argument.first << ", " << argument.second << "\n";
        }
    }
    return arguments;
}

const std::string Console::getCommand(StrVec* p_rawData)
{
    if (!p_rawData) {
        std::cout << "Program logic error: nullptr as rawData @ getCommand\n";
        return {};
    }
    std::string command {};
    if (!p_rawData->empty()) {
        command = p_rawData->front();
        p_rawData->erase(p_rawData->begin());
    }
    return command;
}

const StrVec Console::convert(const int p_argc, const char* const p_argv[])
{
    StrVec rawData;
    for (int i = 1; i < p_argc; ++i) {
        rawData.emplace_back(p_argv[i]);
    }
    return rawData;
}

static inline bool hasKey(const data::console::Argument& p_argument)
{
    return !p_argument.first.empty();
}

static inline bool isKey(const std::string& p_text)
{
    return !p_text.empty() && *p_text.begin() == KEY_MARKER;
}

//static void findHelp(data::console::Arguments p_arguments)
//{
//    for (const std::string& helpFlag : HELP_COMMANDS) {
//        if (p_arguments.find(helpFlag) != p_arguments.end()) {
//            printHelp();
//        }
//    }
//}

static void printHelp()
{
    std::cout << "\n\tThis program can analyze the provided .csv files, seeking for errors.\n"
              << "\tIt can detect if a Record contains more or less Fileds than the number\n"
              << "\tof Labels. The Analyzer identifies Label list in the first non empty row\n"
              << "\tof the file!\n\n"
              << "\tTo parse a file start the program with a filename:\n\n"
              << "\t\t>  csv_validator.exe  path/to/file.csv  [settings]\n\n"
              << "\tSettings:\n\n"
              << "\t-delimiter (char) - default value: \";\" (the delimiter between Fields in .csv file)\n\n"
              << "\t-emptyLines (string) [ skip | error | leave ] - default value: \"skip\" (defines what to do with empty lines)\n\n"
              << "\t-emptyFields (char) <empty>: skip empty values - default value: \".\" (placeholder for empty values)\n\n"
              << "\t-label (string) [ top | inline ] - default value: \"top\" (defines where to put the labels)\n\n"
              << "\t-errorLines (int) - default value: \"0\" (the number of lines to display before and after the wrong lines; -1: all lines)\n\n ";
    exit(0);
}

} // namespace parser
} // namespace csvvalidator
