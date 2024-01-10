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
#include "../utils/ISettings.h"
#include "IReporter.h"

namespace csvvalidator {
namespace display {

///
/// @brief Creates report from csv::File and csv::Result data
///
class Reporter : public IReporter
{
public:
    ///
    /// @brief Constructor for Reporter class.
    ///
    /// @param[in] - p_settings (required) : a reference to the Settings class
    ///
    explicit Reporter(const utils::ISettings& p_settings);

    ///
    /// Convert csv::File and csv::Result to display::Report
    ///
    /// @param[in] - csvFile : the analyzed csv::File
    /// @param[in] - result  : the result of the analyzetion
    /// @return the summarized report about a .csv file
    ///
    const data::display::Report process(const data::csv::File& p_csvFile,
                                        const data::csv::Result& p_result) const final;

private:
    const utils::ISettings& m_settings;

    const data::display::Table addFileInfo(const data::csv::File& p_csvFile,
                                           const data::csv::Result& p_result) const;
    const data::display::Table addFileContent(const data::csv::File& p_csvFile) const;
    const data::display::Table addErrorList(const data::csv::Result& p_result) const;
    bool errorLogFilter(const auto& p_entry) const;
};

} // namespace display
} // namespace csvvalidator
