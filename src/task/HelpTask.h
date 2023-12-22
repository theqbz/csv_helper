///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  HelpTask.h
/// @brief Declaration of HelpTask class
///

#pragma once

#include "../csv/IAnalyzer.h"
#include "../csv/IParser.h"
#include "../data/ConsoleArguments.h"
#include "../display/IDisplay.h"
#include "../display/IReporter.h"
#include "../utils/IFileHandler.h"
#include "../utils/ISettings.h"
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
