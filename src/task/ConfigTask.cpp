///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  ConfigTask.cpp
/// @brief Definition of ConfigTask class
///

#pragma once

#include "ConfigTask.h"
#include "../data/IniFile.h"
#include "../data/SettingData.h"
#include "../parser/IniFile.h"
#include "../utils/FileHandler.h"
#include "../utils/Utility.h"

#include <iostream>
#include <map>
#include <string>

namespace csvvalidator {
namespace task {

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
    // TODO:
    // create conversion
    return std::string();
}

bool task::ConfigTask::run()
{
    data::ini::File existingIniFile {};
    utils::FileHandler iniFile(utils::INI_FILE);
    if (iniFile.get().good()) {
        existingIniFile = parser::IniFile::parse(iniFile.get());
    }
    updateExistingOptions(&existingIniFile.m_content, m_settings);
    iniFile.get() << convertToFileContent(existingIniFile.m_content);

    // Try to open existing ini file
    // If it exists, parse it
    //   Compare the ini file content with the settings, stored in m_settings
    //   Write to the file the new settings
    // If it is not exists, create a new file with default settings merged with the settings, strored in m_settings
    return false;
}

} // namespace task
} // namespace csvvalidator
