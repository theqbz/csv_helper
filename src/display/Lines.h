///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Lines.h
/// @brief Declaration of display::Lines class.
///
#pragma once

#include "../data/Report.h"
#include "../utils/ISettings.h"
#include "IDisplay.h"

namespace csvvalidator {
namespace display {

///
/// @brief Display the data::display::Report about a *csv* file.
///
class Lines : public IDisplay
{
public:
    ///
    /// @brief Constructor for Lines class.
    ///
    /// @param[in] p_settings (required) : a reference to Settings class
    ///
    explicit Lines(const utils::ISettings& p_settings);

    ///
    /// @brief Renders the given Report to the display.
    ///
    /// @param[in] p_report : a reference to a Report object
    /// @return (void)
    ///
    void render(const data::display::Report& p_report) const final;

private:
    const utils::ISettings& m_settings;
};

} // namespace display
} // namespace csvvalidator
