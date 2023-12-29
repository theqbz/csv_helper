///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Lines.h
/// @brief Display the result of the csv::File Analisys in console line by line
///

#pragma once

#include "../data/Report.h"
#include "../utils/ISettings.h"
#include "../utils/Utility.h"
#include "IDisplay.h"

namespace csvvalidator {
namespace display {

class Lines : public IDisplay
{
public:
    Lines(const utils::ISettings& p_settings) :
        m_settings(p_settings)
    {
        DEBUG_LOG("Lines display created\n", utils::verbose);
    }

    void render(const data::display::Report& p_report) const final;

    void printSimpleTable(const data::display::Table& p_table) const;
    void printFileTable(const data::display::Table& p_table) const;

private:
    const utils::ISettings& m_settings;
};

} // namespace display
} // namespace csvvalidator
