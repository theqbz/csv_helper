///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Settings.h
/// @brief Declaration of the settings class
///
/// OPTION NAME     OPTION DETAILS
/// -----------     --------------
/// delimiter       delimiter between fields in a csv file
///
/// emptyLines      [ error | leave | skip ]
///                 defines what to do with empty lines
///
/// diff            [ off | auto | above | below ]
///
/// emptyFields     placeholder for empty values
///                 (0: skip empty values)
///
/// errorLines      the number of lines around errors
///                 (0: show all lines)
///
/// label           [ top | inline ]
///                 defines where to print the labels
///                 (This option and TalbeOutput are mutually exclusive: if
///                 "table" enabled, inactivates this setting.)
///
/// table           show output in a table
///                 (This is mutually exclusive with LabelPosiotion: if this
///                 option is enabled, it inactivates "label" setting.)
///
/// errorLevel      [ all | warning | error ]
///                 defines the verbosity of the error log
///

#pragma once

#include "../data/SettingData.h"
#include "ISettings.h"

#include <filesystem>

namespace csvvalidator {
namespace utils {

///
/// @brief Store program settings in runtime
///
class Settings : public ISettings
{
public:
    Settings() = delete;

    ///
    /// Contructor for Settings class.
    ///
    /// Store the console arguments and the content of the .ini file, and sets
    /// all options to default state.
    ///
    /// @param - consoleArguments : the ordered content of console args
    /// @param - iniFile          : the ordered content of records from .ini file
    ///
    Settings(const data::SettingData& p_consoleArguments,
             const data::SettingData& p_iniFile) :
        m_consoleArguments(p_consoleArguments),
        m_iniFile(p_iniFile)
    {
        init();
    }

    Settings(const Settings&) = delete;
    Settings(Settings&&)      = delete;

    void init();

    inline void iniFileLocation(const std::filesystem::path p_path) { m_iniFileLocation = p_path; }
    inline const std::filesystem::path iniFileLocation() const { return m_iniFileLocation; }
    inline void delimiter(const unsigned char p_delimiter) { m_delimiter = p_delimiter; }
    inline const unsigned char delimiter() const { return m_delimiter; }
    inline void emptyLines(const EmptyLines& p_placeholder) { m_emptyLines = p_placeholder; }
    inline const EmptyLines emptyLines() const { return m_emptyLines; }
    inline void diffDetectMode(const DiffDetectMode p_mode) { m_diff = p_mode; }
    inline const DiffDetectMode diffDetectMode() const { return m_diff; }
    inline void emptyFields(const unsigned char p_placeholder) { m_emptyFields = p_placeholder; }
    inline const unsigned char emptyFields() const { return m_emptyFields; }
    inline void linesAroundErrors(const size_t p_value) { m_linesAroundErrors = p_value; }
    inline const size_t linesAroundErrors() const { return m_linesAroundErrors; }
    inline void labelPosition(const LabelPosition p_label) { m_labels = p_label; }
    inline const LabelPosition labelPosition() const { return m_labels; }
    inline void tableOutput(const bool p_value) { m_tableOutput = p_value; }
    inline const bool tableOutput() const { return m_tableOutput; }
    inline void errorLevel(const ErrorLevel p_errorLevel) { m_errorLevel = p_errorLevel; }
    inline const ErrorLevel errorLevel() const { return m_errorLevel; }

private:
    std::filesystem::path m_iniFileLocation;
    data::SettingData m_consoleArguments;
    data::SettingData m_iniFile;
    unsigned char m_delimiter;
    EmptyLines m_emptyLines;
    DiffDetectMode m_diff;
    unsigned char m_emptyFields;
    size_t m_linesAroundErrors;
    LabelPosition m_labels;
    bool m_tableOutput;
    ErrorLevel m_errorLevel;

    void storeSettings(const data::SettingData& p_tasks);
};

} // namespace utils
} // namespace csvvalidator
