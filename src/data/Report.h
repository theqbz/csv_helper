///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Report.h
/// @brief Definition of datastructure of Report
///

#pragma once

#include <string>
#include <vector>

namespace csvvalidator::data {
namespace display {

///
/// @brief Container for a table row.
/// Row consist a vector of strings
///
struct Row : public std::vector<std::string>
{ };

///
/// @brief Container for a string formed table.
/// Table consists a vector of Rows
///
struct Table : public std::vector<Row>
{ };

///
/// @brief Container for the information to display.
/// Report contains information about the file and processes performed, the
/// neccessary details from the file content and the list of errors
///
struct Report
{
    Table m_fileInfo;
    Table m_file;
    Table m_errors;
};

} // namespace display
} // namespace csvvalidator::data

