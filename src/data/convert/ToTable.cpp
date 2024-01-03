///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  ToTable.h
/// @brief Declarations of data::convert::ToTable class.
///

#include "ToTable.h"
#include "../../utils/ISettings.h"
#include "../../utils/Utility.h"
#include "../CsvData.h"
#include "../Ranges.h"
#include "../Report.h"

namespace csvvalidator::data {
namespace convert {

utils::ISettings::LabelPosition ToTable::s_labelPosition = utils::ISettings::LabelPosition::Top;
utils::ISettings::EmptyLines ToTable::s_emptyLines       = utils::ISettings::EmptyLines::Skip;
bool ToTable::s_tableOutput                              = false;
static const char LINE_NUMBER_SPACING                    = ' ';

const data::display::Table ToTable::get(const data::csv::File& p_csvFile,
                                        const data::display::Ranges& p_ranges,
                                        const utils::ISettings::LabelPosition& p_labelPosition,
                                        const utils::ISettings::EmptyLines& p_emptyLines,
                                        const bool p_tableOutput)
{
    LOG(utils::INDENTATION + "Adding content lines\n", utils::verbose);
    s_labelPosition = p_labelPosition;
    s_emptyLines    = p_emptyLines;
    s_tableOutput   = p_tableOutput;
    const data::csv::Content& content { p_csvFile.m_content };
    if (content.empty()) {
        LOG(utils::INDENTATION + "The file has no csv::Fields\n", utils::verbose);
        return {};
    }
    data::display::Table table {};
    const data::display::Row separator({ "(...)" });
    const size_t lastLineNumber { content.back().first.m_fileLineNumber };
    LOG(utils::INDENTATION + "lastLineNumber = " + std::to_string(lastLineNumber) + "\n", utils::verbose);
    if (!p_ranges.empty() && s_labelPosition != utils::ISettings::LabelPosition::Inline) {
        table.push_back(addLabels(p_csvFile.m_labels, lastLineNumber));
    }
    for (size_t rangeIdx = 0; rangeIdx < p_ranges.size(); ++rangeIdx) {
        if (rangeIdx > 0) {
            table.push_back(separator);
        }
        const data::display::Range& range = p_ranges.at(rangeIdx);
        for (size_t recordIdx = range.first; recordIdx <= range.second; ++recordIdx) {
            table.push_back(addLine(p_csvFile.m_content.at(recordIdx), lastLineNumber));
        }
    }
    return table;
}

const data::display::Row ToTable::addLabels(const data::csv::Labels& p_labels,
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

const data::display::Row ToTable::addLine(const data::csv::Record& p_record,
                                          const size_t p_lastLineNumber)
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

const std::string ToTable::getRowHead(const size_t p_totalLineCount,
                                      const std::string& p_currentLineSign)
{
    std::string_view totalLineCount { std::to_string(p_totalLineCount) };
    return getPlaceholder(totalLineCount, p_currentLineSign)
        + p_currentLineSign + "."
        + utils::DISPLAY_PROMT_CLOSE_SIGN;
}

const std::string ToTable::getRowHead(const size_t p_totalLineCount,
                                      const size_t p_currentLineNumber)
{
    return getRowHead(p_totalLineCount, std::to_string(p_currentLineNumber));
}

const std::string ToTable::getPlaceholder(const std::string_view p_totalLineNumber,
                                          const std::string_view p_currentLineNumber)
{
    const size_t spaceAmount = p_totalLineNumber.length() - p_currentLineNumber.length();
    std::string spaceing { "" };
    return spaceing.insert(0, spaceAmount, LINE_NUMBER_SPACING);
}

const bool ToTable::isEmptyRowAndSkipIt(const data::csv::RecordHead::ErrorState& p_recordState)
{
    return p_recordState == data::csv::RecordHead::ErrorState::EMPTY
        && s_emptyLines == utils::ISettings::EmptyLines::Skip;
}

inline const std::string ToTable::getRecordPrompt(const data::csv::RecordHead& p_recordHead,
                                                  const size_t p_lastLineNumber)
{
    return getRecordState(p_recordHead) + getRowHead(p_lastLineNumber, p_recordHead.m_fileLineNumber);
}

const std::string ToTable::getRecordState(const data::csv::RecordHead& p_recordHead)
{
    typedef data::csv::RecordHead RecordHead;
    RecordHead::ErrorState state = p_recordHead.m_state;
    std::string result {};
    switch (state) {
    case RecordHead::ErrorState::OK:
        result = utils::DISPLAY_PROMPT_NEUTRAL_SIGN;
        if (p_recordHead.m_duplicated) {
            result = utils::DISPLAY_PROMPT_DUPLICATED_SIGN;
        }
        break;
    case RecordHead::ErrorState::ERR:
        result = utils::DISPLAY_PROMPT_ERROR_SIGN;
        break;
    case RecordHead::ErrorState::EMPTY:
        result = utils::DISPLAY_PROMPT_NEUTRAL_SIGN;
        if (p_recordHead.m_duplicated) {
            result = utils::DISPLAY_PROMPT_DUPLICATED_SIGN;
        }
        break;
    default:
        LOG("@!> Program logic error: invalid RecordHead ErrorState\n", true);
        result = "@!> Program logic error: invalid RecordHead ErrorState";
        break;
    }
    return result;
}

const std::string ToTable::getFieldContent(const data::csv::Field& p_field)
{
    const bool labelInline = isLabelInline();
    if (p_field.m_content.second.empty() && labelInline) {
        return {};
    }
    return labelInline
        ? p_field.m_content.first + ": " + p_field.m_content.second
        : p_field.m_content.second;
}

const bool ToTable::isLabelInline()
{
    return !s_tableOutput && s_labelPosition == utils::ISettings::LabelPosition::Inline;
}

} // namespace convert
} // namespace csvvalidator::data
