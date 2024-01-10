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

///
/// @brief Task creator and executor class.
///
class TaskFactory
{
public:
    TaskFactory()                   = delete;
    TaskFactory(const TaskFactory&) = delete;

    ///
    /// @brief Constructor for TaskFactory.
    /// Stores the program settings and creates tasks from arguments.
    ///
    /// @param[in] p_settings (required)  : a reference to Settings class
    /// @param[in] p_arguments (required) : the parsed console arguments
    ///
    explicit TaskFactory(const utils::ISettings& p_settings,
                         const data::console::Arguments& p_arguments) noexcept;

    ///
    /// @brief Run each task from the task list.
    ///
    /// @param (void)
    /// @return true, if every task was successfull
    ///
    bool runTasks();

private:
    const utils::ISettings& m_settings;
    std::queue<std::shared_ptr<task::ITask>> m_tasks;

    void init(const data::console::Arguments& p_arguments);
    void createHelpTask(const std::string p_command);
    void createConfigTask(const data::console::Arguments& p_arguments);
    void createSingleCsvTask(const std::string& p_fileName);
    void createCsvTasksFromDirectory(const std::string& p_directoryPath);
    std::shared_ptr<display::IDisplay> getDisplay() const;
};

} // namespace task
} // namespace csvvalidator
