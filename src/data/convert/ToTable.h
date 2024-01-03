///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  ToTable.h
/// @brief Declarations of data::convert::ToTable class.
///
#pragma once

#include "../../utils/ISettings.h"
#include "../CsvData.h"
#include "../Ranges.h"
#include "../Report.h"

namespace csvvalidator::data {
namespace convert {

class ToTable
{
public:
    static const data::display::Table get(const data::csv::File& p_csvFile,
                                          const data::display::Ranges& p_ranges,
                                          const utils::ISettings::LabelPosition& p_labelPosition,
                                          const utils::ISettings::EmptyLines& p_emptyLines,
                                          const bool p_tableOutput);

    static const data::display::Row addLabels(const data::csv::Labels& p_labels,
                                              const size_t p_lastLineNumber);
    static const data::display::Row addLine(const data::csv::Record& p_record,
                                            const size_t p_lastLineNumber);
    static const std::string getRowHead(const size_t p_totalLineCount,
                                        const std::string& p_currentLineSign);
    static const std::string getRowHead(const size_t p_totalLineCount,
                                        const size_t p_currentLineNumber);
    static const std::string getPlaceholder(const std::string_view p_totalLineNumber,
                                            const std::string_view p_currentLineNumber);
    static const bool isEmptyRowAndSkipIt(const data::csv::RecordHead::ErrorState& p_recordState);
    static inline const std::string getRecordPrompt(const data::csv::RecordHead& p_recordHead,
                                                    const size_t p_lastLineNumber);
    static const std::string getRecordState(const data::csv::RecordHead& p_recordHead);
    static const std::string getFieldContent(const data::csv::Field& p_field);
    static const bool isLabelInline();

    static utils::ISettings::LabelPosition s_labelPosition;
    static utils::ISettings::EmptyLines s_emptyLines;
    static bool s_tableOutput;
};

} // namespace convert
} // namespace csvvalidator::data
