///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  TaskFactory.cpp
/// @brief Definition of TaskFactory class
///

#pragma once

#include "TaskFactory.h"
#include "../data/ConsoleArguments.h"
#include "../display/Grid.h"
#include "../display/IDisplay.h"
#include "../display/Lines.h"
#include "../utils/Utility.h"
#include "ConfigTask.h"
#include "CsvTask.h"
#include "HelpTask.h"

#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

namespace csvvalidator {
namespace task {

static bool isHelp(std::string p_command);
static bool isHelp(data::console::Parameters p_parameters);
static bool isCsvFile(const std::filesystem::path& p_path);

void TaskFactory::init(const data::console::Arguments& p_arguments)
{
    LOG("Init TaskFactory\n", utils::verbose);
    // TODO:
    // add createHelpTask and createCommandTask functions to simplify this
    if (p_arguments.m_command.empty()) {
        LOG("No console arguments provided\n", utils::verbose);
        m_tasks.push(std::make_shared<HelpTask>(utils::CLI_NO_ARGS));
        return;
    }
    if (isHelp(p_arguments.m_command)) {
        LOG("Help command detected\n", utils::verbose);
        m_tasks.push(std::make_shared<HelpTask>());
        return;
    }
    if (p_arguments.m_command == utils::CLI_COMMANDS_CONFIG) {
        LOG("Config command detected\n", utils::verbose);
        if (isHelp(p_arguments.m_parameters)) {
            LOG("Config-help detected\n", utils::verbose);
            m_tasks.push(std::make_shared<HelpTask>(utils::CLI_COMMANDS_CONFIG));
            return;
        }
        m_tasks.push(std::make_shared<ConfigTask>(p_arguments.m_parameters));
        return;
    }
    const std::filesystem::file_status status { std::filesystem::status(std::filesystem::path { p_arguments.m_command }) };
    switch (status.type()) {
    case std::filesystem::file_type::none:
        std::cout << "Can't recognize the type of the file: " << p_arguments.m_command << "\n";
        break;
    case std::filesystem::file_type::not_found:
        std::cout << "Can't find the the file: " << p_arguments.m_command << "\n";
        break;
    case std::filesystem::file_type::regular:
        createSingleCsvTask(p_arguments.m_command);
        break;
    case std::filesystem::file_type::directory:
        searchDirectory(p_arguments.m_command);
        break;
    default:
        std::cout << "Not acceptable file type: " << p_arguments.m_command;
        break;
    }
}

bool TaskFactory::runTasks()
{
    bool success { true };
    while (!m_tasks.empty()) {
        success &= m_tasks.front()->run();
        m_tasks.pop();
    }
    return success;
}

void TaskFactory::createSingleCsvTask(const std::string& p_fileName)
{
    if (!isCsvFile(p_fileName)) {
        LOG("The file " + p_fileName + " is not a csv file.\n", true);
        return;
    }
    m_tasks.push(std::make_shared<CsvTask>(p_fileName, m_settings, getDisplay()));
}

void TaskFactory::searchDirectory(const std::string& p_directoryPath)
{
    LOG("Searching in direcotry: " + p_directoryPath + "\n", utils::verbose);
    std::filesystem::path path { p_directoryPath };
    size_t foundFiles { 0 };
    for (const std::filesystem::path& directoryEntry : std::filesystem::directory_iterator(path)) {
        if (isCsvFile(directoryEntry)) {
            m_tasks.push(std::make_shared<CsvTask>(directoryEntry, m_settings, getDisplay()));
            ++foundFiles;
        }
    }
    std::cout << "There was " << foundFiles << " csv files on path " << p_directoryPath << "\n";
}

std::shared_ptr<display::IDisplay> TaskFactory::getDisplay() const
{
    if (m_settings.tableOutput()) {
        return std::make_shared<display::Grid>(m_settings);
    }
    return std::make_shared<display::Lines>(m_settings);
}

static bool isHelp(std::string p_command)
{
    return utils::CLI_COMMANDS_HELP.contains(p_command);
}

static bool isHelp(data::console::Parameters p_parameters)
{
    for (const std::string& helpFlag : utils::CLI_COMMANDS_HELP) {
        if (p_parameters.find(helpFlag) != p_parameters.end()) {
            return true;
        }
    }
    return false;
}

static bool isCsvFile(const std::filesystem::path& p_path)
{
    return utils::CSV_EXTENSIONS.contains(p_path.extension().string());
}

} // namespace task
} // namespace csvvalidator
