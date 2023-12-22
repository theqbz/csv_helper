///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  CsvTask.h
/// @brief Declaration of CsvTask class
///

#pragma once

namespace csvvalidator {
namespace task {

class ITask
{
public:
    ITask()          = default;
    virtual ~ITask() = default;

    virtual bool run() = 0;
};

} // namespace task
} // namespace csvvalidator