///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  IAnalyzer.h
/// @brief Interface declaration for Analyzer class
///

#pragma once

#include "../data/CsvData.h"
#include "../data/Result.h"

namespace csvvalidator {
namespace csv {

///
/// @brief Interface for csv::Analyzer class.
///
class IAnalyzer
{
public:
    IAnalyzer()          = default;
    virtual ~IAnalyzer() = default;

    virtual data::csv::Result process(data::csv::File& p_csvFile) = 0;
};

} // namespace csv
} // namespace csvvalidator
