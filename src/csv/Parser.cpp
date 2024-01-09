///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  csv::Parser.cpp
/// @brief Functions for .csv file parser
///

#include "Parser.h"
#include "../data/CsvData.h"
#include "../utils/IFileHandler.h"
#include "../utils/Utility.h"

#include <string>
#include <iosfwd>
#include <fstream>

namespace csvvalidator {
namespace csv {

const std::string getLabel(const data::csv::Labels& p_labels,
                           const size_t p_fieldCounter)
{
    if (p_fieldCounter < 0 || (p_labels.size() - 1) < p_fieldCounter) {
        return utils::CSV_INVALID_LABEL;
    }
    return p_labels.at(p_fieldCounter);
}

data::csv::Record getRecords(const std::string& p_line,
                             const data::csv::Labels& p_labels,
                             const unsigned char p_delimiter)
{
    if (p_line.length() == 0) {
        return {};
    }
    LOG("Parsing Records from csv file\n", false);
    data::csv::Record record {};
    data::csv::Fields fields {};
    size_t offset { 0 };
    size_t semicolonPos { 0 };
    size_t fieldCounter { 0 };
    do {
        data::csv::Field field {};
        semicolonPos           = p_line.find(p_delimiter, offset);
        field.m_content.first  = getLabel(p_labels, fieldCounter);
        field.m_content.second = p_line.substr(offset, semicolonPos - offset);
        fields.push_back(field);
        offset = semicolonPos + 1;
        ++fieldCounter;
    } while (semicolonPos < std::string::npos);
    record.second = fields;
    return record;
}

const data::csv::Labels getLabels(const std::string& p_line,
                                  const unsigned char p_delimiter)
{
    if (p_line.empty()) {
        return {};
    }
    LOG("Parsing Labels from csv file\n", false);
    data::csv::Labels labels {};
    size_t offset { 0 };
    size_t semicolonPos { 0 };
    do {
        semicolonPos = p_line.find(p_delimiter, offset);
        labels.push_back(p_line.substr(offset, semicolonPos - offset));
        offset = semicolonPos + 1;
    } while (semicolonPos < std::string::npos);
    return labels;
}

const data::csv::File parse(std::fstream& p_file,
                            const unsigned char p_delimiter)
{
    if (p_file.peek() == std::char_traits<char>::eof()) {
        LOG("File not exists @ csv Parser()\n", utils::verbose);
        return {};
    }
    data::csv::File file {};
    std::string line {};
    bool firstNonEmptyLineFound { false };
    size_t fileLineCounter { 0 };
    while (getline(p_file, line)) {
        ++fileLineCounter;
        if (firstNonEmptyLineFound) {
            file.m_content.push_back(getRecords(line, file.m_labels, p_delimiter));
            file.m_content.back().first.m_fileLineNumber = fileLineCounter;
        }
        if (!firstNonEmptyLineFound && !line.empty()) {
            file.m_labels          = getLabels(line, p_delimiter);
            firstNonEmptyLineFound = true;
        }
    }
    LOG(utils::INDENTATION + "total lines in file = " + std::to_string(fileLineCounter) + "\n", utils::verbose);
    LOG(utils::INDENTATION + "label count = " + std::to_string(file.m_labels.size()) + "\n", utils::verbose);
    LOG(utils::INDENTATION + "content count = " + std::to_string(file.m_content.size()) + "\n", utils::verbose);
    return file;
}

const data::csv::File Parser::process(utils::IFileHandler& p_csvFile)
{
    LOG("Parsing " + p_csvFile.fileName() + " file\n", utils::verbose);
    data::csv::File csvFile { parse(p_csvFile.get(), m_settings.delimiter()) };
    csvFile.m_fileName = p_csvFile.fileName();
    return csvFile;
}

} // namespace csv
} // namespace csvvalidator
