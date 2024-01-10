///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Console.cpp
/// @brief Definition of the parser::Console class.
///
#include "Console.h"

#include "../data/ConsoleArguments.h"
#include "../utils/Utility.h"

#include <string>
#include <vector>

namespace csvvalidator {
namespace parser {

typedef std::vector<std::string> StrVec;

const StrVec convert(const int p_argc, const char* const p_argv[]);
void extractVerbosity(StrVec* p_rawData);
const std::string extractCommand(StrVec* p_rawData);
const data::console::Parameters createParameters(const StrVec& p_rawData);
inline bool hasKey(const data::console::Parameter& p_parameter);
inline bool isKey(const std::string& p_text);
inline void removeDashes(std::string* p_parameterKey);

const data::console::Arguments Console::parse(const int p_argc,
                                              const char* const p_argv[])
{
    LOG("Parsing console arguments...\n", utils::verbose);
    StrVec rawData = convert(p_argc, p_argv);
    extractVerbosity(&rawData);
    data::console::Arguments arguments {};
    arguments.m_command    = extractCommand(&rawData);
    arguments.m_parameters = createParameters(rawData);
    return arguments;
}

const data::console::Parameters createParameters(const StrVec& p_rawData)
{
    data::console::Parameters parameters {};
    StrVec::const_iterator it = p_rawData.begin();
    while (it < p_rawData.end()) {
        data::console::Parameter parameter {};
        bool parameterDone = false;
        while (it < p_rawData.end() && !parameterDone) {
            if (!hasKey(parameter)) {
                parameter.first = *it;
                if (!isKey(*it)) {
                    parameterDone = true;
                }
                ++it;
            } else {
                if (!isKey(*it)) {
                    parameter.second = *it;
                    ++it;
                }
                parameterDone = true;
            }
        }
        removeDashes(&parameter.first);
        const auto [iterator, success] = parameters.insert(parameter);
        if (!success) {
            LOG("An error with console argument: " + parameter.first + ", " + parameter.second + "\n", true);
        }
    }
    return parameters;
}

const std::string extractCommand(StrVec* p_rawData)
{
    if (!p_rawData) {
        LOG("Program logic error: nullptr as rawData @ extractCommand\n", true);
        return {};
    }
    if (p_rawData->empty()) {
        return {};
    }
    std::string command {};
    command = p_rawData->front();
    p_rawData->erase(p_rawData->begin());
    return command;
}

const StrVec convert(const int p_argc, const char* const p_argv[])
{
    StrVec rawData;
    for (int i = 1; i < p_argc; ++i) {
        rawData.emplace_back(p_argv[i]);
    }
    return rawData;
}

inline bool hasKey(const data::console::Parameter& p_parameter)
{
    return !p_parameter.first.empty();
}

inline bool isKey(const std::string& p_text)
{
    return !p_text.empty() && *p_text.begin() == utils::CLI_KEY_MARKER;
}

void removeDashes(std::string* p_parameterKey)
{
    if (!p_parameterKey) {
        LOG("Program logic error: nullptr as p_parameter @ removeDashes\n", true);
        return;
    }
    std::string& key = *p_parameterKey;
    key.erase(key.begin(), key.begin() + key.find_first_not_of(utils::CLI_KEY_MARKER));
}

void extractVerbosity(StrVec* p_rawData)
{
    if (!p_rawData) {
        LOG("Program logic error: nullptr as rawData @ extractVerbosity()\n", true);
        return;
    }
    if (p_rawData->empty()) {
        return;
    }
    for (StrVec::iterator it = p_rawData->begin(); it != p_rawData->end(); ++it) {
        if (utils::CLI_VERBOSE_COMMANDS.contains(*it)) {
            utils::verbose = true;
            p_rawData->erase(it);
            LOG("Verbose mode\n", true);
            return;
        }
    }
}

} // namespace parser
} // namespace csvvalidator
