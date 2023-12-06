///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  TableGenerator.h
/// @brief Declaration of table generator class
///

#pragma once

#include "../csv/Data.h"
#include "../csv/Result.h"
#include "../utils/ISettings.h"
#include "Table.h"

namespace csvhelper {
namespace display {

class TableGenerator
{
public:
    TableGenerator(utils::ISettings& p_settings) :
        m_settings(p_settings)
    {
    }

    // TODO:
    // generate Report instead of Table
    const display::Table convert(const csv::File& p_csvFile, const csv::Result& p_analisysResult);

private:
    utils::ISettings& m_settings;
};

} // namespace display
} // namespace csvhelper
