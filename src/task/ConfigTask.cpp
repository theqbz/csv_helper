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

void updateExistingOptions(data::SettingData* p_existingIniFile,
                           const data::SettingData& p_newOptions)
{
    typedef data::SettingData::iterator it;
    if (!p_existingIniFile) {
        std::cout << "Program logic error: nullptr as existingIniFile @ updateExistingOptions\n";
        return;
    }
    for (const auto& [key, newValue] : p_newOptions) {
        if (it optionToUpdate = p_existingIniFile->find(key);
            optionToUpdate != p_existingIniFile->end()) {
            optionToUpdate->second = newValue;
        }
    }
}

std::string convertToFileContent(const data::SettingData& p_settingData)
{
    std::string fileContent { "# CsvValidator settings\n" };
    for (const auto& [key, value] : p_settingData) {
        std::cout << "key=" << key << " value=" << value << "\n";
        fileContent += key + utils::KEY_VALUE_DELIMITER + value + "\n";
    }
    return fileContent;
}

void writeToFile(utils::IFileHandler& p_file, const data::SettingData& p_settings)
{
    if (p_file.get().good()) {
        std::cout << "Writing to " << p_file.fileName() << "\n";
        p_file.get() << convertToFileContent(p_settings);
        return;
    }
    std::cout << "Creating file " << p_file.fileName() << "\n";
    std::ofstream newFile(p_file.fileName());
    newFile << convertToFileContent(p_settings);
    newFile.close();
}

bool task::ConfigTask::run()
{
    utils::FileHandler iniFile(utils::INI_FILE);
    if (m_arguments.empty()
        && question("Would you like to create a new .ini file with the default settings in it? ")) {
        std::cout << "default settings:\n";
        for(const auto& element : utils::DEFAULT_SETTINGS){
            std::cout << "key=" << element.first << " value=" << element.second << "\n";
        }
        writeToFile(iniFile, data::SettingData(utils::DEFAULT_SETTINGS));
    }

    // TODO:
    // Check for arguments:
    // If there are no argument just the settingWriterCommand, create new -ini file with default settings
    // If there are arguments but no existing .ini file, create a new .ini file with settings that provided in arguments
    // If there are arguments and there is an .ini file, chane the options in existing .ini file to the setting provided in arguments

    data::ini::File existingIniFile {};
    if (iniFile.get().good()) {
        existingIniFile = parser::IniFile::parse(iniFile.get());
    }
    updateExistingOptions(&existingIniFile.m_content, m_arguments);
    iniFile.get() << convertToFileContent(existingIniFile.m_content);

    // TODO:
    // Try to open existing ini file
    // If it exists, parse it
    //   Compare the ini file content with the settings, stored in m_arguments
    //   Write to the file the new settings
    // If it is not exists, create a new file with default settings merged with the settings, strored in m_arguments
    return false;
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
