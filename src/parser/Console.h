/******************************************************************************
 * CSV HELPER by QBZ
 ******************************************************************************
 * Console
 * Create tasks from console arguments
 *****************************************************************************/

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

class Console : public IConsole
{
public:
    Console(const int argc, const char* const argv[]) :
        m_arguments(parse(consoleArgs(argc, argv)))
    {
    }

    inline const Arguments get() const final { return m_arguments; }

private:
    Arguments m_arguments;
};

} // namespace parser
} // namespace csvhelper
