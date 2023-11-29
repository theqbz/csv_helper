///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Console.cpp
/// @brief Functions for console parser
///

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

/// 
/// Create a vector from console arguments.
/// This function skips the first console argument (which is the program name)
/// and read the array from the index 1.
///
/// @param[in] - p_argc : the number of the console arguments
/// @param[in] - p_argv : an array of the console arguments
/// @return a const vector of strings, including the console arguments
/// 
const StrVec consoleArgs(const int p_argc, const char* const p_argv[])
{
    StrVec rawData;
    for (int i = 1; i < p_argc; ++i) {
        rawData.emplace_back(p_argv[i]);
    }
    return rawData;
}

///
/// Check if a given argument has a key.
/// This function checks the Argument's key content.
/// 
/// @param[in] - p_argument : the argument to check
/// @return true, if the argument key is empty
inline bool hasKey(const Argument& p_argument)
{
    return !p_argument.first.empty();
}

///
/// Check if a given string is a key
///
/// @param[in] - p_text : the string to check
/// @return true if the text was a key
/// 
inline bool isKey(const std::string& p_text)
{
    return !p_text.empty() && *p_text.begin() == KEY_MARKER;
}

///
/// Create key-value pairs from argument list.
/// 
/// @param[in] - p_rawDara : a vector of strings as raw argument list
/// @return Arguments formed into ordered < key, value > pairs
/// 
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
