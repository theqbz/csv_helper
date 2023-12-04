///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Analyzer.h
/// @brief Definition of csv::File analyzer class
///

#include "Analyzer.h"
#include "Data.h"
#include "Result.h"

namespace csvhelper {
namespace csv {

///
/// @brief Edit the State of the RecordHead accordingly the size of the
/// csv::Recod and program Settings.
///
/// Record size is the number of Fileds in the csv::Record, which if different
/// from the total number of labels, may idicate an error. Empty csv::Records
/// (say without a csv::Field) are only considered errors if this is specified
/// in the program settings.
///
/// @param[in,out] - record : the csv::Record to check
/// @param[in,out] - result : the Result data to store error and increment
///                           empty line copunter
/// @return (void)
///
void markWrongLineLength(csv::Record* p_record,
                         csv::Result* p_result,
                         const size_t p_labelCount,
                         const bool p_emptyLinesNotErrors)
{
    if (!p_record || !p_result) {
        return;
    }
    const size_t recordSize = p_record->second.size();
    if (recordSize == p_labelCount) {
        p_record->first.m_state = csv::RecordHead::State::OK;
        return;
    }
    if (recordSize == 0 && p_emptyLinesNotErrors) {
        p_record->first.m_state = csv::RecordHead::State::EMPTY;
        ++p_result->m_emptyLineCount;
        return;
    }
    p_record->first.m_state = csv::RecordHead::State::ERR;
    csv::ErrorEntry errorEntry {};
    errorEntry.first  = p_record->first.m_fileLineNumber;
    errorEntry.second = ("The line doesn't match to the label list. (records: "
                         + std::to_string(recordSize) + " / "
                         + std::to_string(p_labelCount) + ")");
    p_result->m_errors.push_back(errorEntry);
}

csv::Result Analyzer::process(csv::File& p_csvFile)
{
    Result result {};
    const bool emptyLinesNotErrors { m_settings.emptyLines() != utils::ISettings::EmptyLines::Error };
    const size_t labelCount { p_csvFile.m_labels.size() };
    for (csv::Record& record : p_csvFile.m_content) {
        markWrongLineLength(&record, &result, labelCount, emptyLinesNotErrors);
    }
    // TODO:
    // 2) Scan the Fields vertically (Record by Record, the same Field) and look after differences.
    return result;
}

} // namespace csv
} // namespace csvhelper
