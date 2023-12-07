///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  IParser.h
/// @brief Interface definition of Parser class
///

#pragma once

#include "../utils/IFileHandler.h"
#include "../data/CsvData.h"

namespace csvvalidator {
namespace csv {

class IParser
{
public:
    IParser()          = default;
    virtual ~IParser() = default;

    virtual inline const data::csv::File process(utils::IFileHandler& p_csvFile) = 0;
};

} // namespace csv
} // namespace csvvalidator
