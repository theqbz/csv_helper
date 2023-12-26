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

class ConfigTask : public ITask
{
public:
    ConfigTask(const data::SettingData& p_settings) :
        m_settings(p_settings)
    {
    }

    bool run() final;

private:
    const data::SettingData m_settings;
};

} // namespace task
} // namespace csvvalidator
