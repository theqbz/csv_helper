///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  IParser.h
/// @brief Interface declaration of Parser class
///

#pragma once

#include "../data/CsvData.h"
#include "../utils/IFileHandler.h"

namespace csvvalidator {
namespace csv {

///
/// @brief Interface for csv::Parser class.
/// 
class IParser
{
public:
    IParser()          = default;
    virtual ~IParser() = default;

    virtual inline const data::csv::File process(utils::IFileHandler& p_csvFile) = 0;
};

} // namespace csv
} // namespace csvvalidator
