///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Console.cpp
/// @brief Functions for console parser
///

#include "Console.h"
#include "../data/ConsoleArguments.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace csvvalidator {
namespace parser {

typedef std::vector<std::string> StrVec;

static const char KEY_MARKER = '-';
static const std::set<std::string> HELP_FLAGS { "-h", "--h", "-help", "--help" };

static inline bool hasKey(const data::console::Argument& p_argument);
static inline bool isKey(const std::string& p_text);
static void findHelp(data::console::Arguments p_arguments);
static void printHelp();

const data::console::Arguments Console::parse(const int p_argc,
                                     const char* const p_argv[])
{
    data::console::Arguments arguments = Console::createArguments(Console::convert(p_argc, p_argv));
    findHelp(arguments);
    return arguments;
}

const data::console::Arguments Console::createArguments(const StrVec& p_rawData)
{
    data::console::Arguments arguments {};
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

void findHelp(data::console::Arguments p_arguments)
{
    for (const std::string& helpFlag : HELP_FLAGS) {
        if (p_arguments.find(helpFlag) != p_arguments.end()) {
            printHelp();
        }
    }
}

[[noreturn]] void printHelp()
{
    std::cout << "\n\tThis program can analyze the provided .csv files, seeking for errors.\n"
              << "\tIt can detect if a Record contains more or less Fileds than the number\n"
              << "\tof Labels. The Analyzer identifies Label list in the first non empty row\n"
              << "\tof the file!\n\n"
              << "\tTo parse a file start the program with a filename:\n\n"
              << "\t\t>  csv_validator.exe  path/to/file.csv  [settings]\n\n"
              << "\tSettings:\n\n"
              << "\t-delimiter (char)  -  default value: \";\"\n"
              << "\tthe delimiter between Fields in .csv file\n\n"
              << "\t-emptyLines (string) [ skip | error | leave ]  -  default value: \"skip\"\n"
              << "\tdefines what to do with empty lines\n\n"
              << "\t-emptyFields (char) <empty>: skip empty values  -  default value: \".\"\n"
              << "\tplaceholder for empty values\n\n"
              << "\t-label (string) [ top | inline ]  -  default value: \"top\"\n"
              << "\tdefines where to put the labels\n\n";
    exit(0);
}

} // namespace parser
} // namespace csvvalidator
