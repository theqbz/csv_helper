///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Lines.cpp
/// @brief Definition of display::Lines class.
///
#include "Lines.h"

#include "../data/Report.h"
#include "../utils/ISettings.h"
#include "../utils/Utility.h"

#include <iostream>
#include <string>

namespace csvvalidator {
namespace display {

void printFileTable(const data::display::Table& p_table, const unsigned char p_emptyCellFiller, const bool p_skipEmptyRow);
void printSimpleTable(const data::display::Table& p_table);

Lines::Lines(const utils::ISettings& p_settings) :
    m_settings(p_settings)
{
    LOG("Lines display created\n", utils::verbose);
}

void Lines::render(const data::display::Report& p_report) const
{
    const bool skipEmptyRow { m_settings.emptyLines() == utils::ISettings::EmptyLines::Skip };
    const unsigned char emptyCellFiller { m_settings.emptyFields() };
    LOG("Rendering report\n\n", utils::verbose);
    LOG(utils::INDENTATION + "Skip empty Row = " + std::string(skipEmptyRow ? "true" : "false") + "\n", utils::verbose);
    LOG(utils::INDENTATION + "Skip empty Row = " + std::to_string(emptyCellFiller) + "\n", utils::verbose);
    printSimpleTable(p_report.m_info);
    printFileTable(p_report.m_file, emptyCellFiller, skipEmptyRow);
    printSimpleTable(p_report.m_errors);
    std::cout << "____\n";
}

const std::string cellSeparator(bool& p_previousCellWasEmpty,
                                const bool p_thisCellIsEmpty,
                                const unsigned char p_emptyCellFiller)
{
    std::string separator {};
    if (!p_previousCellWasEmpty && !p_thisCellIsEmpty) {
        separator = " " + utils::DISPLAY_CELL_SEPARATOR + " ";
    }
    if (!p_previousCellWasEmpty && p_thisCellIsEmpty) {
        separator = " " + utils::DISPLAY_CELL_SEPARATOR;
    }
    if (p_previousCellWasEmpty && p_thisCellIsEmpty) {
        separator = p_emptyCellFiller;
    }
    if (p_previousCellWasEmpty && !p_thisCellIsEmpty) {
        separator = p_emptyCellFiller;
        separator += utils::DISPLAY_CELL_SEPARATOR + " ";
    }
    p_previousCellWasEmpty = p_thisCellIsEmpty;
    return separator;
}

void printFileTable(const data::display::Table& p_table,
                    const unsigned char p_emptyCellFiller,
                    const bool p_skipEmptyRow)
{
    const bool skipEmptyCell { p_emptyCellFiller == 0 };
    if (!p_table.empty()) {
        std::cout << "\n";
    }
    for (const data::display::Row& row : p_table) {
        if (row.empty() && p_skipEmptyRow) {
            continue;
        }
        bool previousCellWasEmpty { false };
        bool firstCell { true };
        for (const std::string& cell : row) {
            bool thisCellIsEmpty = cell.empty();
            if (thisCellIsEmpty && skipEmptyCell) {
                continue;
            }
            if (firstCell) {
                std::cout << cell;
                firstCell = false;
            } else {
                std::cout << cellSeparator(previousCellWasEmpty, thisCellIsEmpty, p_emptyCellFiller) << cell;
            }
        }
        std::cout << "\n";
    }
}

void printSimpleTable(const data::display::Table& p_table)
{
    // if (!p_table.empty()) {
    //     std::cout << "\n";
    // }
    for (const data::display::Row& row : p_table) {
        if (row.empty()) {
            continue;
        }
        bool firstCell { true };
        for (const std::string& cell : row) {
            if (firstCell) {
                std::cout << cell;
                firstCell = false;
            } else {
                std::cout << " " << cell;
            }
        }
        std::cout << "\n";
    }
}

} // namespace display
} // namespace csvvalidator
