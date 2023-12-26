///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  CsvTask.h
/// @brief Declaration of CsvTask class
///

#pragma once

#include "../display/IDisplay.h"
#include "../utils/ISettings.h"
#include "ITask.h"

#include <filesystem>
#include <memory>
#include <string>

namespace csvvalidator {
namespace task {

///
/// @brief A Task to parse, analyze and present a csv file
///
class CsvTask : public ITask
{
public:
    CsvTask() = delete;

    ///
    /// @brief Constructor for CsvTask.
    /// Stores the state of the class and check if the display is not exis
    ///
    /// @param[in] - path     : the path to the file to be parse as string
    /// @param[in] - settings : a reference to the program Settings handler class
    /// @param[in] - display  : a pointer to the result display
    ///
    explicit CsvTask(const std::string& p_path,
                     const utils::ISettings& p_settings,
                     std::shared_ptr<display::IDisplay> p_display) noexcept;

    ///
    /// @brief Constructor for CsvTask.
    /// Stores the state of the class and check if the display is not exis
    ///
    /// @param[in] - path     : the path to the file to be parse as fs::path
    /// @param[in] - settings : a reference to the program Settings handler class
    /// @param[in] - display  : a pointer to the result display
    ///
    explicit CsvTask(const std::filesystem::path& p_path,
                     const utils::ISettings& p_settings,
                     std::shared_ptr<display::IDisplay> p_display) noexcept;

    ///
    /// Execute the task
    ///
    /// @param (void)
    /// @return true, if the execution was successfull
    ///
    bool run() final;

private:
    const utils::ISettings& m_settings;
    const std::filesystem::path m_file;
    std::shared_ptr<display::IDisplay> m_display;
};

} // namespace task
} // namespace csvvalidator
