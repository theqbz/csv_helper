///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Analyzer.h
/// @brief Definition of csv::File analyzer class
///

#pragma once

#include "../data/CsvData.h"
#include "../data/Result.h"
#include "../utils/ISettings.h"

namespace csvvalidator {
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
    data::csv::Result process(data::csv::File& p_csvFile);

private:
    const utils::ISettings& m_settings;
};

} // namespace csv
} // namespace csvvalidator
