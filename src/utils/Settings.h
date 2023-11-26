/******************************************************************************
 * CSV HELPER by QBZ
 ******************************************************************************
 * Settings
 * Stores program settings
 *****************************************************************************/

#pragma once

#include "../parser/IConsole.h"
#include "../parser/IIniFile.h"
#include "ISettings.h"

namespace csvhelper {
namespace settings {

typedef std::map<std::string, std::string> Tasks;

class Settings : public ISettings
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

    Settings(parser::IConsole& p_consoleParser,
             parser::IIniFile& p_iniFileParser) :
        m_consoleParser(p_consoleParser),
        m_iniFileParser(p_iniFileParser),
        m_linesAroundErrors(0),
        m_labelPosition(LabelPosition::Top),
        m_emptyFields('.'),
        m_emptyLines(0),
        m_tableOutput(false),
        m_diff(DiffDetectMode::Off)
    {
    }
    Settings(const Settings&) = delete;
    Settings(Settings&&)      = default;

    void init();

    inline void linesAroundErrors(const unsigned int p_value) { m_linesAroundErrors = p_value; }
    inline unsigned int linesAroundErrors() const { return m_linesAroundErrors; }
    inline void labelPosition(const LabelPosition p_position) { m_labelPosition = p_position; }
    inline LabelPosition labelPosition() const { return m_labelPosition; }
    inline void emptyFields(const unsigned char p_placeholder) { m_emptyFields = p_placeholder; }
    inline unsigned char emptyFields() const { return m_emptyFields; }
    inline void emptyLines(const unsigned char p_placeholder) { m_emptyLines = p_placeholder; }
    inline unsigned char emptyLines() const { return m_emptyLines; }
    inline void tableOutput(const bool p_value) { m_tableOutput = p_value; }
    inline bool tableOutput() const { return m_tableOutput; }
    inline void diffDetectMode(const DiffDetectMode p_mode) { m_diff = p_mode; }
    inline DiffDetectMode diffDetectMode() const { return m_diff; }

private:
    parser::IConsole& m_consoleParser;
    parser::IIniFile& m_iniFileParser;
    unsigned int m_linesAroundErrors; // sohw number of lines around errors (0: show all lines)
    LabelPosition m_labelPosition;    // top / inline (This option and TalbeOutput are mutually exclusive: if TableOutput is true, it inactivates this setting.)
    unsigned char m_emptyFields;      // placeholder for empty values (0: skip empty values)
    unsigned char m_emptyLines;       // placeholder for empty lines (0: skip empty lines / 1: show as error empty lines)
    bool m_tableOutput;               // show output in a table (This option and LabelPosiotion are mutually exclusive: if this is true, it inactivates LabelPosition setting.)
    DiffDetectMode m_diff;            // off / auto / above / below

    void storeSettings(const Tasks& p_tasks);
};

} // namespace settings
} // namespace csvhelper
