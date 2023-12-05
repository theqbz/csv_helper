///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Data.cpp
/// @brief Definition of the datastructure which describes the structure of a
///        .csv file and stores the data from it.
///

#include "Data.h"
#include "../display/Table.h"
#include "../utils/ISettings.h"

#include <string>
#include <string_view>

namespace csvhelper {
namespace csv {

static const char LINE_NUMBER_SPACING = ' ';
const std::string TABLE_HEADER_SIGN   = "H";
const std::string PROMT_CLOSING_SIGN  = ">";

inline const bool isLabelInline(const utils::ISettings& p_settings)
{
    return !p_settings.tableOutput()
        && p_settings.labelPosition() == utils::ISettings::LabelPosition::Inline;
}

inline const std::string fieldContent(const Field& p_field,
                                      const bool p_labelInline)
{
    return p_labelInline
        ? p_field.m_content.first + ": " + p_field.m_content.second
        : p_field.m_content.second;
}

const std::string recordState(const RecordHead& p_recordHead)
{
    std::string result {};
    RecordHead::State state = p_recordHead.m_state;
    switch (state) {
    case csvhelper::csv::RecordHead::OK:
        result = " ";
        break;
    case csvhelper::csv::RecordHead::ERR:
        result = "*";
        break;
    case csvhelper::csv::RecordHead::EMPTY:
        result = " ";
        break;
    default:
        result = "@!> Program logic error: invalid RecordHead State";
        break;
    }
    return result;
}

inline const bool isEmptyRowAndSkipIt(const RecordHead::State& p_recordState,
                                      const utils::ISettings::EmptyLines& p_emptyLineOption)
{
    return p_recordState == RecordHead::State::EMPTY
        && p_emptyLineOption == utils::ISettings::EmptyLines::Skip;
}

const std::string placeholder(const std::string_view p_totalLineNumber,
                              const std::string_view p_currentLineNumber)
{
    const size_t spaceAmount = p_totalLineNumber.length() - p_currentLineNumber.length();
    std::string spaceing { "" };
    return spaceing.insert(0, spaceAmount, LINE_NUMBER_SPACING);
}

const std::string rowHead(const size_t p_totalLineCount,
                          const std::string& p_currentLineSign)
{
    std::string_view totalLineCount { std::to_string(p_totalLineCount) };
    return placeholder(totalLineCount, p_currentLineSign)
        + p_currentLineSign
        + PROMT_CLOSING_SIGN;
}

const std::string rowHead(const size_t p_totalLineCount,
                          const size_t p_currentLineNumber)
{
    return rowHead(p_totalLineCount, std::to_string(p_currentLineNumber));
}

const display::Table File::getTable(const utils::ISettings& p_settings)
{
    const size_t totalLines = m_content.back().first.m_fileLineNumber;
    display::Table table {};
    display::Row firstRow {};
    firstRow.push_back(" " + rowHead(totalLines, TABLE_HEADER_SIGN));
    for (const std::string& label : m_labels) {
        firstRow.push_back(label);
    }
    table.push_back(firstRow);
    for (const Record& record : m_content) {
        display::Row row {};
        if (!isEmptyRowAndSkipIt(record.first.m_state, p_settings.emptyLines())) {
            row.push_back(recordState(record.first) + rowHead(totalLines, record.first.m_fileLineNumber));
        }
        for (const Field& field : record.second) {
            row.push_back(fieldContent(field, isLabelInline(p_settings)));
        }
        table.push_back(row);
    }
    return table;
}

} // namespace csv
} // namespace csvhelper
