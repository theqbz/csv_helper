/******************************************************************************
 * CSV HELPER by QBZ
 ******************************************************************************
 * IConsole
 * Interface definition of Console
 *****************************************************************************/

#pragma once

#include <map>
#include <string>
#include <vector>

namespace csvhelper {
namespace parser {

typedef std::vector<std::string> StrVec;
typedef std::pair<std::string, std::string> Pair;
typedef std::map<std::string, std::string> Tasks;

class IConsole
{
public:
    IConsole()          = default;
    virtual ~IConsole() = default;

    virtual inline const Tasks getTaskList() const = 0;
};

} // namespace parser
} // namespace csvhelper
