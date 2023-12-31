///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  HelpTask.h
/// @brief Declaration of HelpTask class
///

#pragma once

#include "../utils/Utility.h"
#include "ITask.h"

#include <string>

namespace csvvalidator {
namespace task {

class HelpTask : public ITask
{
public:
    HelpTask(const std::string& p_helpRequest = "") :
        m_request(p_helpRequest)
    {
        LOG("HelpTask created\n", utils::verbose);
    }

    bool run() final;
    void printShortHelp() const;
    void printFullHelp() const;
    void printConfigWriterHelp() const;

private:
    std::string m_request;
};

} // namespace task
} // namespace csvvalidator
