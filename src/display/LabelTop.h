///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  LabelTop.h
/// @brief Display a csv::File with no table format and labels on top
///

#pragma once

#include "Table.h"
#include "../utils/ISettings.h"

namespace csvhelper {
namespace display {

class LabelTop
{
public:
    LabelTop(const utils::ISettings& p_settings) :
        m_settings(p_settings)
    {
    }


    void show(const Table& p_csvFile, const Table& p_result);

private:
    const utils::ISettings& m_settings;
};

} // namespace display
} // namespace csvhelper
