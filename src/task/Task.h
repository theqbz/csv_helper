///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  CsvTask.h
/// @brief Declaration of CsvTask class
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
            utils::ISettings& p_settings,
            utils::IFileHandler& p_file,
            csv::IParser& p_csvParser,
            csv::IAnalyzer& p_csvAnalyzer,
            display::IReporter& p_reporter,
            display::IDisplay& p_display) :
        m_settings(p_settings),
        m_file(p_file),
        m_csvParser(p_csvParser),
        m_csvAnalyzer(p_csvAnalyzer),
        m_reporter(p_reporter),
        m_display(p_display)
    {
    }

    ///
    /// Execute the task
    ///
    /// @param (void)
    /// @return true, if the execution was successfull
    ///
    bool run() final;

private:
    utils::ISettings& m_settings;
    utils::IFileHandler& m_file;
    csv::IParser& m_csvParser;
    csv::IAnalyzer& m_csvAnalyzer;
    display::IReporter& m_reporter;
    display::IDisplay& m_display;
};

} // namespace task
} // namespace csvvalidator
