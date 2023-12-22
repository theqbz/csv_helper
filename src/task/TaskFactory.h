///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  TaskFactory.h
/// @brief Declaration of TaskFactory class
///

#pragma once

#include "../csv/IAnalyzer.h"
#include "../csv/IParser.h"
#include "../data/ConsoleArguments.h"
#include "../display/IDisplay.h"
#include "../display/IReporter.h"
#include "../utils/IFileHandler.h"
#include "../utils/ISettings.h"
#include "ITask.h"

#include <queue>

namespace csvvalidator {
namespace task {

class TaskFactory
{
public:
    TaskFactory() = delete;
    TaskFactory(const TaskFactory&) = delete;
    TaskFactory(const data::console::Arguments& p_arguments);

    void init(const data::console::Arguments& p_arguments);
    void execute();

private:
    std::queue<task::ITask> m_tasks;
};

} // namespace task
} // namespace csvvalidator
