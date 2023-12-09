///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Lines.cpp
/// @brief Function definitions for the Lines class
///

#include "Lines.h"

#include "../data/Report.h"
#include "../utils/ISettings.h"
#include <iostream>
#include <string>

namespace csvvalidator {
namespace display {

const std::string CELL_SEPARATOR = "|";

const std::string cellSeparator(bool* p_previousCellWasEmpty,
                                const bool p_thisCellIsEmpty,
                                const unsigned char p_emptyCellFiller)
{
    if (p_previousCellWasEmpty == nullptr) {
        return {};
    }
    std::string separator {};
    if (!*p_previousCellWasEmpty && !p_thisCellIsEmpty) {
        separator = " " + CELL_SEPARATOR + " ";
    }
    if (!*p_previousCellWasEmpty && p_thisCellIsEmpty) {
        separator = " " + CELL_SEPARATOR;
        separator += p_emptyCellFiller;
    }
    if (*p_previousCellWasEmpty && p_thisCellIsEmpty) {
        separator = p_emptyCellFiller;
    }
    if (*p_previousCellWasEmpty && !p_thisCellIsEmpty) {
        separator = p_emptyCellFiller;
        separator += CELL_SEPARATOR + " ";
    }
    *p_previousCellWasEmpty = p_thisCellIsEmpty;
    return separator;
}

void Lines::render(const data::display::Table& p_csvFile, const data::display::Table& p_result)
{
    const bool skipEmptyRow { m_settings.emptyLines() == utils::ISettings::EmptyLines::Skip };
    const unsigned char emptyCellFiller { m_settings.emptyFields() };
    const bool skipEmptyCell { emptyCellFiller == 0 };
    // TODO:
    // Print some data about file
    for (const data::display::Row& row : p_csvFile) {
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
                std::cout << cellSeparator(&previousCellWasEmpty, thisCellIsEmpty, emptyCellFiller) << cell;
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    for (const data::display::Row& row : p_result) {
        for (const std::string& cell : row) {
            std::cout << cell;
        }
        std::cout << "\n";
    }
}

} // namespace display
} // namespace csvvalidator
