///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Analyzer.h
/// @brief Definition of csv::File analyzer class
///

#pragma once

#include "../utils/ISettings.h"
#include "Data.h"
#include "Result.h"

namespace csvhelper {
namespace csv {

class Analyzer
{
public:
    Analyzer(const utils::ISettings& p_settings) :
        m_settings(p_settings)
    {
    }

    ///
    /// Analyze the csv::File
    /// (The analysis modifies some attributes of the csv::File)
    ///
    /// @param[in,out] csvFile : the csv::File to analyze
    /// @return The result of the analysis
    ///
    csv::Result process(csv::File& p_csvFile);

private:
    const utils::ISettings& m_settings;
};

} // namespace csv
} // namespace csvhelper
