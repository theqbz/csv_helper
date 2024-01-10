///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  IDisplay.h
/// @brief Interface declaration for Display classes
///

#pragma once

#include "../data/Report.h"

namespace csvvalidator {
namespace display {

///
/// @brief Interface for display classes
///
class IDisplay
{
public:
    IDisplay()          = default;
    virtual ~IDisplay() = default;

    virtual void render(const data::display::Report& p_report) const = 0;
};

} // namespace display
} // namespace csvvalidator
