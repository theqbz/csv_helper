///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Result.h
/// @brief Definition of the datastructure which stores the result of the
///        analysis of a csv::File
///

#pragma once

#include "../utils/ISettings.h"
#include "DisplayTable.h"

#include <string>
#include <utility>
#include <vector>

namespace csvvalidator::data {
namespace csv {

///
/// @brief Container for error messages.
/// An ErrorEntry consist the line number an the error message
/// represented by a < int, string > pair
///
struct ErrorEntry : public std::pair<size_t, std::string>
{ };

///
/// @brief Container for error log.
/// Error log is a vector of ErrorEntryes
///
struct ErrorLog : public std::vector<ErrorEntry>
{ };

///
/// @brief Conainer for the result of the analysis of a csv::File
///
struct Result
{
    ErrorLog m_errors;             ///< vector of error entries
    unsigned int m_emptyLineCount; ///< counts the empty lines in a csv::File

    const display::Table getTable(const utils::ISettings& p_settings);
};

} // namespace csv
} // namespace csvvalidator::data
