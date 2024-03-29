///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  IReporter.h
/// @brief Interface declaration of the Reporter class
///

#pragma once

#include "../data/CsvData.h"
#include "../data/Report.h"
#include "../data/Result.h"

namespace csvvalidator {
namespace display {

///
/// @brief Interface for display::Reporter class.
///
class IReporter
{
public:
    IReporter()          = default;
    virtual ~IReporter() = default;

    virtual const data::display::Report process(const data::csv::File& p_csvFile,
                                                const data::csv::Result& p_result) const
        = 0;
};

} // namespace display
} // namespace csvvalidator
