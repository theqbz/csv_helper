///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Parser.h
/// @brief Declaration of .csv file parser class
///

#pragma once

#include "../utils/IFileHandler.h"
#include "../utils/ISettings.h"
#include "../data/CsvData.h"
#include "IParser.h"

namespace csvvalidator {
namespace csv {

///
/// @brief Csv file parser class.
///
/// Creates a csv::File datastructure from a *csv file*
///
class Parser : public IParser
{
public:
    Parser() = delete;

    ///
    /// Constructor for csv::Parser class.
    ///
    /// @param[in] p_settings : a reference to the Settings class
    ///
    Parser(const utils::ISettings& p_settings) :
        m_settings(p_settings)
    {
    }

    Parser(const Parser&) = delete;
    Parser(Parser&&)      = delete;

    ///
    /// Parse a .csv file to a csv::File
    ///
    /// @param[in] p_csvFile : a handler that holds the csv file
    /// @return a csv::File datastructure, with the content of the csv file
    ///
    const data::csv::File process(utils::IFileHandler& p_csvFile);

private:
    const utils::ISettings& m_settings;
};

} // namespace csv
} // namespace csvvalidator
