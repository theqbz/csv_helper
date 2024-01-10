///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  ITask.h
/// @brief Interface declaration for task classes
///

#pragma once

namespace csvvalidator {
namespace task {

///
/// @brief Interface for task classes.
/// 
class ITask
{
public:
    ITask()          = default;
    virtual ~ITask() = default;

    virtual bool run() = 0;
};

} // namespace task
} // namespace csvvalidator