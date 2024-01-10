///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Reporter.cpp
/// @brief Definition of the Reporter class
///
#include "Reporter.h"

#include "../data/CsvData.h"
#include "../data/Ranges.h"
#include "../data/Report.h"
#include "../data/Result.h"
#include "../data/convert/ToRanges.h"
#include "../data/convert/ToTable.h"
#include "../utils/ISettings.h"
#include "../utils/Utility.h"

#include <ranges>
#include <string>
#include <vector>

namespace csvvalidator {
namespace display {

static const std::vector<size_t> getErrorLineNumbers(const data::csv::Content& p_content);
static const std::string getEntryType(const data::csv::ErrorEntry::Type& p_entryType);
static const data::display::Row getErrorAndWarningReport(const size_t p_errorCounter, const size_t p_warningCounter);

Reporter::Reporter(const utils::ISettings& p_settings) :
    m_settings(p_settings)
{
}

const data::display::Report Reporter::process(const data::csv::File& p_csvFile,
                                              const data::csv::Result& p_result) const
{
    LOG("Creating report\n", utils::verbose);
    if (p_csvFile.m_content.empty()) {
        LOG(utils::INDENTATION + "The file has no csv::Fields\n", utils::verbose);
        return {};
    }
    data::display::Report report {};
    report.m_info   = addFileInfo(p_csvFile, p_result);
    report.m_file   = addFileContent(p_csvFile);
    report.m_errors = addErrorList(p_result);
    return report;
}

const data::display::Table Reporter::addFileInfo(const data::csv::File& p_csvFile,
                                                 const data::csv::Result& p_result) const
{
    typedef data::display::Row Row;
    LOG(utils::INDENTATION + "Adding file info\n", utils::verbose);
    data::display::Table table;
    table.push_back(Row({ "File: " + p_csvFile.m_fileName }));
    if (m_settings.errorLevel() < utils::ISettings::ErrorLevel::Error) {
        table.push_back(Row({ "This file contains " + std::to_string(p_result.m_emptyLineCount) + " empty lines" }));
        // table.push_back(Row({ getErrorAndWarningReport(p_result.m_errorCount, p_result.m_warningCount) }));
    }
    return table;
}

const data::display::Table Reporter::addFileContent(const data::csv::File& p_csvFile) const
{
    LOG(utils::INDENTATION + "Adding file content\n", utils::verbose);
    const std::vector<size_t> lineNumbers { getErrorLineNumbers(p_csvFile.m_content) };
    const data::display::Ranges ranges { data::convert::ToRanges::get(lineNumbers,
                                                                      m_settings.linesAroundErrors(),
                                                                      0ULL,
                                                                      p_csvFile.m_content.size() - 1) };
    const data::display::Table table { data::convert::ToTable::get(p_csvFile,
                                                                   ranges,
                                                                   m_settings.labelPosition(),
                                                                   m_settings.emptyLines(),
                                                                   m_settings.tableOutput()) };
    return table;
}

const data::display::Table Reporter::addErrorList(const data::csv::Result& p_result) const
{
    typedef data::csv::ErrorEntry ErrorEntry;
    LOG(utils::INDENTATION + "Adding error list\n", utils::verbose);
    data::display::Table table {};
    const data::csv::ErrorList errorLog { p_result.m_errorList };
    size_t errorCounter { 0 };
    size_t warningCounter { 0 };
    auto f = [&](const auto& e) { return errorLogFilter(e); };
    for (const ErrorEntry& entry : errorLog | std::views::filter(f)) {
        entry.m_type == ErrorEntry::Type::ERR ? ++errorCounter : NULL;
        entry.m_type == ErrorEntry::Type::WARNING ? ++warningCounter : NULL;
        data::display::Row row {};
        row.push_back(getEntryType(entry.m_type) + " in line " + std::to_string(entry.first) + ":");
        row.push_back(entry.second);
        table.push_back(row);
    }
    table.insert(table.begin(), getErrorAndWarningReport(errorCounter, warningCounter));
    return table;
}

bool Reporter::errorLogFilter(const auto& p_entry) const
{
    if (m_settings.errorLevel() == utils::ISettings::ErrorLevel::All) {
        return true;
    }
    return p_entry.m_type == data::csv::ErrorEntry::Type::ERR;
}

static const std::vector<size_t> getErrorLineNumbers(const data::csv::Content& p_content)
{
    typedef data::csv::Content::const_iterator cIt;
    LOG(utils::INDENTATION + "Getting error line numbers\n", utils::verbose);
    std::vector<size_t> errorLineNumbers {};
    const cIt firstRecord = p_content.begin();
    for (cIt currentRecord = firstRecord; currentRecord != p_content.end(); ++currentRecord) {
        if (currentRecord->first.m_state == data::csv::RecordHead::ErrorState::ERR) {
            errorLineNumbers.push_back(std::distance(firstRecord, currentRecord));
        }
    }
    return errorLineNumbers;
}

static const std::string getEntryType(const data::csv::ErrorEntry::Type& p_entryType)
{
    typedef data::csv::ErrorEntry ErrorEntry;
    std::string typeAsString;
    switch (p_entryType) {
    case ErrorEntry::Type::INFO: {
        typeAsString = "Information";
        break;
    }
    case ErrorEntry::Type::WARNING: {
        typeAsString = "Warning";
        break;
    }
    case ErrorEntry::Type::ERR: {
        typeAsString = "Error";
        break;
    }
    default:
        LOG("Program logic error! Wrong ErrorEntry type @ getEntryType()\n", true);
        break;
    }
    return typeAsString;
}

static const data::display::Row getErrorAndWarningReport(const size_t p_errorCount,
                                                         const size_t p_warningCount)
{
    std::string bridgeText {};
    if (p_errorCount == 0 && p_warningCount == 0) {
        bridgeText = "No errors or warnings";
    }
    if (p_errorCount != 0 && p_warningCount != 0) {
        bridgeText = " and ";
    }
    std::string errorText { p_errorCount == 0 ? "" : std::to_string(p_errorCount) + " errors" };
    std::string warningText { p_warningCount == 0 ? "" : std::to_string(p_warningCount) + " warnings" };
    return data::display::Row({ errorText + bridgeText + warningText + " found in the file." });
}

} // namespace display
} // namespace csvvalidator
