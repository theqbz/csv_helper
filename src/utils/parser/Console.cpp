///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Console.cpp
/// @brief Functions for console parser
///

#include "Console.h"
#include "data/ConsoleArguments.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace csvhelper::utils {
namespace parser {

typedef std::vector<std::string> StrVec;

static const char KEY_MARKER = '-';

static inline bool hasKey(const data::console::Argument& p_argument);
static inline bool isKey(const std::string& p_text);

const data::console::Arguments Console::createArguments(const StrVec& p_rawData)
{
    data::console::Arguments result {};
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
        const auto [iterator, success] = result.insert(argument);
        if (!success) {
            std::cout << "An error with argument: " << argument.first << ", " << argument.second << "\n";
        }
    }
    return result;
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

} // namespace parser
} // namespace csvhelper::utils
