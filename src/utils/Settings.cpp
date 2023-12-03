//
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Settings.cpp
/// @brief Definition of the Settings class and helper functions to store settings
///

#include "Settings.h"
#include "parser/data/SettingData.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>

namespace csvhelper {
namespace utils {

const std::string DEFAULT_INI_FILE    = "settings.ini";
const std::string SETTING_WRITER_FLAG = "settings";

// TODO:
// Do this storeNewDefaultSettings outside of the class!
[[noreturn]] static void storeNewDefaultSettings(const parser::data::SettingData& p_tasks)
{
    // TODO: 1) write new settings into .ini file
    //       2) exit program!
    exit(1);
}

bool isNumber(const std::string& p_text)
{
    std::string::const_iterator it = p_text.begin();
    for (; it < p_text.end() && std::isdigit(*it); ++it) { }
    return it == p_text.end();
}

int convertToInt(const std::string& p_text)
{
    if (p_text.empty() || !isNumber(p_text)) {
        return 0;
    }
    return stoi(p_text);
}

unsigned char convertToChar(const std::string& p_text)
{
    return p_text.at(0);
}

bool convertToBool(const std::string& p_text)
{
    std::set<std::string> truePhrases { "true", "yes", "on", "1" };
    return truePhrases.contains(p_text);
}

Settings::LabelPosition convertToLabelPosition(const std::string& p_text)
{
    if (p_text == "inline") {
        return Settings::LabelPosition::Inline;
    }
    if (p_text != "top") {
        std::cout << "Error with argument \"LabelPosition\". This option will be set to default.\n"
                  << "( Possible values: -labelPosition [ top | inline ] )";
    }
    return Settings::LabelPosition::Top;
}

Settings::DiffDetectMode convertToDiffMode(const std::string& p_text)
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
                  << "( Possible values: -diffMode [ off | auto | above | below ] )";
    }
    return Settings::DiffDetectMode::Off;
}

void Settings::init()
{
    // TODO:
    // Make this decision about writing settings, outside of the class!
    if (const auto search = m_consoleArguments.find(SETTING_WRITER_FLAG);
        search != m_consoleArguments.end()) {
        storeNewDefaultSettings(m_consoleArguments);
    }
    parser::data::SettingData settingsToStore {};
    settingsToStore.merge(m_consoleArguments);
    settingsToStore.merge(m_iniFile);
    storeSettings(settingsToStore);
}

void Settings::storeSettings(const parser::data::SettingData& p_settingsData)
{
    if (const auto delimiter = p_settingsData.find("delimiter");
        delimiter != p_settingsData.end()) {
        m_delimiter = convertToChar(delimiter->second);
    }
    if (const auto error_lines = p_settingsData.find("errorLines");
        error_lines != p_settingsData.end()) {
        m_linesAroundErrors = convertToInt(error_lines->second);
    }
    if (const auto label_position = p_settingsData.find("labelPosition");
        label_position != p_settingsData.end()) {
        m_labelPosition = convertToLabelPosition(label_position->second);
    }
    if (const auto empty_fields = p_settingsData.find("emptyFields");
        empty_fields != p_settingsData.end()) {
        m_emptyFields = convertToChar(empty_fields->second);
    }
    if (const auto empty_lines = p_settingsData.find("emptyLines");
        empty_lines != p_settingsData.end()) {
        m_emptyLines = convertToInt(empty_lines->second);
    }
    if (const auto table_output = p_settingsData.find("table");
        table_output != p_settingsData.end()) {
        m_tableOutput = convertToBool(table_output->second);
    }
    if (const auto diff_detect_mode = p_settingsData.find("diffMode");
        diff_detect_mode != p_settingsData.end()) {
        m_diff = convertToDiffMode(diff_detect_mode->second);
    }
}

} // namespace utils
} // namespace csvhelper
