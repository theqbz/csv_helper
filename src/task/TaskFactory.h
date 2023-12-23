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

    TaskFactory(const data::console::Arguments& p_arguments,
                const utils::ISettings& p_settings) :
        m_settings(p_settings)
    {
        init(p_arguments);
    }

    void init(const data::console::Arguments& p_arguments);
    bool runTasks();

private:
    const utils::ISettings& m_settings;
    std::queue<std::shared_ptr<task::ITask>> m_tasks;

    void searchDirectory(const std::string& p_directoryPath);
    std::shared_ptr<display::IDisplay> getDisplay() const;
};

} // namespace task
} // namespace csvvalidator
