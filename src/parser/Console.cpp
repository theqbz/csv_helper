/******************************************************************************
 * CSV HELPER by QBZ
 ******************************************************************************
 * ConsoleParser
 * Implementation of ConsolepParser class
 *****************************************************************************/

#include "Console.h"
#include "../utils/datastructure/Arguments.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace csvhelper {
namespace parser {

typedef std::vector<std::string> StrVec;
typedef csvhelper::utils::console::Argument Argument;
typedef csvhelper::utils::console::Arguments Arguments;

const char KEY_MARKER = '-';

const StrVec consoleArgs(const int p_argc, const char* const p_argv[])
{
    StrVec rawData;
    for (int i = 1; i < p_argc; ++i) {
        rawData.emplace_back(p_argv[i]);
    }
    return rawData;
}

inline bool hasKey(const Argument& p_argument)
{
    return !p_argument.first.empty();
}

inline bool isKey(const std::string& p_text)
{
    return !p_text.empty() && *p_text.begin() == KEY_MARKER;
}

const Arguments parse(const StrVec& p_rawData)
{
    Arguments result {};
    StrVec::const_iterator it = p_rawData.begin();
    while (it < p_rawData.end()) {
        Argument argument;
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
        const auto [iterator, success] = result.insert(argument);
        if (!success) {
            std::cout << "An error with console argument: " << argument.first << ", " << argument.second << "\n";
        }
    }
    return result;
}

} // namespace parser
} // namespace csvhelper
