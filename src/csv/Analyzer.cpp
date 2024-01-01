///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Analyzer.h
/// @brief Definition of csv::File analyzer class
///

#include "Analyzer.h"
#include "../data/CsvData.h"
#include "../data/Result.h"
#include "../utils/ISettings.h"
#include "../utils/Utility.h"

#include <string>
#include <vector>

namespace csvvalidator {
namespace csv {

///
/// @brief Scan trough the file content to find duplicated records and edit the
///        state of the RecordHead accordingly the scan result.
///
/// @param[in,out] - content : the content of the file to copare
/// @return the Result of the process
///
const data::csv::Result checkRecordDuplication(data::csv::Content* p_content)
{
    LOG(utils::INDENTATION + "Checking duplicated records\n", utils::verbose);
    if (!p_content) {
        LOG("Program logic error! nullptr as content or result @ checkRecordDuplication()\n", true);
        return {};
    }
    data::csv::Result result {};
    data::csv::Content::iterator currentRecordIt = p_content->begin();
    for (; currentRecordIt != p_content->end(); ++currentRecordIt) {
        if (currentRecordIt->second.empty() || currentRecordIt->first.m_duplicated) {
            continue;
        }
        data::csv::Content::iterator recordToCheckIt = currentRecordIt + 1;
        for (; recordToCheckIt != p_content->end(); ++recordToCheckIt) {
            if (*currentRecordIt != *recordToCheckIt) {
                continue;
            }
            if (!currentRecordIt->first.m_duplicated) {
                currentRecordIt->first.m_duplicated = true;
                data::csv::ErrorEntry currentRecordErrorEntry {};
                currentRecordErrorEntry.first  = currentRecordIt->first.m_fileLineNumber;
                currentRecordErrorEntry.second = "Multiple occurrence record (this is the first occurrence)";
                currentRecordErrorEntry.m_type = data::csv::ErrorEntry::Type::WARNING;
                result.m_errorList.push_back(currentRecordErrorEntry);
            }
            recordToCheckIt->first.m_duplicated = true;
            data::csv::ErrorEntry checkedRecordErrorEntry {};
            checkedRecordErrorEntry.first  = recordToCheckIt->first.m_fileLineNumber;
            checkedRecordErrorEntry.second = ("Multiple occurrence record (the first occurrence is in line "
                                              + std::to_string(currentRecordIt->first.m_fileLineNumber)
                                              + ")");
            checkedRecordErrorEntry.m_type = data::csv::ErrorEntry::Type::WARNING;
            result.m_errorList.push_back(checkedRecordErrorEntry);
        }
    }
    return result;
}

///
/// @brief Edit the ErrorState of the RecordHead accordingly the size of the
///        csv::Recod and program Settings.
///
/// Record size is the number of Fileds in the csv::Record, which if different
/// from the total number of labels, may idicate an error. Empty csv::Records
/// (say without a csv::Field) are only considered errors if this is specified
/// in the program settings.
///
/// @param[in,out] - record : the csv::Record to check
/// @param[in] - labelCount : the total number of labels in the csv::File
/// @param[in] - emptyLinesNotErrors : setting for handling empty lines
/// @return the Result of the process
///
const data::csv::Result markWrongLineLength(data::csv::Record* p_record,
                                            const size_t p_labelCount,
                                            const bool p_emptyLinesNotErrors)
{
    if (!p_record) {
        LOG("Program logic error! nullptr as record @ markWrongLineLength()\n", true);
        return {};
    }
    const size_t recordSize = p_record->second.size();
    if (recordSize == p_labelCount) {
        p_record->first.m_state = data::csv::RecordHead::ErrorState::OK;
        return {};
    }
    data::csv::Result result {};
    if (recordSize == 0 && p_emptyLinesNotErrors) {
        p_record->first.m_state = data::csv::RecordHead::ErrorState::EMPTY;
        ++result.m_emptyLineCount;
        return result;
    }
    p_record->first.m_state = data::csv::RecordHead::ErrorState::ERR;
    data::csv::ErrorEntry errorEntry {};
    errorEntry.first  = p_record->first.m_fileLineNumber;
    errorEntry.second = ("The line doesn't match to the label list. (records: "
                         + std::to_string(recordSize) + " / "
                         + std::to_string(p_labelCount) + ")");
    errorEntry.m_type = data::csv::ErrorEntry::Type::ERR;
    result.m_errorList.push_back(errorEntry);
    return result;
}

///
/// @brief Loop trough the csv::Records of the csv::Content and mark records
///        with the wrong line length.
///
/// @param[in,out] - content : the csv::Content to check
/// @param[in] - labelCount  : the total number of labels in the csv::File
/// @param[in] - emptyLinesNotErrors : setting for handling empty lines
/// @return the Result of the process
///
const data::csv::Result checkRecordLengths(data::csv::Content* p_content,
                                           const size_t p_labelCount,
                                           const bool p_emptyLinesNotErrors)
{
    LOG(utils::INDENTATION + "Checking record lengths\n", utils::verbose);
    if (!p_content) {
        LOG("Program logic error! nullptr as content @ checkRecordLengths()\n", true);
        return {};
    }
    data::csv::Result result {};
    for (data::csv::Record& record : *p_content) {
        result += markWrongLineLength(&record, p_labelCount, p_emptyLinesNotErrors);
    }
    return result;
}

data::csv::Result Analyzer::process(data::csv::File& p_csvFile)
{
    LOG("Analyzing csv::File\n", utils::verbose);
    const bool emptyLinesNotErrors { m_settings.emptyLines() != utils::ISettings::EmptyLines::Error };
    const size_t labelCount { p_csvFile.m_labels.size() };
    data::csv::Content& content { p_csvFile.m_content };
    if (content.empty()) {
        LOG(utils::INDENTATION + "The file has no csv::Fields\n", true);
        return {};
    }
    data::csv::Result result {};
    result.m_lastLineNumber = content.back().first.m_fileLineNumber;
    result += checkRecordLengths(&content, labelCount, emptyLinesNotErrors);
    result += checkRecordDuplication(&content);
    // TODO:
    // Scan the Fields vertically (Record by Record, the same Field) and look after differences.
    return result;
}

} // namespace csv
} // namespace csvvalidator
