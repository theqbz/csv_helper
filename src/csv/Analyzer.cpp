///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Analyzer.cpp
/// @brief Definition of csv::Analyzer class.
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

const data::csv::Result checkRecordDuplication(data::csv::Content* p_content);
const data::csv::Result checkRecordLengths(data::csv::Content* p_content,
                                           const size_t p_labelCount,
                                           const bool p_emptyLinesNotErrors);

data::csv::Result Analyzer::process(data::csv::File& p_csvFile)
{
    LOG("Analyzing csv::File\n", utils::verbose);
    data::csv::Content& content { p_csvFile.m_content };
    if (content.empty()) {
        LOG(utils::INDENTATION + "The file has no csv::Fields\n", true);
        return {};
    }
    data::csv::Result result {};
    result.m_lastLineNumber = content.back().first.m_fileLineNumber;
    result += checkRecordLengths(&content, p_csvFile.m_labels.size(), m_settings.emptyLines() != utils::ISettings::EmptyLines::Error);
    result += checkRecordDuplication(&content);
    // TODO:
    // Scan the Fields vertically (Record by Record, the same Field) and look after differences.
    LOG(utils::INDENTATION + "empty line count = " + std::to_string(result.m_emptyLineCount) + "\n", utils::verbose);
    LOG(utils::INDENTATION + "error count = " + std::to_string(result.m_errorCount) + "\n", utils::verbose);
    LOG(utils::INDENTATION + "warning count = " + std::to_string(result.m_warningCount) + "\n", utils::verbose);
    return result;
}

///
/// @brief Edit the duplicated flag in RecordHead if the record is duplicated.
///
/// @param[in,out] p_current       : the "current record"
/// @param[in,out] p_recordToCheck : the "record to check"
/// @return the Result of the process
///
const data::csv::Result markMultiplication(data::csv::Content::iterator p_current,
                                           data::csv::Content::iterator p_recordToCheck)
{
    if (*p_current != *p_recordToCheck) {
        return {};
    }
    data::csv::Result result {};
    if (!p_current->first.m_duplicated) {
        p_current->first.m_duplicated = true;
        data::csv::ErrorEntry currentRecordErrorEntry {};
        currentRecordErrorEntry.first  = p_current->first.m_fileLineNumber;
        currentRecordErrorEntry.second = "Multiple occurrence record (this is the first occurrence)";
        currentRecordErrorEntry.m_type = data::csv::ErrorEntry::Type::WARNING;
        ++result.m_warningCount;
        result.m_errorList.push_back(currentRecordErrorEntry);
    }
    p_recordToCheck->first.m_duplicated = true;
    data::csv::ErrorEntry checkedRecordErrorEntry {};
    checkedRecordErrorEntry.first  = p_recordToCheck->first.m_fileLineNumber;
    checkedRecordErrorEntry.second = ("Multiple occurrence record (the first occurrence is in line "
                                      + std::to_string(p_current->first.m_fileLineNumber)
                                      + ")");
    checkedRecordErrorEntry.m_type = data::csv::ErrorEntry::Type::WARNING;
    ++result.m_warningCount;
    result.m_errorList.push_back(checkedRecordErrorEntry);
    return result;
}

///
/// @brief Scan trough the file content to find duplicated records and edit the
///        state of the RecordHead accordingly the scan result.
///
/// @param[in,out] - content : the content of the file to copare
/// @return the Result of the process
///
const data::csv::Result checkRecordDuplication(data::csv::Content* p_content)
{
    typedef data::csv::Content::iterator ContentIt;
    LOG(utils::INDENTATION + "Checking duplicated records\n", utils::verbose);
    if (!p_content) {
        LOG("Program logic error! nullptr as content or result @ checkRecordDuplication()\n", true);
        return {};
    }
    data::csv::Result result {};
    for (ContentIt currentRecordIt = p_content->begin(); currentRecordIt != p_content->end(); ++currentRecordIt) {
        if (currentRecordIt->second.empty() || currentRecordIt->first.m_duplicated) {
            continue;
        }
        for (ContentIt recordToCheckIt = currentRecordIt + 1; recordToCheckIt != p_content->end(); ++recordToCheckIt) {
            result += markMultiplication(currentRecordIt, recordToCheckIt);
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
    ++result.m_errorCount;
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
/// @brief Scan the csv::Content to mark records with the wrong line length.
///
/// @param[in,out] - content : the csv::Content to check
/// @param[in] - labelCount  : the total number of labels in the csv::File
/// @param[in] - emptyLinesNotErrors : setting for handling empty lines
/// @return the Result of the process
///
const data::csv::Result checkRecordLengths(data::csv::Content* p_content, const size_t p_labelCount, const bool p_emptyLinesNotErrors)
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

} // namespace csv
} // namespace csvvalidator
