///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  ISettings.h
/// @brief Interface declaration of the Settings class
///

#pragma once

#include <string>

namespace csvvalidator {
namespace utils {

///
/// @brief Interface for Settings class
///
class ISettings
{
public:
    enum class EmptyLines
    {
        Skip,  ///< Skip empty lines in result
        Error, ///< Display enmpty lines as error in result
        Keep  ///< Display empty lines as empty lines in result
    };

    enum class LabelPosition
    {
        Top,
        Inline
    };

    enum class DiffDetectMode
    {
        Off,
        Auto,
        Above,
        Below
    };

    ISettings()          = default;
    virtual ~ISettings() = default;

    virtual inline void delimiter(const unsigned char p_delimiter)     = 0;
    virtual inline const unsigned char delimiter() const               = 0;
    virtual inline void linesAroundErrors(const size_t p_value)        = 0;
    virtual inline const size_t linesAroundErrors() const              = 0;
    virtual inline void labelPosition(const LabelPosition p_position)  = 0;
    virtual inline const LabelPosition labelPosition() const           = 0;
    virtual inline void emptyFields(const unsigned char p_placeholder) = 0;
    virtual inline const unsigned char emptyFields() const             = 0;
    virtual inline void emptyLines(const EmptyLines& p_placeholder)    = 0;
    virtual inline const EmptyLines emptyLines() const                 = 0;
    virtual inline void tableOutput(const bool p_value)                = 0;
    virtual inline const bool tableOutput() const                      = 0;
    virtual inline void diffDetectMode(const DiffDetectMode p_mode)    = 0;
    virtual inline const DiffDetectMode diffDetectMode() const         = 0;
};

} // namespace utils
} // namespace csvvalidator
