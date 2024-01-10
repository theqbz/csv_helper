///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  ToTable.h
/// @brief Declaration of data::convert::ToTable class.
///
#pragma once

#include "../../utils/ISettings.h"
#include "../CsvData.h"
#include "../Ranges.h"
#include "../Report.h"

namespace csvvalidator::data {
namespace convert {

///
/// @brief Worker class to create data::display::Table from the content of a
///        data::csv::File depending on data::Display::Ranges and other
///        relevant settings.
///
class ToTable
{
public:
    ///
    /// @brief Creates a table from the content of a csv::File.
    /// 
    /// @param[in] - p_csvFile       : the parsed content of a *csv* file
    /// @param[in] - p_ranges        : the ranges of line numbers to display
    ///                                from the csv::File
    /// @param[in] - p_labelPosition : setting for the location of the label in
    ///                                the table
    /// @param[in] - p_emptyLines    : setting for handling empty lines
    /// @param[in] - p_tableOutput   : setting for table output
    /// 
    /// @return displayable data in a display::Table datastructure
    ///
    static const data::display::Table get(const data::csv::File& p_csvFile,
                                          const data::display::Ranges& p_ranges,
                                          const utils::ISettings::LabelPosition& p_labelPosition,
                                          const utils::ISettings::EmptyLines& p_emptyLines,
                                          const bool p_tableOutput);

    static utils::ISettings::LabelPosition s_labelPosition;
    static utils::ISettings::EmptyLines s_emptyLines;
    static bool s_tableOutput;
};

} // namespace convert
} // namespace csvvalidator::data
