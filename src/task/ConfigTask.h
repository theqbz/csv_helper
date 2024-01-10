///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  ConfigTask.h
/// @brief Declaration of ConfigTask class
///
#pragma once

#include "../data/SettingData.h"
#include "ITask.h"

namespace csvvalidator {
namespace task {

///
/// @brief A task to store new settings.
///
class ConfigTask : public ITask
{
public:
    ///
    /// @brief Constructor for ConfigTask.
    /// Set the state with arguments.
    ///
    /// @param[in] - p_arguments  : the settings to be stored
    ///
    explicit ConfigTask(const data::SettingData& p_arguments) noexcept;

    ///
    /// @brief Execute the task
    ///
    /// @param (void)
    /// @return true, if the execution was successfull
    ///
    bool run() final;

private:
    data::SettingData m_arguments;
};

} // namespace task
} // namespace csvvalidator
