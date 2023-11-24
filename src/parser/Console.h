/******************************************************************************
 * CSV HELPER by QBZ
 ******************************************************************************
 * Console
 * Create tasks from console arguments
 *****************************************************************************/

#pragma once

#include <map>
#include <string>
#include <vector>

#include "IConsole.h"

namespace csvhelper {
namespace parser {

typedef std::vector<std::string> StrVec;
typedef std::map<std::string, std::string> Tasks;

extern const StrVec consoleArgs(const int p_argc, const char* const p_argv[]);
extern const Tasks parse(const StrVec& p_rawData);

class Console : public IConsole
{
public:
    Console(const int argc, const char* const argv[]) :
        m_taskList(parse(consoleArgs(argc, argv)))
    {
    }

    inline const Tasks getTaskList() const override { return m_taskList; }

private:
    Tasks m_taskList;
};

} // namespace parser
} // namespace csvhelper
