///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Result.h
/// @brief Declarations of csv::Result, csv::ErrorList and csv::ErrorEntry
///        datastructures.
///
/// These datastructures stores the result of the analysis of a csv::File
///
#pragma once

#include <string>
#include <utility>
#include <vector>

namespace csvvalidator::data {
namespace csv {

///
/// @brief Container for error messages.
///
/// An ErrorEntry is a < size_t, string > pair of the line number and the error
/// message, and contains the type of the entry.
///
struct ErrorEntry : public std::pair<size_t, std::string>
{
    ///
    /// @brief The type of the entry.
    ///
    enum class Type
    {
        INFO,    ///> information
        WARNING, ///> warning
        ERR      ///> error
    };

    Type m_type { Type::INFO }; ///< The type of the error entry
};

///
/// @brief Container for error log.
///
/// Error log is a vector of ErrorEntries
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

    ///
    /// @brief Merge Result objects.
    ///
    /// It adds only the errorList and emptyLineCount, the lastLineNumber must
    /// set separatley!
    ///
    Result& operator+=(const Result& p_other)
    {
        this->m_errorList.insert(this->m_errorList.end(), p_other.m_errorList.begin(), p_other.m_errorList.end());
        this->m_emptyLineCount += p_other.m_emptyLineCount;
        return *this;
    }
};

} // namespace csv
} // namespace csvvalidator::data
