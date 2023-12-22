///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Result.h
/// @brief Definition of the datastructure which stores the result of the
///        analysis of a csv::File
///

#pragma once

#include "../utils/ISettings.h"
#include "Report.h"

#include <string>
#include <utility>
#include <vector>

namespace csvvalidator {
namespace data {
namespace csv {

///
/// @brief Container for error messages.
/// An ErrorEntry consist the line number and the error message represented
/// by a < size_t, string > pair, and the type of the message
///
struct ErrorEntry : public std::pair<size_t, std::string>
{
    ///
    /// @brief The type of the entry.
    /// ErrorEntry type can be [ info | warning | err(or) ]
    ///
    enum class Type
    {
        INFO,    ///> information
        WARNING, ///> warning
        ERR      ///> error
    };

    ///
    /// The type of the error entry
    ///
    Type m_type { Type::INFO };
};

///
/// @brief Container for error log.
/// Error log is a vector of ErrorEntryes
///
struct ErrorList : public std::vector<ErrorEntry>
{ };

///
/// @brief Conainer for the result of the analysis of a csv::File
///
struct Result
{
    ErrorList m_errorList;   ///< vector of error entries
    size_t m_lastLineNumber; ///< number of the last line of the .csv file
    size_t m_emptyLineCount; ///< counts the empty lines in the csv::File
};

} // namespace csv
} // namespace data
} // namespace csvvalidator
