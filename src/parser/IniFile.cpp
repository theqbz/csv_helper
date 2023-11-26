/**
 * CSV HELPER by QBZ
 *
 * @file  IniFile.cpp
 * @brief Logic implementation of parsing an .ini file for IniFile class of csvhelper
 */

#include "../utils/IFileHandler.h"
#include "../utils/datastructure/IniData.h"

#include <iostream>

namespace csvhelper {
namespace parser {

typedef csvhelper::utils::ini::Record Record;
typedef csvhelper::utils::ini::File File;

const std::string COMMENT_SIGNS       = "#;";
const std::string KEY_VALUE_DELIMITER = "=";
const std::string WHITESPACE          = " \t\n";

const std::string
trim(const std::string& p_text)
{
    const size_t firstChar = p_text.find_first_not_of(WHITESPACE);
    if (firstChar == std::string::npos) {
        return {};
    }
    const size_t lastChar = p_text.find_last_not_of(WHITESPACE, firstChar);
    if (lastChar == std::string::npos) {
        return {};
    }
    return p_text.substr(firstChar, lastChar - 1);
}

const Record
iniLine(const std::string& p_line)
{
    if (p_line.empty()) {
        return {};
    }
    const size_t commentPos   = p_line.find_first_of(COMMENT_SIGNS);
    const size_t delimiterPos = p_line.find(KEY_VALUE_DELIMITER, 0);
    if (delimiterPos >= commentPos) {
        return {};
    }
    Record record;
    record.first  = trim(p_line.substr(0, delimiterPos));
    record.second = trim(p_line.substr(delimiterPos + 1));
    return record;
}

const File
read(std::fstream& p_iniFile)
{
    if (p_iniFile.peek() == std::char_traits<char>::eof()) {
        std::cout << "Ini file error\n";
        // TODO: create default .ini file
        //       or not? -> only when user ask for it with SETTING_WRITER_FLAG from console Argument?
        return {};
    }
    std::cout << "Reading ini file\n";
    File iniFile;
    std::string line;
    while (std::getline(p_iniFile, line)) {
        if (!line.empty()) {
            const auto [it, success] = iniFile.m_content.insert(iniLine(line));
            if (!success) {
                std::cout << "Error in .ini file: " << line << "\n";
            }
        }
    }
    return iniFile;
}

} // namespace parser
} // namespace csvhelper
