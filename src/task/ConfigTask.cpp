///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  ConfigTask.cpp
/// @brief Definition of ConfigTask class
///

#include "ConfigTask.h"
#include "../data/SettingData.h"
#include "../parser/IniFile.h"
#include "../utils/FileHandler.h"
#include "../utils/Utility.h"

#include <filesystem>
#include <iosfwd>
#include <iostream>
#include <string>

namespace csvvalidator {
namespace task {

static bool question(const std::string& p_text);

std::string convertToFileContent(const data::SettingData& p_settingData)
{
    std::string fileContent { "# CsvValidator settings\n" };
    for (const auto& [key, value] : p_settingData) {
        fileContent += key + utils::INI_KEY_VALUE_DELIMITER + value + "\n";
    }
    return fileContent;
}

void createNewIniFile(const data::SettingData& p_settings,
                      const std::filesystem::path& p_iniPath)
{
    LOG("Creating new config file\n", true);
    std::ofstream newFile(p_iniPath);
    newFile << convertToFileContent(p_settings).c_str();
    newFile.close();
}

void updateExistingIniFile(const data::SettingData& p_settings,
                           const std::filesystem::path& p_iniPath)
{
    utils::FileHandler file(p_iniPath);
    LOG("Update config file\n", true);
    file.get() << convertToFileContent(p_settings).c_str();
}

const data::SettingData mergeSettings(data::SettingData& p_newSettings,
                                      data::SettingData& p_existingSettings)
{
    LOG("Previous setting:\n", utils::verbose);
    PRINT_SETTINGS(p_existingSettings, utils::verbose);
    LOG("New settings:\n", utils::verbose);
    PRINT_SETTINGS(p_newSettings, utils::verbose);

    data::SettingData newIniContent {};
    newIniContent.merge(p_newSettings);
    newIniContent.merge(p_existingSettings);

    LOG("Settings to be stored:\n", utils::verbose);
    PRINT_SETTINGS(newIniContent, utils::verbose);
    return newIniContent;
}

void storeSettings(data::SettingData& p_settingsToStore)
{
    LOG("Store settings\n", utils::verbose);
    const std::filesystem::path iniPath { utils::getIniLocation() };
    const bool iniFileExists { utils::iniFileExists(iniPath) };
    data::SettingData existingIniContent {};
    if (iniFileExists) {
        utils::FileHandler file(iniPath);
        existingIniContent = parser::IniFile::read(file.get()).m_content;
    }
    const data::SettingData newIniContent { mergeSettings(p_settingsToStore, existingIniContent) };
    if (iniFileExists) {
        updateExistingIniFile(newIniContent, iniPath);
        return;
    }
    createNewIniFile(newIniContent, iniPath);
}

bool task::ConfigTask::run()
{
    LOG("ConfigTask running\n", utils::verbose);
    data::SettingData settingsToStore { m_arguments };
    if (m_arguments.empty()) {
        LOG("No arguments to store to .ini file\n", utils::verbose);
        if (!question("Would you like to create a _new_ config file with the default settings? ")) {
            return true;
        }
        settingsToStore = data::SettingData(utils::DEFAULT_SETTINGS);
    }
    storeSettings(settingsToStore);
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
