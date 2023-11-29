///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  IniFile.cpp
/// @brief Functions for .ini file parser of csvhelper
///

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

///
/// Trim whitespaces from the edges of text
///
/// @param[in] - p_text : the text to trim
/// @return the trimmed text
///
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

///
/// Read record from a line of a .ini file
///
/// @param[in] - p_line : the line of the file
/// @return a Record, contains a < key, value > pair
///
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

///
/// Create a ini::File data from a .ini file.
/// Parse the file line by line and store the records. (If it find a second
/// record with the same key, the first occurrence will be stored.)
///
/// @param[in] - p_iniFile : a filestream contains the .ini file
/// @return a File, contains the records of the .ini file
///
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
                std::cout << "Error in .ini record: " << line << "\n";
            }
        }
    }
    return iniFile;
}

} // namespace parser
} // namespace csvhelper
