///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  IniFile.cpp
/// @brief Functions for .ini file parser
///

#include "IniFile.h"
#include "../data/IniFile.h"
#include "../utils/FileHandler.h"
#include "../utils/Utility.h"

#include <filesystem>
#include <iosfwd>
#include <string>

namespace csvvalidator {
namespace parser {

const data::ini::File IniFile::parse(const std::string& p_file)
{
    std::filesystem::path iniPath { utils::getIniLocation(p_file) };
    if (!utils::iniFileExists(iniPath)) {
        LOG(iniPath.filename().string() + " file not exists\n", utils::verbose);
        return {};
    }
    utils::FileHandler iniFile(iniPath);
    return read(iniFile.get());
}

const data::ini::File IniFile::parse(std::fstream& p_file)
{
    return read(p_file);
}

const data::ini::File IniFile::read(std::fstream& p_iniFile)
{
    if (p_iniFile.peek() == std::char_traits<char>::eof()) {
        return {};
    }
    LOG("Reading ini file\n", utils::verbose);
    data::ini::File file;
    std::string line;
    size_t lineNumber { 1 };
    while (std::getline(p_iniFile, line)) {
        if (line.empty()) {
            continue;
        }
        data::ini::Record record = IniFile::line(line);
        if (record.first.empty()) {
            continue;
        }
        const auto [it, success] = file.m_content.insert(IniFile::line(line));
        if (!success) {
            LOG("Error in .ini record: " + line + " (in line " + std::to_string(lineNumber) + "\n", true);
        }
        ++lineNumber;
    }
    return file;
}

const data::ini::Record IniFile::line(const std::string& p_line)
{
    if (p_line.empty()) {
        return {};
    }
    const size_t commentPos   = p_line.find_first_of(utils::INI_COMMENT_SIGNS);
    const size_t delimiterPos = p_line.find(utils::INI_KEY_VALUE_DELIMITER, 0);
    if (commentPos < delimiterPos) {
        return {};
    }
    data::ini::Record record;
    record.first  = trim(p_line.substr(0, delimiterPos));
    record.second = trim(p_line.substr(delimiterPos + 1));
    return record;
}

const std::string IniFile::trim(const std::string& p_text)
{
    const size_t firstChar = p_text.find_first_not_of(utils::INI_WHITESPACE);
    if (firstChar == std::string::npos) {
        return {};
    }
    const size_t lastChar = p_text.find_last_not_of(utils::INI_WHITESPACE);
    if (lastChar == std::string::npos) {
        return {};
    }
    return p_text.substr(firstChar, lastChar + 1);
}

} // namespace parser
} // namespace csvvalidator
