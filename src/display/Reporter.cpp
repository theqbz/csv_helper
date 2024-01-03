///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Reporter.h
/// @brief Function definitions of the Reporter class
///

#include "Reporter.h"
#include "../data/Ranges.h"
#include "../data/Report.h"
#include "../data/Result.h"
#include "../data/convert/ToRanges.h"
#include "../data/convert/ToTable.h"
#include "../utils/ISettings.h"
#include "../utils/Utility.h"

#include <iostream>
#include <limits>
#include <ranges>
#include <string>
#include <vector>

namespace csvvalidator {
namespace display {


static const std::vector<size_t> getErrorLineNumbers(const data::csv::Content& p_content);
static const std::string getEntryType(const data::csv::ErrorEntry::Type& p_entryType);
static const data::display::Row getFirstErrorRow(const size_t p_errorCounter, const size_t p_warningCounter);

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
    LOG(utils::INDENTATION + "Adding file info\n", utils::verbose);
    data::display::Row file_name({ "File: " + p_csvFile.m_fileName });
    data::display::Row empty_lines {};
    if (m_settings.errorLevel() < utils::ISettings::ErrorLevel::Error) {
        empty_lines.assign({ "This file contains "
                             + std::to_string(p_result.m_emptyLineCount)
                             + " empty lines" });
    }
    return data::display::Table({ file_name, empty_lines });
}

const data::display::Table Reporter::addFileContent(const data::csv::File& p_csvFile) const
{
    LOG(utils::INDENTATION + "Adding file content\n", utils::verbose);
    const std::vector<size_t> lineNumbers { getErrorLineNumbers(p_csvFile.m_content) };
    const data::display::Ranges ranges { data::convert::Ranges::get(lineNumbers,
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
    const data::csv::ErrorList errorLog { p_result.m_errorList };
    data::display::Table table {};
    size_t errorCounter { 0 };
    size_t warningCounter { 0 };
    auto f = [&](const auto& e) { return errorLogFilter(e); };
    for (const ErrorEntry& entry : errorLog | std::views::filter(f)) {
        entry.m_type == ErrorEntry::Type::ERR ? ++errorCounter : NULL;
        entry.m_type == ErrorEntry::Type::WARNING ? ++warningCounter : NULL;
        data::display::Row row {};
        row.push_back(getEntryType(entry.m_type) + " in line " + std::to_string(entry.first));
        row.push_back(entry.second);
        table.push_back(row);
    }
    table.insert(table.begin(), getFirstErrorRow(errorCounter, warningCounter));
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

const data::display::Row getFirstErrorRow(const size_t p_errorCounter, const size_t p_warningCounter)
{
    std::string andText {};
    if (p_errorCounter == 0 && p_warningCounter == 0) {
        andText = "No errors";
    }
    if (p_errorCounter != 0 && p_warningCounter != 0) {
        andText = " and ";
    }
    std::string errorText { p_errorCounter == 0 ? "" : std::to_string(p_errorCounter) + " errors" };
    std::string warningText { p_warningCounter == 0 ? "" : std::to_string(p_warningCounter) + " warnings" };
    return data::display::Row({ errorText + andText + warningText + " found in the file." });
}

} // namespace display
} // namespace csvvalidator
