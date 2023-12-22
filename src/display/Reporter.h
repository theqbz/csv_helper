///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Reporter.h
/// @brief Declaration of the Reporter class
///

#pragma once

#include "../data/CsvData.h"
#include "../data/Ranges.h"
#include "../data/Report.h"
#include "../data/Result.h"
#include "IReporter.h"

namespace csvvalidator {
namespace display {

///
/// @brief Creates report from csv::File and csv::Result data
///
class Reporter : public IReporter
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
                                        const data::csv::Result& p_result) const final;
    const data::display::Table addFileInfo(const data::csv::File& p_csvFile,
                                           const data::csv::Result& p_result) const;
    const data::display::Table addFileContent(const data::csv::File& p_csvFile) const;
    const data::display::Table addErrorList(const data::csv::Result& p_result) const;

    const data::display::Ranges getRanges(const std::vector<size_t>& p_errorLineNumbers,
                                          const size_t p_upperLimit) const;

    const bool isLabelInline() const;
    const std::string getFieldContent(const data::csv::Field& p_field) const;
    const bool isEmptyRowAndSkipIt(const data::csv::RecordHead::State& p_recordState) const;
    const data::display::Row addLine(const data::csv::Record& p_record,
                                     const size_t p_lastLineNumber) const;
    const data::display::Table addLines(const data::csv::File& p_csvFile,
                                        const data::display::Ranges& p_finalRanges) const;

private:
    const utils::ISettings& m_settings;
};

} // namespace display
} // namespace csvvalidator
