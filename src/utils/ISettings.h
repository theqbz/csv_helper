///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  ISettings.h
/// @brief Interface declaration of the Settings class
///

#pragma once

namespace csvhelper {
namespace settings {

///
/// @brief Interface for Settings class
///
class ISettings
{
public:
    ISettings()          = default;
    virtual ~ISettings() = default;
};

} // namespace settings
} // namespace csvhelper
