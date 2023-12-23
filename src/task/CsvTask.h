///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  CsvTask.h
/// @brief Declaration of CsvTask class
///

#pragma once

#include "../data/ConsoleArguments.h"
#include "../display/IDisplay.h"
#include "../utils/ISettings.h"
#include "ITask.h"

#include <filesystem>
#include <memory>

namespace csvvalidator {
namespace task {

///
/// @brief A Task to parse, analyze and present a .csv file
///
class CsvTask : public ITask
{
public:
    CsvTask() = delete;

    explicit CsvTask(const data::console::Arguments& p_consoleArguments,
                     const utils::ISettings& p_settings,
                     std::shared_ptr<display::IDisplay> p_display) noexcept;

    explicit CsvTask(const std::filesystem::path& p_path,
                     const utils::ISettings& p_settings,
                     std::shared_ptr<display::IDisplay> p_display) noexcept;

    ///
    /// Execute the task
    ///
    /// @param (void)
    /// @return true, if the execution was successfull
    ///
    bool run() final;

private:
    const utils::ISettings& m_settings;
    const std::filesystem::path m_file;
    std::shared_ptr<display::IDisplay> m_display;
    // utils::IFileHandler& m_file;
    // csv::IParser& m_csvParser;
    // csv::IAnalyzer& m_csvAnalyzer;
    // display::IReporter& m_reporter;
    // display::IDisplay& m_display;
};

} // namespace task
} // namespace csvvalidator
