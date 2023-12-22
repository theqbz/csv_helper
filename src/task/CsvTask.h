///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  CsvTask.h
/// @brief Declaration of CsvTask class
///

#pragma once

#include "../data/ConsoleArguments.h"
#include "../utils/ISettings.h"
#include "ITask.h"

namespace csvvalidator {
namespace task {

///
/// @brief A Task to parse, analyze and present a .csv file
///
class CsvTask : public ITask
{
public:
    CsvTask() = delete;
    CsvTask(const data::console::Arguments& p_consoleArguments,
            const utils::ISettings& p_settings) :
        m_settings(p_settings)
    {
    }

    ///
    /// Execute the task
    ///
    /// @param (void)
    /// @return true, if the execution was successfull
    ///
    bool run() final
    {
        // TODO:
        // Create run function
        return false;
    }

private:
    const utils::ISettings& m_settings;
    //utils::IFileHandler& m_file;
    //csv::IParser& m_csvParser;
    //csv::IAnalyzer& m_csvAnalyzer;
    //display::IReporter& m_reporter;
    //display::IDisplay& m_display;
};

} // namespace task
} // namespace csvvalidator
