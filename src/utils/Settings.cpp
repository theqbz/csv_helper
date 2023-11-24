/******************************************************************************
 * CSV HELPER by QBZ
 ******************************************************************************
 * Settings
 * implementation of Settings class
 *****************************************************************************/

#include "Settings.h"
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>

namespace csvhelper::settings {

typedef std::pair<std::string, std::string> Pair;
typedef std::map<std::string, std::string> Tasks;

const std::string DEFAULT_INI_FILE    = "settings.ini";
const std::string SETTING_WRITER_FLAG = "settings";
const std::string COMMENT_SIGNS       = "#;";
const std::string KEY_VALUE_DELIMITER = "=";
const std::string WHITESPACE          = " \t\n";

static std::fstream
openFile(const std::string& p_fileName)
{
    std::fstream file(p_fileName);
    if (!file.good()) {
        return {};
    }
    return file;
}

[[noreturn]] static void
storeNewDefaultSettings(const Tasks& p_tasks)
{
    // TODO: 1) write new settings into .ini file
    //       2) exit program!
    exit(1);
}

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

const Pair
parseIniLine(const std::string& p_line)
{
    if (p_line.empty()) {
        return {};
    }
    const size_t commentPos   = p_line.find_first_of(COMMENT_SIGNS);
    const size_t delimiterPos = p_line.find(KEY_VALUE_DELIMITER, 0);
    if (delimiterPos >= commentPos) {
        return {};
    }
    Pair pair;
    pair.first  = trim(p_line.substr(0, delimiterPos));
    pair.second = trim(p_line.substr(delimiterPos + 1));
    return pair;
}

const Tasks
parseIniFile(std::fstream p_iniFile)
{
    if (p_iniFile.peek() == std::char_traits<char>::eof()) {
        // TODO: create default .ini file
        //       or not? -> only when user ask for it with SETTING_WRITER_FLAG?
        return {};
    }
    Tasks tasks;
    std::string line;
    while (std::getline(p_iniFile, line)) {
        if (!line.empty()) {
            const auto [it, success] = tasks.insert(parseIniLine(line));
            if (!success) {
                std::cout << "Error in .ini file: " << line << "\n";
            }
        }
    }
    return tasks;
}

bool isNumber(const std::string& p_text)
{
    if (p_text.empty()) {
        return false;
    }
    // TODO: check if p_text contains only digits
    return true;
}

int convertToInt(const std::string& p_text)
{
    if (p_text.empty() || !isNumber(p_text)) {
        return 0;
    }
    return stoi(p_text);
}

unsigned char
convertToChar(const std::string& p_text)
{
    return p_text.at(0);
}

bool convertToBool(const std::string& p_text)
{
    std::set<std::string> truePhraseSet { "true", "yes", "on", "1" };
    return truePhraseSet.contains(p_text);
}

Settings::LabelPosition
convertToLabelPosition(const std::string& p_text)
{
    if (p_text == "inline") {
        return Settings::LabelPosition::Inline;
    }
    if (p_text != "top") {
        std::cout << "Error with argument \"LabelPosition\". This option will be set to default.\n"
                  << "( Possible values: -labelPosition [ top | inline ]";
    }
    return Settings::LabelPosition::Top;
}

Settings::DiffDetectMode
convertToDiffMode(const std::string& p_text)
{
    if (p_text == "above") {
        return Settings::DiffDetectMode::Above;
    }
    if (p_text == "below") {
        return Settings::DiffDetectMode::Below;
    }
    if (p_text == "auto") {
        return Settings::DiffDetectMode::Auto;
    }
    if (p_text != "off") {
        std::cout << "Error with argument \"DiffDetectMode\". This option will be set to default.\n"
                  << "( Possible values: -diffMode [ off | auto | above | below ]";
    }
    return Settings::DiffDetectMode::Off;
}

void Settings::init()
{
    const Tasks tasksFromConsole = m_consoleParser.getTaskList();
    if (const auto search = tasksFromConsole.find(SETTING_WRITER_FLAG);
        search != tasksFromConsole.end()) {
        storeNewDefaultSettings(tasksFromConsole);
    }
    const Tasks tasksFromIniFile = parseIniFile(openFile(DEFAULT_INI_FILE));
    storeSettings(tasksFromIniFile);
    storeSettings(tasksFromConsole);
    // TODO:
    // 1) store option's value from ini file
    // 2) replace values at options which modified with console args
}

void Settings::storeSettings(const Tasks& p_tasks)
{
    if (const auto error_lines = p_tasks.find("errorLines");
        error_lines != p_tasks.end()) {
        m_linesAroundErrors = convertToInt(error_lines->second);
    }
    if (const auto label_position = p_tasks.find("labelPosition");
        label_position != p_tasks.end()) {
        m_labelPosition = convertToLabelPosition(label_position->second);
    }
    if (const auto empty_fields = p_tasks.find("emptyFields");
        empty_fields != p_tasks.end()) {
        m_emptyFields = convertToChar(empty_fields->second);
    }
    if (const auto empty_lines = p_tasks.find("emptyLines");
        empty_lines != p_tasks.end()) {
        m_emptyLines = convertToInt(empty_lines->second);
    }
    if (const auto table_output = p_tasks.find("table");
        table_output != p_tasks.end()) {
        m_tableOutput = convertToBool(table_output->second);
    }
    if (const auto diff_detect_mode = p_tasks.find("diffMode");
        diff_detect_mode != p_tasks.end()) {
        m_diff = convertToDiffMode(diff_detect_mode->second);
    }
}

} // namespace csvhelper::settings
