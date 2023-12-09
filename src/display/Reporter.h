///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Reporter.h
/// @brief Declaration of the Reporter class
///

#pragma once

#include "../data/CsvData.h"
#include "../data/Report.h"
#include "../data/Result.h"

namespace csvvalidator {
namespace display {

///
/// @brief Creates report from csv::File and csv::Result data
///
class Reporter
{
public:
    explicit Reporter(const utils::ISettings& p_settings) :
        m_settings(p_settings)
    {
    }

    ///
    /// Convert csv::File and csv::Result to display::Report
    ///
    /// @param[in] - csvFile : the analyzed csv::File
    /// @param[in] - result  : the result of the analyzetion
    /// @return the summarized report about a .csv file
    ///
    const data::display::Report process(const data::csv::File& p_csvFile,
                                        const data::csv::Result& p_result);
    const data::display::Table addFileInfo(const data::csv::File& p_csvFile,
                                           const data::csv::Result& p_result);
    const data::display::Table addFileContent(const data::csv::File& p_csvFile);
    const data::display::Table addErrorList(const data::csv::Result& p_result);

private:
    const utils::ISettings& m_settings;
};

} // namespace display
} // namespace csvvalidator
