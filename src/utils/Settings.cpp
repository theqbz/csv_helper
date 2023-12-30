//
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Settings.cpp
/// @brief Definition of the Settings class and helper functions to store settings
///

#include "Settings.h"
#include "../data/SettingData.h"
#include "../utils/Utility.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <string>
#include <utility>

namespace csvvalidator {
namespace utils {

bool isNumber(const std::string& p_text)
{
    std::string::const_iterator it = p_text.begin();
    for (; it < p_text.end() && std::isdigit(*it); ++it) { }
    return it == p_text.end();
}

size_t convertToSizeT(const std::string& p_text)
{
    if (p_text.empty() || !isNumber(p_text)) {
        return std::numeric_limits<size_t>::max();
    }
    return stoi(p_text);
}

char convertToChar(const std::string& p_text)
{
    if (p_text.empty()) {
        return 0;
    }
    return p_text.at(0);
}

bool convertToBool(const std::string& p_text)
{
    std::set<std::string> truePhrases { "true", "yes", "on", "1" };
    return truePhrases.contains(p_text);
}

ISettings::EmptyLines convertToEmptyLines(const std::string& p_text)
{
    if (p_text == "keep") {
        return ISettings::EmptyLines::Keep;
    }
    if (p_text == "error") {
        return ISettings::EmptyLines::Error;
    }
    if (p_text != "skip") {
        std::cout << "Error with argument \"EmptyLines\". This option will be set to default (skip).\n"
                  << "( Possible values: -emptyLines [ skip | error | keep ] )\n";
    }
    return ISettings::EmptyLines::Skip;
}

ISettings::LabelPosition convertToLabelPosition(const std::string& p_text)
{
    if (p_text == "inline") {
        return ISettings::LabelPosition::Inline;
    }
    if (p_text != "top") {
        std::cout << "Error with argument \"LabelPosition\". This option will be set to default (top).\n"
                  << "( Possible values: -labelPosition [ top | inline ] )\n";
    }
    return ISettings::LabelPosition::Top;
}

ISettings::DiffDetectMode convertToDiffMode(const std::string& p_text)
{
    if (p_text == "above") {
        return ISettings::DiffDetectMode::Above;
    }
    if (p_text == "below") {
        return ISettings::DiffDetectMode::Below;
    }
    if (p_text == "auto") {
        return ISettings::DiffDetectMode::Auto;
    }
    if (p_text != "off") {
        std::cout << "Error with argument \"DiffDetectMode\". This option will be set to default (off).\n"
                  << "( Possible values: -diffMode [ off | auto | above | below ] )\n";
    }
    return ISettings::DiffDetectMode::Off;
}

ISettings::ErrorLevel convertToErrorLevel(const std::string& p_text)
{
    if (p_text == "all") {
        return ISettings::ErrorLevel::All;
    }
    if (p_text != "error") {
        std::cout << "Error with argument \"ErrorLevel\". This option will ve se to default (error).\n"
                  << "( Possible values: -errorLevel [ all | error ] )\n";
    }
    return ISettings::ErrorLevel::Error;
}

void Settings::init()
{
    LOG("Storing settings\n", utils::verbose);
    LOG("Defaults:\n", utils::verbose);
    PRINT_SETTINGS(utils::DEFAULT_SETTINGS, utils::verbose);
    LOG("From .ini file:\n", utils::verbose);
    PRINT_SETTINGS(m_iniFile, utils::verbose);
    LOG("From console args:\n", utils::verbose);
    PRINT_SETTINGS(m_consoleArguments, utils::verbose);

    data::SettingData settingsToStore {};
    settingsToStore.merge(m_consoleArguments);
    settingsToStore.merge(m_iniFile);
    settingsToStore.merge(data::SettingData(utils::DEFAULT_SETTINGS));
    storeSettings(settingsToStore);
}

void Settings::storeSettings(const data::SettingData& p_settingsData)
{
    typedef data::SettingData::const_iterator it;
    if (it delimiter = p_settingsData.find("delimiter");
        delimiter != p_settingsData.end()) {
        m_delimiter = convertToChar(delimiter->second);
    }
    if (it error_lines = p_settingsData.find("errorLines");
        error_lines != p_settingsData.end()) {
        m_linesAroundErrors = convertToSizeT(error_lines->second);
    }
    if (it labels = p_settingsData.find("labels");
        labels != p_settingsData.end()) {
        m_labels = convertToLabelPosition(labels->second);
    }
    if (it empty_fields = p_settingsData.find("emptyFields");
        empty_fields != p_settingsData.end()) {
        m_emptyFields = convertToChar(empty_fields->second);
    }
    if (it empty_lines = p_settingsData.find("emptyLines");
        empty_lines != p_settingsData.end()) {
        m_emptyLines = convertToEmptyLines(empty_lines->second);
    }
    if (it table_output = p_settingsData.find("table");
        table_output != p_settingsData.end()) {
        m_tableOutput = convertToBool(table_output->second);
    }
    if (it diff_detect_mode = p_settingsData.find("diffMode");
        diff_detect_mode != p_settingsData.end()) {
        m_diff = convertToDiffMode(diff_detect_mode->second);
    }
    if (it error_level = p_settingsData.find("errorLevel");
        error_level != p_settingsData.end()) {
        m_errorLevel = convertToErrorLevel(error_level->second);
    }
}

} // namespace utils
} // namespace csvvalidator
