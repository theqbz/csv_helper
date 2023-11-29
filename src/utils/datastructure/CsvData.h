///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  CsvData.h
/// @brief Definition of the datastructure, to describe and store labels and
///        records from a .csv file
///

#pragma once

#include <stdint.h>
#include <string>
#include <utility>
#include <vector>

namespace csvhelper::utils {
namespace csv {

///
/// @brief Contains the state of the record
///
struct RecordHead
{
    enum State
    {
        OK,
        ERR
    };
    uint64_t m_fieldCount { 0 };
    State m_state { State::OK };
};

///
/// @brief Descriptor for a single value from a .csv file.
///
struct Field
{
    ///
    /// The state of the field.
    /// Represent by [ UNCHECKED | OK | DIFF ]
    ///
    enum State
    {
        UNCHECKED, /// The csv field has not been checked yet
        OK,        /// The csv field was checked and marked as no difference
        DIFF       /// The csv field was checked and marked as difference
    };

    ///
    /// The content of the csv field.
    /// The content consists a pair of < key, value >
    ///
    std::pair<std::string, std::string> m_content;

    ///
    /// The state of the csv value
    ///
    State m_state { State::UNCHECKED };
};

///
/// @brief Container for fields from a record (row) of a .csv file.
///
struct Fields : public std::vector<Field>
{ };

///
/// @brief Container for a record (row) of a .csv file.
/// The Record consists a header and the content of the record,
/// represent by a pair of < RecordHead, Fields >
///
struct Record : public std::pair<RecordHead, Fields>
{ };

///
/// @brief Container for the records of a .csv file
///
struct Content : public std::vector<Record>
{ };

///
/// @brief Container for the labels of a .csv file
///
struct Labels : public std::vector<std::string>
{ };

///
/// @brief Container for a whole .csv file
///
struct File
{
    std::string m_fileName;
    Labels m_labels;
    Content m_content;
};

} // namespace csv
} // namespace csvhelper::utils
