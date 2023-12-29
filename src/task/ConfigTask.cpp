///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  ConfigTask.cpp
/// @brief Definition of ConfigTask class
///

#include "ConfigTask.h"
#include "../data/IniFile.h"
#include "../data/SettingData.h"
#include "../parser/IniFile.h"
#include "../utils/FileHandler.h"
#include "../utils/Utility.h"

#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <string>

namespace csvvalidator {
namespace task {

static bool question(const std::string& p_text);

std::string convertToFileContent(const data::SettingData& p_settingData)
{
    std::string fileContent { "# CsvValidator settings\n" };
    for (const auto& [key, value] : p_settingData) {
        fileContent += key + utils::KEY_VALUE_DELIMITER + value + "\n";
    }
    return fileContent;
}

void write(const data::SettingData& p_settings)
{
    utils::FileHandler file(utils::INI_FILE);
    if (!file.get().good()) {
        DEBUG_LOG("Creating file " + file.fileName() + " for config\n", true);
        std::ofstream newFile(file.fileName());
        newFile << convertToFileContent(p_settings).c_str();
        newFile.close();
        return;
    }
    DEBUG_LOG("Writing config to " + file.fileName() + "\n", true);
    file.get() << convertToFileContent(p_settings).c_str();
}

void storeDefaultSettings()
{
    if (question("Would you like to create a _new_ .ini file with the _default_ settings? ")) {
        write(data::SettingData(utils::DEFAULT_SETTINGS));
    }
}

void updateIniFile(data::SettingData& p_settings)
{
    DEBUG_LOG("Updating existing .ini file\n", utils::verbose);
    data::ini::File existingIniFile {};
    {
        utils::FileHandler file(utils::INI_FILE);
        existingIniFile = parser::IniFile::read(file.get());
    }

    DEBUG_LOG("Setting from existing .ini file:\n", utils::verbose);
    PRINT_SETTINGS(existingIniFile.m_content, utils::verbose);
    DEBUG_LOG("Settings from console args:\n", utils::verbose);
    PRINT_SETTINGS(p_settings, utils::verbose);

    data::SettingData newIniContent {};
    newIniContent.merge(p_settings);
    newIniContent.merge(existingIniFile.m_content);

    DEBUG_LOG("Merged settings:\n", utils::verbose);
    PRINT_SETTINGS(newIniContent, utils::verbose);

    write(newIniContent);
}

bool task::ConfigTask::run()
{
    DEBUG_LOG("ConfigTask running\n", utils::verbose);
    if (m_arguments.empty()) {
        DEBUG_LOG("No arguments to store to .ini file\n", utils::verbose);
        storeDefaultSettings();
        return true;
    }
    updateIniFile(m_arguments);
    return true;
}

bool question(const std::string& p_text)
{
    std::cout << p_text;
    std::string answer {};
    std::cin >> answer;
    return utils::YES_ANSWERS.contains(answer);
}

} // namespace task
} // namespace csvvalidator
