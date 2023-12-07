///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  IDisplay.h
/// @brief Interface definition for Display classes
///

#pragma once

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

    virtual void render(/* const Report& p_report */) = 0;
};

} // namespace display
} // namespace csvvalidator
