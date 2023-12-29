///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Lines.cpp
/// @brief Function definitions for the Lines class
///

#include "Lines.h"

#include "../data/Report.h"
#include "../utils/ISettings.h"
#include "../utils/Utility.h"

#include <iostream>
#include <string>

namespace csvvalidator {
namespace display {

static const std::string CELL_SEPARATOR = "|";

static const std::string cellSeparator(bool& p_previousCellWasEmpty,
                                       const bool p_thisCellIsEmpty,
                                       const unsigned char p_emptyCellFiller);

void Lines::render(const data::display::Report& p_report) const
{
    DEBUG_LOG("Rendering result\n\n", utils::verbose);
    printSimpleTable(p_report.m_info);
    printFileTable(p_report.m_file);
    printSimpleTable(p_report.m_errors);
    std::cout << "____\n";
}

void Lines::printSimpleTable(const data::display::Table& p_table) const
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

void Lines::printFileTable(const data::display::Table& p_table) const
{
    const bool skipEmptyRow { m_settings.emptyLines() == utils::ISettings::EmptyLines::Skip };
    const unsigned char emptyCellFiller { m_settings.emptyFields() };
    const bool skipEmptyCell { emptyCellFiller == 0 };
    if (!p_table.empty()) {
        std::cout << "\n";
    }
    for (const data::display::Row& row : p_table) {
        if (row.empty() && skipEmptyRow) {
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
                std::cout << cellSeparator(previousCellWasEmpty, thisCellIsEmpty, emptyCellFiller) << cell;
            }
        }
        std::cout << "\n";
    }
}

const std::string cellSeparator(bool& p_previousCellWasEmpty,
                                const bool p_thisCellIsEmpty,
                                const unsigned char p_emptyCellFiller)
{
    std::string separator {};
    if (!p_previousCellWasEmpty && !p_thisCellIsEmpty) {
        separator = " " + CELL_SEPARATOR + " ";
    }
    if (!p_previousCellWasEmpty && p_thisCellIsEmpty) {
        separator = " " + CELL_SEPARATOR;
    }
    if (p_previousCellWasEmpty && p_thisCellIsEmpty) {
        separator = p_emptyCellFiller;
    }
    if (p_previousCellWasEmpty && !p_thisCellIsEmpty) {
        separator = p_emptyCellFiller;
        separator += CELL_SEPARATOR + " ";
    }
    p_previousCellWasEmpty = p_thisCellIsEmpty;
    return separator;
}

} // namespace display
} // namespace csvvalidator
