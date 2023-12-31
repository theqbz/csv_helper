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
#include "../utils/ISettings.h"
#include "../utils/Utility.h"

#include <iostream>
#include <limits>
#include <ranges>
#include <string>
#include <vector>

namespace csvvalidator {
namespace display {

static const char LINE_NUMBER_SPACING = ' ';

static const std::string getRecordState(const data::csv::RecordHead& p_recordHead);
static bool areRangesOverlaping(const data::display::Range& p_range1, const data::display::Range& p_range2);
static void merge(const data::display::Range& p_sourceRange, data::display::Range* p_targetRange);
static const data::display::Ranges mergeRanges(data::display::Ranges& p_rawRanges);
static const std::string getPlaceholder(const std::string_view p_totalLineNumber, const std::string_view p_currentLineNumber);
static const std::string getRowHead(const size_t p_totalLineCount, const std::string& p_currentLineSign);
static const std::string getRowHead(const size_t p_totalLineCount, const size_t p_currentLineNumber);
static const data::display::Row addLabels(const data::csv::Labels& p_labels, const size_t p_lastLineNumber);
static const std::vector<size_t> getErrorLineNumbers(const data::csv::Content& p_content);
static const size_t lowerBound(const size_t p_initialNumber, const size_t p_rangeWidth, const size_t p_lowerLimit = 0);
static const size_t upperBound(const size_t p_initialNumber, const size_t p_rangeWidth, const size_t p_upperLimit);
static inline const std::string getRecordPrompt(const data::csv::RecordHead& p_recordHead, const size_t p_lastLineNumber);
static inline const std::string getEntryType(const data::csv::ErrorEntry::Type& p_entryType);
static const data::display::Row getFirstRow(const size_t p_errorCounter, const size_t p_warningCounter);

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
    data::display::Ranges rawRanges = getRanges(getErrorLineNumbers(p_csvFile.m_content),
                                                p_csvFile.m_content.size() - 1);
    LOG(utils::INDENTATION + "rawRanges = " + std::to_string(rawRanges.size()) + "\n", utils::verbose);
    const data::display::Ranges mergedRanges = mergeRanges(rawRanges);
    LOG(utils::INDENTATION + "mergedRanges = " + std::to_string(mergedRanges.size()) + "\n", utils::verbose);
    const data::display::Table table = addLines(p_csvFile, mergedRanges);
    return table;
}

const data::display::Table Reporter::addErrorList(const data::csv::Result& p_result) const
{
    LOG(utils::INDENTATION + "Adding error list\n", utils::verbose);
    const data::csv::ErrorList errorLog { p_result.m_errorList };
    data::display::Table table {};
    size_t errorCounter { 0 };
    size_t warningCounter { 0 };
    auto f = [&](const auto& e) { return errorLogFilter(e); };
    for (const data::csv::ErrorEntry& entry : errorLog | std::views::filter(f)) {
        entry.m_type == data::csv::ErrorEntry::Type::ERR ? ++errorCounter : NULL;
        entry.m_type == data::csv::ErrorEntry::Type::WARNING ? ++warningCounter : NULL;
        data::display::Row row {};
        row.push_back(getEntryType(entry.m_type) + " in line " + std::to_string(entry.first));
        row.push_back(entry.second);
        table.push_back(row);
    }
    table.insert(table.begin(), getFirstRow(errorCounter, warningCounter));
    return table;
}

bool Reporter::errorLogFilter(const auto& p_entry) const
{
    if (m_settings.errorLevel() == utils::ISettings::ErrorLevel::All) {
        return true;
    }
    return p_entry.m_type == data::csv::ErrorEntry::Type::ERR;
}

const data::display::Ranges Reporter::getRanges(const std::vector<size_t>& p_errorLineNumbers,
                                                const size_t p_upperLimit) const
{
    LOG(utils::INDENTATION + "Getting raw ranges\n", utils::verbose);
    data::display::Ranges ranges {};
    const size_t rangeWidth = m_settings.linesAroundErrors();
    for (const size_t& number : p_errorLineNumbers) {
        data::display::Range range({ lowerBound(number, rangeWidth),
                                     upperBound(number, rangeWidth, p_upperLimit) });
        ranges.push_back(range);
    }
    return ranges;
}

const bool Reporter::isLabelInline() const
{
    return !m_settings.tableOutput()
        && m_settings.labelPosition() == utils::ISettings::LabelPosition::Inline;
}

const std::string Reporter::getFieldContent(const data::csv::Field& p_field) const
{
    const bool labelInline = isLabelInline();
    if (p_field.m_content.second.empty() && labelInline) {
        return {};
    }
    return labelInline
        ? p_field.m_content.first + ": " + p_field.m_content.second
        : p_field.m_content.second;
}

const bool Reporter::isEmptyRowAndSkipIt(const data::csv::RecordHead::State& p_recordState) const
{
    return p_recordState == data::csv::RecordHead::State::EMPTY
        && m_settings.emptyLines() == utils::ISettings::EmptyLines::Skip;
}

const data::display::Row Reporter::addLine(const data::csv::Record& p_record,
                                           const size_t p_lastLineNumber) const
{
    if (isEmptyRowAndSkipIt(p_record.first.m_state)) {
        return {};
    }
    data::display::Row row {};
    row.push_back(getRecordPrompt(p_record.first, p_lastLineNumber));
    for (const data::csv::Field& field : p_record.second) {
        row.push_back(getFieldContent(field));
    }
    return row;
}

const data::display::Table Reporter::addLines(const data::csv::File& p_csvFile,
                                              const data::display::Ranges& p_finalRanges) const
{
    LOG(utils::INDENTATION + "Adding content lines\n", utils::verbose);
    const data::csv::Content& content { p_csvFile.m_content };
    if (content.empty()) {
        LOG(utils::INDENTATION + "The file has no csv::Fields\n", utils::verbose);
        return {};
    }
    data::display::Table table {};
    const data::display::Row separator({ "(...)" });
    const size_t lastLineNumber { content.back().first.m_fileLineNumber };
    LOG(utils::INDENTATION + "lastLineNumber = " + std::to_string(lastLineNumber) + "\n", utils::verbose);
    if (!p_finalRanges.empty() && m_settings.labelPosition() != utils::ISettings::LabelPosition::Inline) {
        table.push_back(addLabels(p_csvFile.m_labels, lastLineNumber));
    }
    for (size_t rangeIdx = 0; rangeIdx < p_finalRanges.size(); ++rangeIdx) {
        if (rangeIdx > 0) {
            table.push_back(separator);
        }
        const data::display::Range& range = p_finalRanges.at(rangeIdx);
        for (size_t recordIdx = range.first; recordIdx <= range.second; ++recordIdx) {
            table.push_back(addLine(p_csvFile.m_content.at(recordIdx), lastLineNumber));
        }
    }
    return table;
}

static const std::vector<size_t> getErrorLineNumbers(const data::csv::Content& p_content)
{
    LOG(utils::INDENTATION + "Getting error line numbers\n", utils::verbose);
    std::vector<size_t> errorLineNumbers {};
    data::csv::Content::const_iterator firstRecord   = p_content.begin();
    data::csv::Content::const_iterator currentRecord = firstRecord;
    for (; currentRecord != p_content.end(); ++currentRecord) {
        if (currentRecord->first.m_state == data::csv::RecordHead::State::ERR) {
            errorLineNumbers.push_back(std::distance(firstRecord, currentRecord));
        }
    }
    return errorLineNumbers;
}

static const size_t lowerBound(const size_t p_initialNumber,
                               const size_t p_rangeWidth,
                               const size_t p_lowerLimit)
{
    if (p_rangeWidth == std::numeric_limits<size_t>::max()) {
        return p_lowerLimit;
    }
    const long long lower_bound = std::make_signed_t<size_t>(p_initialNumber) - std::make_signed_t<size_t>(p_rangeWidth);
    if (lower_bound < std::make_signed_t<size_t>(p_lowerLimit)) {
        return p_lowerLimit;
    }
    return static_cast<size_t>(lower_bound);
}

static const size_t upperBound(const size_t p_initialNumber,
                               const size_t p_rangeWidth,
                               const size_t p_upperLimit)
{
    if (p_rangeWidth == std::numeric_limits<size_t>::max()) {
        return p_upperLimit;
    }
    const size_t upper_bound = p_initialNumber + p_rangeWidth;
    return upper_bound < p_upperLimit ? upper_bound : p_upperLimit;
}

static const std::string getRecordState(const data::csv::RecordHead& p_recordHead)
{
    data::csv::RecordHead::State state = p_recordHead.m_state;
    std::string result {};
    switch (state) {
    case data::csv::RecordHead::OK:
        result = utils::DISPLAY_PROMPT_NEUTRAL_SIGN;
        break;
    case data::csv::RecordHead::ERR:
        result = utils::DISPLAY_PROMPT_ERROR_SIGN;
        break;
    case data::csv::RecordHead::EMPTY:
        result = utils::DISPLAY_PROMPT_NEUTRAL_SIGN;
        break;
    default:
        result = "@!> Program logic error: invalid RecordHead State";
        break;
    }
    return result;
}

static bool areRangesOverlaping(const data::display::Range& p_range1,
                                const data::display::Range& p_range2)
{
    if (p_range1.first <= p_range2.first) {
        return p_range2.first <= p_range1.second;
    }
    return p_range1.first <= p_range2.second;
}

static void merge(const data::display::Range& p_sourceRange,
                  data::display::Range* p_targetRange)
{
    if (!p_targetRange) {
        std::cout << "Program logic error @ merge()! nullptr as p_targetRange\n";
        return;
    }
    if (p_sourceRange.first < p_targetRange->first) {
        p_targetRange->first = p_sourceRange.first;
    }
    if (p_sourceRange.second > p_targetRange->second) {
        p_targetRange->second = p_sourceRange.second;
    }
}

static const data::display::Ranges mergeRanges(data::display::Ranges& p_rawRanges)
{
    LOG(utils::INDENTATION + "Merging ranges\n", utils::verbose);
    if (p_rawRanges.empty()) {
        return {};
    }
    p_rawRanges.normalize();
    p_rawRanges.sort();
    data::display::Ranges final_ranges {};
    data::display::Ranges::const_iterator currentRangeToCompareIt = p_rawRanges.begin();
    for (; currentRangeToCompareIt != p_rawRanges.end(); ++currentRangeToCompareIt) {
        if (final_ranges.empty() || !areRangesOverlaping(final_ranges.back(), *currentRangeToCompareIt)) {
            final_ranges.push_back(*currentRangeToCompareIt);
            continue;
        }
        merge(*currentRangeToCompareIt, &final_ranges.back());
    }
    return final_ranges;
}

static const std::string getPlaceholder(const std::string_view p_totalLineNumber,
                                        const std::string_view p_currentLineNumber)
{
    const size_t spaceAmount = p_totalLineNumber.length() - p_currentLineNumber.length();
    std::string spaceing { "" };
    return spaceing.insert(0, spaceAmount, LINE_NUMBER_SPACING);
}

static const std::string getRowHead(const size_t p_totalLineCount,
                                    const std::string& p_currentLineSign)
{
    std::string_view totalLineCount { std::to_string(p_totalLineCount) };
    return getPlaceholder(totalLineCount, p_currentLineSign)
        + p_currentLineSign + "."
        + utils::DISPLAY_PROMT_END_SIGN;
}

static const std::string getRowHead(const size_t p_totalLineCount,
                                    const size_t p_currentLineNumber)
{
    return getRowHead(p_totalLineCount, std::to_string(p_currentLineNumber));
}

static const data::display::Row addLabels(const data::csv::Labels& p_labels,
                                          const size_t p_lastLineNumber)
{
    LOG(utils::INDENTATION + "Adding labels\n", utils::verbose);
    data::display::Row labels {};
    labels.push_back(" " + getRowHead(p_lastLineNumber, utils::DISPLAY_ROMPT_HEADER_SIGN));
    for (const std::string& label : p_labels) {
        labels.push_back(label);
    }
    return labels;
}

static inline const std::string getRecordPrompt(const data::csv::RecordHead& p_recordHead,
                                                const size_t p_lastLineNumber)
{
    return getRecordState(p_recordHead) + getRowHead(p_lastLineNumber, p_recordHead.m_fileLineNumber);
}

static inline const std::string getEntryType(const data::csv::ErrorEntry::Type& p_entryType)
{
    std::string typeAsString;
    switch (p_entryType) {
    case data::csv::ErrorEntry::Type::INFO: {
        typeAsString = "Information";
        break;
    }
    case data::csv::ErrorEntry::Type::WARNING: {
        typeAsString = "Warning";
        break;
    }
    case data::csv::ErrorEntry::Type::ERR: {
        typeAsString = "Error";
        break;
    }
    default:
        std::cout << "Program logic error! Wrong ErrorEntry type @ getEntryType()\n";
        break;
    }
    return typeAsString;
}

const data::display::Row getFirstRow(const size_t p_errorCounter, const size_t p_warningCounter)
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
