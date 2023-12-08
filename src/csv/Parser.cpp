///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  csv::Parser.cpp
/// @brief Functions for .csv file parser
///

#include "Parser.h"
#include "../data/CsvData.h"
#include "../utils/IFileHandler.h"

#include <algorithm>
#include <fstream>
#include <iostream>

namespace csvvalidator {
namespace csv {

const char DELIMITER            = ';';
const std::string INVALID_LABEL = "<INVALID_LABEL>";

const std::string getLabel(const data::csv::Labels& p_labels,
                           const size_t p_fieldCounter)
{
    if (p_fieldCounter < 0 || p_fieldCounter > p_labels.size() - 1) {
        return INVALID_LABEL;
    }
    return p_labels.at(p_fieldCounter);
}

data::csv::Record getRecords(const std::string& p_line,
                             const data::csv::Labels& p_labels)
{
    if (p_line.length() == 0) {
        return {};
    }
    data::csv::Record record {};
    data::csv::Fields fields {};
    size_t offset { 0 };
    size_t semicolonPos { 0 };
    size_t fieldCounter { 0 };
    do {
        data::csv::Field field {};
        semicolonPos           = p_line.find(DELIMITER, offset);
        field.m_content.first  = getLabel(p_labels, fieldCounter);
        field.m_content.second = p_line.substr(offset, semicolonPos - offset);
        fields.push_back(field);
        offset = semicolonPos + 1;
        ++fieldCounter;
    } while (semicolonPos < std::string::npos);
    record.second = fields;
    return record;
}

const data::csv::Labels getLabels(const std::string& p_line)
{
    if (p_line.empty()) {
        return {};
    }
    data::csv::Labels labels {};
    size_t offset { 0 };
    size_t semicolonPos { 0 };
    do {
        semicolonPos = p_line.find(DELIMITER, offset);
        labels.push_back(p_line.substr(offset, semicolonPos - offset));
        offset = semicolonPos + 1;
    } while (semicolonPos < std::string::npos);
    return labels;
}

const data::csv::File parse(std::fstream& p_file,
                            const unsigned char p_delimiter)
{
    if (p_file.peek() == std::char_traits<char>::eof()) {
        return {};
    }
    data::csv::File file {};
    std::string line {};
    bool firstNonEmptyLineFound { false };
    size_t fileLineCounter { 0 };
    while (!firstNonEmptyLineFound && std::getline(p_file, line)) {
        ++fileLineCounter;
        if (!line.empty()) {
            file.m_labels          = getLabels(line);
            firstNonEmptyLineFound = true;
        }
    }
    while (std::getline(p_file, line)) {
        ++fileLineCounter;
        file.m_content.push_back(getRecords(line, file.m_labels));
        file.m_content.back().first.m_fileLineNumber = fileLineCounter;
    }
    return file;
}

const data::csv::File Parser::process(utils::IFileHandler& p_csvFile)
{
    data::csv::File csvFile = parse(p_csvFile.get(), m_settings.delimiter());
    csvFile.m_fileName      = p_csvFile.fileName();
    return csvFile;
}

} // namespace csv
} // namespace csvvalidator