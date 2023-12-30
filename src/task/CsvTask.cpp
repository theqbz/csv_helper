///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  CsvTask.cpp
/// @brief Definition of CsvTask class
///

#include "CsvTask.h"
#include "../csv/Analyzer.h"
#include "../csv/Parser.h"
#include "../data/CsvData.h"
#include "../data/Report.h"
#include "../data/Result.h"
#include "../display/IDisplay.h"
#include "../display/Reporter.h"
#include "../utils/FileHandler.h"
#include "../utils/ISettings.h"
#include "../utils/Utility.h"

#include <filesystem>
#include <memory>
#include <string>

namespace csvvalidator {
namespace task {

CsvTask::CsvTask(const std::string& p_path,
                 const utils::ISettings& p_settings,
                 std::shared_ptr<display::IDisplay> p_display) noexcept :
    m_settings(p_settings),
    m_file(p_path),
    m_display(p_display)
{
    LOG("CsvTask created\n", utils::verbose);
    if (!m_display.get()) {
        LOG("Program logic error: nullptr as display @ CsvTask constructor\n", true);
        std::exit(1);
    }
}

CsvTask::CsvTask(const std::filesystem::path& p_path,
                 const utils::ISettings& p_settings,
                 std::shared_ptr<display::IDisplay> p_display) noexcept :
    m_settings(p_settings),
    m_file(p_path),
    m_display(p_display)
{
    LOG("CsvTask created\n", utils::verbose);
    if (!m_display.get()) {
        LOG("Program logic error: nullptr as display @ CsvTask constructor\n", true);
        std::exit(1);
    }
}

bool CsvTask::run()
{
    LOG("CsvTask running\n", utils::verbose);
    csv::Parser csvParser(m_settings);
    csv::Analyzer csvAnalyzer(m_settings);
    display::Reporter reporter(m_settings);
    data::csv::File csvFile {};

    {
        utils::FileHandler file(m_file);
        csvFile = csvParser.process(file);
    }
    data::csv::Result csvResult { csvAnalyzer.process(csvFile) };

    data::display::Report report { reporter.process(csvFile, csvResult) };
    m_display->render(report);

    return true;
}

} // namespace task
} // namespace csvvalidator
