///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  ISettings.h
/// @brief Interface declaration of the Settings class
///
#pragma once

namespace csvvalidator {
namespace utils {

///
/// @brief Interface for Settings class
///
class ISettings
{
public:
    ///
    /// @brief Defines how to handle the empty lines in files
    ///
    enum class EmptyLines
    {
        Skip,  ///< Skip empty lines in result
        Error, ///< Display enmpty lines as error in result
        Keep   ///< Display empty lines as empty lines in result
    };

    ///
    /// @brief Defines where to print the labels
    ///
    enum class LabelPosition
    {
        Top,   ///< Print labels only on top of the file
        Inline ///< Print labels in fields
    };

    ///
    /// @brief Defines how detailed the error log should be
    ///
    enum class ErrorLevel
    {
        All,  ///< Prints errors and warnings
        Error ///< Prints only errors
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

    virtual inline void delimiter(const unsigned char)         = 0;
    virtual inline const unsigned char delimiter() const       = 0;
    virtual inline void linesAroundErrors(const size_t)        = 0;
    virtual inline const size_t linesAroundErrors() const      = 0;
    virtual inline void labelPosition(const LabelPosition)     = 0;
    virtual inline const LabelPosition labelPosition() const   = 0;
    virtual inline void emptyFields(const unsigned char)       = 0;
    virtual inline const unsigned char emptyFields() const     = 0;
    virtual inline void emptyLines(const EmptyLines&)          = 0;
    virtual inline const EmptyLines emptyLines() const         = 0;
    virtual inline void tableOutput(const bool)                = 0;
    virtual inline const bool tableOutput() const              = 0;
    virtual inline void diffDetectMode(const DiffDetectMode)   = 0;
    virtual inline const DiffDetectMode diffDetectMode() const = 0;
    virtual inline void errorLevel(const ErrorLevel)           = 0;
    virtual inline const ErrorLevel errorLevel() const         = 0;
};

} // namespace utils
} // namespace csvvalidator
