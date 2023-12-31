///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Report.h
/// @brief Declarations of display::Report, display::Table and display::Row
///        datastructures.
///
/// These datastructures stores data to be shown on the display.
///
#pragma once

#include <string>
#include <vector>

namespace csvvalidator::data {
namespace display {

///
/// @brief Container for a table row.
/// 
/// Row consist a vector of strings
///
struct Row : public std::vector<std::string>
{ };

///
/// @brief Container for a string formed table.
/// 
/// Table consists a vector of Rows
///
struct Table : public std::vector<Row>
{ };

///
/// @brief Container for the information to display.
/// 
/// Report contains Tables with information about the file and the analysis
/// processes, the neccessary details from the file content, and the list of
/// errors.
///
struct Report
{
    Table m_info;
    Table m_file;
    Table m_errors;
};

} // namespace display
} // namespace csvvalidator::data
