///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Table.h
/// @brief Definition of datastructure of displaying data
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

} // namespace display
} // namespace csvvalidator::data
