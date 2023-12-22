///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Analyzer.h
/// @brief Interface definition for Analyzer class
///

#pragma once

#include "../data/CsvData.h"
#include "../data/Result.h"

namespace csvvalidator {
namespace csv {

class IAnalyzer
{
public:
    IAnalyzer()          = default;
    virtual ~IAnalyzer() = default;

    virtual data::csv::Result process(data::csv::File& p_csvFile) = 0;
};

} // namespace csv
} // namespace csvvalidator
