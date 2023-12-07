///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Result.cpp
/// @brief Definition of the datastructure which stores the result of the
///        analysis of a csv::File
///

#include "Result.h"
#include "../utils/ISettings.h"
#include "DisplayTable.h"

#include <string>
#include <vector>

namespace csvvalidator::data {
namespace csv {

const display::Table Result::getTable(const utils::ISettings& p_settings)
{
    display::Table table {};
    table.push_back(display::Row({ "This file conains " + std::to_string(m_emptyLineCount) + " empty lines." }));
    if (m_errors.empty()) {
        table.push_back(display::Row({ "No errors found! :)" }));
        return table;
    }
    table.push_back(display::Row({ "The following " + std::to_string(m_errors.size()) + " errors found:" }));
    for (const csv::ErrorEntry& entry : m_errors) {
        display::Row errorRow {};
        errorRow.push_back("Error in line " + std::to_string(entry.first) + ": ");
        errorRow.push_back(entry.second);
        table.push_back(errorRow);
    }
    return table;
}

} // namespace csv
} // namespace csvvalidator::data
