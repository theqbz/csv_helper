///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Console.h
/// @brief Declaration of the console argument parser class for csvhelper
///

#pragma once

#include "../utils/datastructure/Arguments.h"
#include "IConsole.h"

#include <map>
#include <string>
#include <vector>

namespace csvhelper {
namespace parser {

typedef std::vector<std::string> StrVec;
typedef csvhelper::utils::console::Arguments Arguments;

extern const StrVec consoleArgs(const int p_argc, const char* const p_argv[]);
extern const Arguments parse(const StrVec& p_rawData);

///
/// @brief Store the parsed console arguments
///
class Console : public IConsole
{
public:
    Console(const int argc, const char* const argv[]) :
        m_arguments(parse(consoleArgs(argc, argv)))
    {
    }

    ///
    /// Get the stored console arguments
    ///
    /// @param (void)
    /// @return console::Arguments datastructure
    inline const Arguments get() const final { return m_arguments; }

private:
    Arguments m_arguments;
};

} // namespace parser
} // namespace csvhelper
