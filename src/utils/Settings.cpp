/******************************************************************************
 * CSV HELPER by QBZ
 ******************************************************************************
 * Settings
 * implementation of Settings class
 *****************************************************************************/

#include "Settings.h"
#include "datastructure/Arguments.h"
#include "datastructure/IniData.h"
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>

namespace csvhelper {
namespace settings {

typedef std::map<std::string, std::string> Tasks;

const std::string DEFAULT_INI_FILE    = "settings.ini";
const std::string SETTING_WRITER_FLAG = "settings";

[[noreturn]] static void
storeNewDefaultSettings(const Tasks& p_tasks)
{
    // TODO: 1) write new settings into .ini file
    //       2) exit program!
    exit(1);
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
    const csvhelper::utils::console::Arguments tasksFromConsole = m_consoleParser.get();
    if (const auto search = tasksFromConsole.find(SETTING_WRITER_FLAG);
        search != tasksFromConsole.end()) {
        storeNewDefaultSettings(tasksFromConsole);
    }
    const csvhelper::utils::ini::File tasksFromIniFile = m_iniFileParser.get();
    storeSettings(tasksFromIniFile.m_content);
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

} // namespace settings
} // namespace csvhelper
