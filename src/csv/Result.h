///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Result.h
/// @brief Definition of the datastructure which stores the result of the
///        analysis of a csv::File
///

#pragma once

#include <string>
#include <vector>

namespace csvhelper {
namespace csv {

///
/// @brief Container for error messages
///
struct ErrorMessages : public std::vector<std::string>
{ };

///
/// @brief Conainer for the result of the analysis of a csv::File
///
struct Result
{
    ErrorMessages m_errors;        ///< vector of error messages
    unsigned int m_emptyLineCount; ///< counts the empty lines in a csv::File
};

} // namespace csv
} // namespace csvhelper
