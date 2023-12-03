///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  ISettings.h
/// @brief Interface declaration of the Settings class
///

#pragma once

namespace csvhelper {
namespace utils {

///
/// @brief Interface for Settings class
///
class ISettings
{
public:
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
    virtual inline unsigned char delimiter() const                     = 0;
    virtual inline void linesAroundErrors(const unsigned int p_value)  = 0;
    virtual inline unsigned int linesAroundErrors() const              = 0;
    virtual inline void labelPosition(const LabelPosition p_position)  = 0;
    virtual inline LabelPosition labelPosition() const                 = 0;
    virtual inline void emptyFields(const unsigned char p_placeholder) = 0;
    virtual inline unsigned char emptyFields() const                   = 0;
    virtual inline void emptyLines(const unsigned char p_placeholder)  = 0;
    virtual inline unsigned char emptyLines() const                    = 0;
    virtual inline void tableOutput(const bool p_value)                = 0;
    virtual inline bool tableOutput() const                            = 0;
    virtual inline void diffDetectMode(const DiffDetectMode p_mode)    = 0;
    virtual inline DiffDetectMode diffDetectMode() const               = 0;
};

} // namespace utils
} // namespace csvhelper
