#include <functional>
#include <map>
#include <string>
#include <utility>

///
/// The final storage for settings.
/// The program use this class to get the actual settings after initialization
///
class Settings
{ };


// Settings-transfer storage example
// To store the setting data and transfer it between objects
{
    ///
    /// Container for setting data to set settings
    /// Consists of a < key, value > pair
    /// Key: the name of setting
    /// Value: the value of the setting
    ///
    struct SettingData : public std::map<std::string, std::string>
    { };

    // examples:

    const SettingData burnedInDefault { ("emptyLines", "0"),
                                        ("emptyFields", "0"),
                                        ("label", "inline") };

    const SettingData fromIniFile { /* ... */ };

    const SettingData fromConsole { /* ... */ };
}

//

struct IOption
{ };

struct OptionData : public std::map<std::string, IOption>
{ };

enum class LabelPosition
{
    Top,
    Inline
};

struct LabelPosOption : public IOption
{
    explicit LabelPosOption(LabelPosition p_opt) :
        m_opt(p_opt) { }
    LabelPosition m_opt;
};

const LabelPosOption label_top { LabelPosition::Top };
const LabelPosOption label_inline { LabelPosition::Inline };

const OptionData label_position { { "top", label_top },
                                  { "inline", label_inline } };

///
/// sets
struct SettingSetter
{
    inline bool call(Settings& p_settings, const std::string& p_key) { m_setterFunction(p_settings, p_key, m_optionData); }
    std::function<bool(Settings&, const std::string&, const OptionData&)> m_setterFunction;
    OptionData m_optionData;
};

///
/// Container for setting setter.
/// Consists of a < key, SettingSetter > pair
/// Key: the name of setting
/// Value: SettingSetter class
/// This will call the SettingSetter's m_setterFunction, with the key and the OptionData
///
struct Setter : public std::map<std::string, SettingSetter>
{ };
