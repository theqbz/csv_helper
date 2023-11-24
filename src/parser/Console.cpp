/******************************************************************************
 * CSV HELPER by QBZ
 ******************************************************************************
 * ConsoleParser
 * Implementation of ConsolepParser class
 *****************************************************************************/

#include "Console.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace csvhelper {
namespace parser {

typedef std::vector<std::string> StrVec;
typedef std::pair<std::string, std::string> Pair;
typedef std::map<std::string, std::string> Tasks;

const char KEY_MARKER = '-';

const StrVec consoleArgs(const int p_argc, const char* const p_argv[])
{
    StrVec rawData;
    for (int i = 1; i < p_argc; ++i) {
        rawData.emplace_back(p_argv[i]);
    }
    return rawData;
}

inline bool hasKey(const Pair& p_pair)
{
    return !p_pair.first.empty();
}

inline bool isKey(const std::string& p_text)
{
    return !p_text.empty() && *p_text.begin() == KEY_MARKER;
}

const Tasks parse(const StrVec& p_rawData)
{
    Tasks result {};
    StrVec::const_iterator it = p_rawData.begin();
    while (it < p_rawData.end()) {
        Pair pair;
        bool pairDone = false;
        while (it < p_rawData.end() && !pairDone) {
            if (!hasKey(pair)) {
                pair.first = *it;
                if (!isKey(*it)) {
                    pairDone = true;
                }
                ++it;
            } else {
                if (!isKey(*it)) {
                    pair.second = *it;
                    ++it;
                }
                pairDone = true;
            }
        }
        const auto [iterator, success] = result.insert(pair);
        if (!success) {
            std::cout << "An error with console arguments: " << pair.first << ", " << pair.second << "\n";
        }
    }
    return result;
}

} // namespace parser
} // namespace csvhelper
