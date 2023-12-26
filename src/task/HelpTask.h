///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  HelpTask.h
/// @brief Declaration of HelpTask class
///

#pragma once

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
    }

    bool run() final;
    void printShortHelp() const;
    void printFullHelp() const;
    void printSettingWriterHelp() const;

private:
    std::string m_request;
};

} // namespace task
} // namespace csvvalidator
