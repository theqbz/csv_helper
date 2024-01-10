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
    ErrorList m_errorList;         ///< vector of error entries
    size_t m_lastLineNumber { 0 }; ///< number of the last line of the *csv file*
    size_t m_emptyLineCount { 0 }; ///< counts the empty lines in the csv::File
    size_t m_errorCount { 0 };     ///< counts errors during the Analyzis
    size_t m_warningCount { 0 };   ///< counts warnings during the Analyzis

    ///
    /// @brief Merge Result objects.
    ///
    /// Merging process appends the right-hand side's error list to the end of
    /// the left-hand side list, also adds the empty line count, the error and
    /// the warning counts. This function doesn't do anthing with last line
    /// number, it must handle separatley!
    /// 
    /// @param[in] p_rhs : the Result object to be merged (into left-hand side)
    /// @return a reference to left-hand side object
    ///
    Result& operator+=(const Result& p_rhs)
    {
        this->m_errorList.insert(this->m_errorList.end(), p_rhs.m_errorList.begin(), p_rhs.m_errorList.end());
        this->m_emptyLineCount += p_rhs.m_emptyLineCount;
        this->m_errorCount += p_rhs.m_errorCount;
        this->m_warningCount += p_rhs.m_warningCount;
        return *this;
    }
};

} // namespace csv
} // namespace csvvalidator::data
