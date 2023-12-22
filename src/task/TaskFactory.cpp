///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  TaskFactory.h
/// @brief Declaration of TaskFactory class
///

#pragma once

#include "TaskFactory.h"
#include "../data/ConsoleArguments.h"
#include "../utils/Utility.h"
#include "CsvTask.h"
#include "HelpTask.h"

#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

namespace csvvalidator {
namespace task {

static bool isHelp(data::console::Arguments p_arguments);

void TaskFactory::init(const data::console::Arguments& p_arguments)
{
    if (p_arguments.m_command.empty()) {
        m_tasks.push(std::make_shared<HelpTask>(NO_ARGS));
        return;
    }
    if (p_arguments.m_command == SETTING_WRITER_COMMAND) {
        if (isHelp(p_arguments)) {
            m_tasks.push(std::make_shared<HelpTask>(SETTING_WRITER_COMMAND));
            return;
        }
        // TODO:
        // Create a setting writer task with p_arguments
    }
    const std::filesystem::path path(p_arguments.m_command);
    std::error_code errorCode;
    if (std::filesystem::is_regular_file(path, errorCode)) {
        m_tasks.push(std::make_shared<CsvTask>(p_arguments, m_settings));
        return;
    }
    if (errorCode) {
        std::cout << "Error in Task Factory, with is_regular_file: " << errorCode.message() << "\n";
        return;
    }
    if (std::filesystem::is_directory(path, errorCode)) {
        // TODO:
        // search the directory for .csv files 
        // and create CsvTasks from each found .csv file
        // If there are no .csv file in the directory, print an error message
        return;
    }
    if (errorCode) {
        std::cout << "Error in Task Factory, with is_directory: " << errorCode.message() << "\n";
        return;
    }
}
static bool isHelp(data::console::Arguments p_arguments)
{
    for (const std::string& helpFlag : HELP_COMMANDS) {
        if (p_arguments.find(helpFlag) != p_arguments.end()) {
            return true;
        }
    }
    return false;
}

} // namespace task
} // namespace csvvalidator