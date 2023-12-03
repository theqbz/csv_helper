///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Settings.h
/// @brief Declaration of the settings class
///

#pragma once

#include "ISettings.h"
#include "parser/data/ConsoleArguments.h"
#include "parser/data/IniFile.h"
#include "parser/data/SettingData.h"

namespace csvhelper {
namespace utils {

///
/// @brief Store program settings in runtime
///
/// OPTION NAME         OPTION DETAILS
/// -----------         --------------
/// delimiter           delimiter between fields in .csv file
/// emptyLines          placeholder for empty lines
///                     (0: skip empty lines / 1: show empty lines as error)
/// diff                off / auto / above / below
/// emptyFields         placeholder for empty values
///                     (0: skip empty values)
/// linesAroundErrors   sohw number of lines around errors
///                     (0: show all lines)
/// labelPosition       top / inline
///                     (This option and TalbeOutput are mutually exclusive:
///                     if TableOutput enabled, inactivates this setting.)
/// tableOutput         show output in a table
///                     (This is mutually exclusive with LabelPosiotion: it
///                     inactivates LabelPosition if enabled.)
///
class Settings : public ISettings
{
public:
    ///
    /// Contructor for Settings class.
    ///
    /// Store the console arguments and the content of the .ini file, and sets
    /// all options to default state.
    ///
    /// @param - consoleArguments : the ordered content of console args
    /// @param - iniFile          : the ordered content of records from .ini file
    ///
    Settings(const parser::data::SettingData& p_consoleArguments,
             const parser::data::SettingData& p_iniFile) :
        m_consoleArguments(p_consoleArguments),
        m_iniFile(p_iniFile),
        m_delimiter(';'),
        m_emptyLines(0),
        m_diff(DiffDetectMode::Off),
        m_emptyFields('.'),
        m_linesAroundErrors(0),
        m_labelPosition(LabelPosition::Top),
        m_tableOutput(false)
    {
    }

    Settings(const Settings&) = delete;
    Settings(Settings&&)      = delete;

    void init();

    inline void delimiter(const unsigned char p_delimiter) { m_delimiter = p_delimiter; }
    inline unsigned char delimiter() const { return m_delimiter; }
    inline void emptyLines(const unsigned char p_placeholder) { m_emptyLines = p_placeholder; }
    inline unsigned char emptyLines() const { return m_emptyLines; }
    inline void diffDetectMode(const DiffDetectMode p_mode) { m_diff = p_mode; }
    inline DiffDetectMode diffDetectMode() const { return m_diff; }
    inline void emptyFields(const unsigned char p_placeholder) { m_emptyFields = p_placeholder; }
    inline unsigned char emptyFields() const { return m_emptyFields; }
    inline void linesAroundErrors(const unsigned int p_value) { m_linesAroundErrors = p_value; }
    inline unsigned int linesAroundErrors() const { return m_linesAroundErrors; }
    inline void labelPosition(const LabelPosition p_position) { m_labelPosition = p_position; }
    inline LabelPosition labelPosition() const { return m_labelPosition; }
    inline void tableOutput(const bool p_value) { m_tableOutput = p_value; }
    inline bool tableOutput() const { return m_tableOutput; }

private:
    parser::data::SettingData m_consoleArguments;
    parser::data::SettingData m_iniFile;
    unsigned char m_delimiter;
    unsigned char m_emptyLines;
    DiffDetectMode m_diff;
    unsigned char m_emptyFields;
    unsigned int m_linesAroundErrors;
    LabelPosition m_labelPosition;
    bool m_tableOutput;

    void storeSettings(const parser::data::SettingData& p_tasks);
};

} // namespace utils
} // namespace csvhelper
