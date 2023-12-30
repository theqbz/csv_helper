///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  ConfigTask.h
/// @brief Declaration of ConfigTask class
///

#pragma once

#include "../data/SettingData.h"
#include "../utils/Utility.h"
#include "ITask.h"

namespace csvvalidator {
namespace task {

class ConfigTask : public ITask
{
public:
    ConfigTask(const data::SettingData& p_arguments) :
        m_arguments(p_arguments)
    {
        LOG("ConfigTask created\n", utils::verbose);
    }

    bool run() final;

private:
    data::SettingData m_arguments;
};

} // namespace task
} // namespace csvvalidator
