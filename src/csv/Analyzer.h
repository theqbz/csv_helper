///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Analyzer.h
/// @brief Declaration of csv::File analyzer class
///

#pragma once

#include "../data/CsvData.h"
#include "../data/Result.h"
#include "../utils/ISettings.h"
#include "IAnalyzer.h"

namespace csvvalidator {
namespace csv {

///
/// @brief Analyze a csv::File and create a csv::Result about the process.
/// 
class Analyzer : public IAnalyzer
{
public:
    Analyzer() = delete;

    ///
    /// Contructor for Settings class.
    ///
    /// Store the console arguments and the content of the .ini file, and sets
    /// all options to default state.
    ///
    /// @param - consoleArguments : the ordered content of console args
    /// @param - iniFile          : the ordered content of records from .ini file
    ///
    Analyzer(const utils::ISettings& p_settings) :
        m_settings(p_settings)
    {
    }

    Analyzer(const Analyzer&) = delete;
    Analyzer(Analyzer&&)      = delete;

    ///
    /// Analyze the csv::File
    /// (The analysis modifies some attributes of the csv::File)
    ///
    /// @param[in,out] csvFile : the csv::File to analyze
    /// @return The result of the analysis
    ///
    data::csv::Result process(data::csv::File& p_csvFile) final;

private:
    const utils::ISettings& m_settings;
};

} // namespace csv
} // namespace csvvalidator
