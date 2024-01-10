///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  HelpTask.h
/// @brief Declaration of HelpTask class
///
#pragma once

#include "../utils/Utility.h"
#include "ITask.h"

#include <string>

namespace csvvalidator {
namespace task {

///
/// @brief A task to print help.
///
class HelpTask : public ITask
{
public:
    ///
    /// @brief Constructor for HelpTask.
    /// Set the state with help-request, which determines what type of help
    /// text requested to display.
    ///
    /// @param[in] - p_helpRequest  : the help request
    ///
    explicit HelpTask(const std::string& p_helpRequest = "") noexcept :
        m_request(p_helpRequest)
    {
        LOG("HelpTask created\n", utils::verbose);
    }

    ///
    /// @brief Execute the task
    ///
    /// @param (void)
    /// @return true, if the execution was successfull
    ///
    bool run() final;

private:
    std::string m_request;
};

} // namespace task
} // namespace csvvalidator
