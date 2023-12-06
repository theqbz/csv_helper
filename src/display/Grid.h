///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Grid.h
/// @brief Display the result of the csv::File Analisys in a grid (ftxui table)
///

#pragma once

#include "IDisplay.h"
#include "../utils/ISettings.h"

namespace csvhelper {
namespace display {

class Grid : public IDisplay
{
public:
    Grid(const utils::ISettings& p_settings):
        m_settings(p_settings)
    {
    }

    void render(/* const Report& p_report */);

private:
    const utils::ISettings& m_settings;
};

} // namespace display
} // namespace csvhelper
