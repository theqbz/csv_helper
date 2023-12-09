///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Reporter.h
/// @brief Function definitions of the Reporter class
///

#include "Reporter.h"
#include <string>

namespace csvvalidator {
namespace display {

const data::display::Report Reporter::process(const data::csv::File& p_csvFile,
                                              const data::csv::Result& p_result)
{
    data::display::Report report {};
    report.m_fileInfo = addFileInfo(p_csvFile, p_result);
    report.m_file     = addFileContent(p_csvFile);
    report.m_errors   = addErrorList(p_result);
    return report;
}

const data::display::Table Reporter::addFileInfo(const data::csv::File& p_csvFile,
                                                 const data::csv::Result& p_result)
{
    return data::display::Table({ { { "File: " + p_csvFile.m_fileName } },
                                  { { "This file contains "
                                      + std::to_string(p_result.m_emptyLineCount)
                                      + " empty lines" } } });
}

const data::display::Table Reporter::addFileContent(const data::csv::File& p_csvFile)
{
    // TODO:
    // - Get the errorLines setting
    //  - if errorLines = -1 (aka max of unsigned int) it means this option is off
    // - Loop trougt the csv file and store in an array the line-index of the errors
    //  - get index with std::sidtance(.begin(), it)
    // - Create a range of each line-index dependent of errorLines setting
    // - Merge overlaped these ranges and create the final ranges
    // - add the lines from the final ranges
    return data::display::Table();
}

const data::display::Table Reporter::addErrorList(const data::csv::Result& p_result)
{
    // TODO:
    // - number of errors (if any)
    // - the errors
    return data::display::Table();
}

} // namespace display
} // namespace csvvalidator
