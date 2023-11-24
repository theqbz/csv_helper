/******************************************************************************
 * CSV HELPER by QBZ
 ******************************************************************************
 * Settings
 * implementation of Settings class
 *****************************************************************************/

#include "Settings.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>

namespace csvhelper::settings {

typedef std::pair<std::string, std::string> Pair;
typedef std::map<std::string, std::string> Tasks;

const std::string DEFAULT_INI_FILE    = "settings.ini";
const std::string SETTING_WRITER_FLAG = "settings";
const std::string COMMENT_SIGNS       = "#;";
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
    const size_t equalsignPos = p_line.find('=', 0);
    if (!(equalsignPos < commentPos)) {
        return {};
    }
    Pair pair;
    pair.first  = trim(p_line.substr(0, equalsignPos));
    pair.second = trim(p_line.substr(equalsignPos + 1));
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

void Settings::init()
{
    const Tasks tasks = m_consoleParser.getTaskList();
    if (const auto search = tasks.find(SETTING_WRITER_FLAG); search != tasks.end()) {
        storeNewDefaultSettings(tasks);
    }
    const Tasks tasksFromIniFile = parseIniFile(openFile(DEFAULT_INI_FILE));
    // TODO:
    // 1) store option's value from ini file
    // 2) replace values at options which modified with console args
}

} // namespace csvhelper::settings
