///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  TaskFactory.h
/// @brief Declaration of TaskFactory class
///

#pragma once

#include "../data/ConsoleArguments.h"
#include "../display/IDisplay.h"
#include "../utils/ISettings.h"
#include "ITask.h"

#include <memory>
#include <queue>
#include <string>

namespace csvvalidator {
namespace task {

class TaskFactory
{
public:
    TaskFactory()                   = delete;
    TaskFactory(const TaskFactory&) = delete;

    explicit TaskFactory(const data::console::Arguments& p_arguments,
                         const utils::ISettings& p_settings) noexcept;
    void init(const data::console::Arguments& p_arguments);
    bool runTasks();

private:
    const utils::ISettings& m_settings;
    std::queue<std::shared_ptr<task::ITask>> m_tasks;

    void createHelpTask(const std::string p_command);
    void createConfigTask(const data::console::Arguments& p_arguments);
    void createSingleCsvTask(const std::string& p_fileName);
    void createCsvTasksFromDirectory(const std::string& p_directoryPath);
    std::shared_ptr<display::IDisplay> getDisplay() const;
};

} // namespace task
} // namespace csvvalidator
