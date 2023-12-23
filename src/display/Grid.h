///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Grid.h
/// @brief Display the result of the csv::File Analisys in a grid (ftxui table)
///

#pragma once

#include "../utils/ISettings.h"
#include "IDisplay.h"

namespace csvvalidator {
namespace display {

class Grid : public IDisplay
{
public:
    Grid(const utils::ISettings& p_settings) :
        m_settings(p_settings)
    {
    }

    void render(const data::display::Report& p_report) const;

private:
    const utils::ISettings& m_settings;
};

} // namespace display
} // namespace csvvalidator
