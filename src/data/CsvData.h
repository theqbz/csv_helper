///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  CsvData.h
/// @brief Declarations of csv::File, csv::Labels, csv::Content, csv::Record,
///        csv::Fields, csv::Field and csv::RecordHead datastructures.
///
/// These datastructures describes the structure of a *csv file* and stores the
/// data from the file.
///
#pragma once

#include <string>
#include <utility>
#include <vector>

namespace csvvalidator::data {
namespace csv {

///
/// @brief The state of a csv::Record.
///
/// A RecordHead consists the errorState, the line number and the duplication
/// state of the csv::Record.
///
struct RecordHead
{
    ///
    /// @brief The error state of the Record.
    ///
    enum ErrorState
    {
        OK,    ///< Record without error
        ERR,   ///< Incorrect Record
        EMPTY, ///< Record is empty but this is not an error (to handle differently during displaying)
    };

    ErrorState m_state { ErrorState::OK }; ///< The error state of the record
    size_t m_fileLineNumber { 0 };         ///< The line number in the original file
    bool m_duplicated { false };           ///< Signs if the current line occoures more than once on the file

    inline bool operator==(const RecordHead& p_other) const
    {
        return this->m_fileLineNumber == p_other.m_fileLineNumber && this->m_state == p_other.m_state;
    }
};

///
/// @brief Descriptor for a value from a *csv file*.
///
/// A Field consists the state and the content of the field.
///
struct Field
{
    ///
    /// @brief The difference state of the field.
    ///
    enum DiffState
    {
        UNCHECKED, ///< The csv field has not been checked yet
        OK,        ///< The csv field was checked and marked as no difference
        DIFF       ///< The csv field was checked and marked as difference
    };

    DiffState m_state { DiffState::UNCHECKED };    ///< The difference state of the Field
    std::pair<std::string, std::string> m_content; ///< The content of the field

    inline bool operator==(const Field& p_other) const { return this->m_content == p_other.m_content; }
};

///
/// @brief Container for fields from a record (row) of a *csv file*.
///
/// Fields is the list of csv::Fields.
///
struct Fields : public std::vector<Field>
{ };

///
/// @brief Container for a record (row) of a *csv file*.
///
/// The Record consists a header and the content of the record,
/// represent by a pair of < RecordHead, Fields >.
///
struct Record : public std::pair<RecordHead, Fields>
{
    inline bool operator==(const Record& p_other) const { return this->second == p_other.second; }
};

///
/// @brief Container for the records of a *csv file*
///
/// Content is the list of csv::Records.
///
struct Content : public std::vector<Record>
{ };

///
/// @brief Container for the labels of a *csv file*.
///
/// Labels is a list of strings, which are the labels.
///
struct Labels : public std::vector<std::string>
{ };

///
/// @brief Container for a whole *csv file*.
/// 
/// A *csv file* constists the name of the file, the list of Labels and the
/// list of Records.
///
struct File
{
    std::string m_fileName; ///< the path and filename of the .csv file
    Labels m_labels;        ///< container for the labels of .csv file. Type: vector of strings
    Content m_content;      ///< container for Records of .csv file. Type: vector of Records
};

} // namespace csv
} // namespace csvvalidator::data
