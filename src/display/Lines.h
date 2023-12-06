///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Lines.h
/// @brief Display the result of the csv::File Analisys in console line by line
///

#pragma once

#include "Table.h"
#include "IDisplay.h"
#include "../utils/ISettings.h"

namespace csvhelper {
namespace display {

class Lines
{
public:
    Lines(const utils::ISettings& p_settings) :
        m_settings(p_settings)
    {
    }

    void render(const Table& p_csvFile, const Table& p_result);

private:
    const utils::ISettings& m_settings;
};

} // namespace display
} // namespace csvhelper
