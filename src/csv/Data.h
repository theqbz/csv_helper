///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Data.h
/// @brief Definition of the datastructure which describes the structure of a
///        .csv file and stores the data from it.
///

#pragma once

#include "../display/Table.h"
#include "../utils/ISettings.h"

#include <stdint.h>
#include <string>
#include <utility>
#include <vector>

namespace csvhelper {
namespace csv {

///
/// @brief Contains the state of the record
///
struct RecordHead
{
    ///
    /// The state of the Record
    /// Represent by [ OK | ERR | EMPTY ]
    ///
    enum State
    {
        OK,   ///< Line alright
        ERR,  ///< Line error
        EMPTY ///< Line empty but not error (to handle differently during displaying)
    };

    size_t m_fileLineNumber { 0 };
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
        UNCHECKED, ///< The csv field has not been checked yet
        OK,        ///< The csv field was checked and marked as no difference
        DIFF       ///< The csv field was checked and marked as difference
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
    std::string m_fileName; ///< the path and filename of the .csv file
    Labels m_labels;        ///< container for the labels of .csv file. Type: vector of strings
    Content m_content;      ///< container for Records of .csv file. Type: vector of Records

    const display::Table getTable(const utils::ISettings& p_settings);
    //const display::Table getReport(const utils::ISettings& p_settings);
};

} // namespace csv
} // namespace csvhelper
