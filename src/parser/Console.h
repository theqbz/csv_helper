///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Console.h
/// @brief Declaration of the console argument parser class
///
/// TODO:
/// Must separate the file from settings!

#pragma once

#include "../data/ConsoleArguments.h"

#include <string>
#include <vector>

namespace csvvalidator {
namespace parser {

typedef std::vector<std::string> StrVec;

///
/// @brief Parse the console arguments
///
class Console
{
public:
    ///
    /// Parse the console arguments to a list fo ordered < key, value > pairs
    ///
    /// @param[in] - p_argc : the number of the console arguments
    /// @param[in] - p_argv : an array of the console arguments
    /// @return console::Arguments datastructure
    ///
    static const data::console::Arguments parse(const int p_argc, const char* const p_argv[]);
    static const data::console::Arguments createArguments(const StrVec& p_rawData);
    static const std::string getCommand(StrVec* p_rawData);
    static const StrVec convert(const int p_argc, const char* const p_argv[]);
};

} // namespace parser
} // namespace csvvalidator
