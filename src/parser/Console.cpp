///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  Console.cpp
/// @brief Functions for console parser
///

#include "Console.h"
#include "../data/ConsoleArguments.h"
#include "../utils/Utility.h"

#include <iostream>
#include <set>
#include <string>
#include <vector>

namespace csvvalidator {
namespace parser {

typedef std::vector<std::string> StrVec;

static inline bool hasKey(const data::console::Parameter& p_parameter);
static inline bool isKey(const std::string& p_text);
static inline void removeDashes(std::string* p_parameterKey);

const data::console::Arguments Console::parse(const int p_argc,
                                              const char* const p_argv[])
{
    StrVec rawData = Console::convert(p_argc, p_argv);
    data::console::Arguments arguments {};
    arguments.m_command    = getCommand(&rawData);
    arguments.m_parameters = Console::createParameters(rawData);
    return arguments;
}

const data::console::Parameters Console::createParameters(const StrVec& p_rawData)
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
            std::cout << "An error with parameter: " << parameter.first << ", " << parameter.second << "\n";
        }
    }
    return parameters;
}

const std::string Console::getCommand(StrVec* p_rawData)
{
    if (!p_rawData) {
        std::cout << "Program logic error: nullptr as rawData @ getCommand\n";
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

const StrVec Console::convert(const int p_argc, const char* const p_argv[])
{
    StrVec rawData;
    for (int i = 1; i < p_argc; ++i) {
        rawData.emplace_back(p_argv[i]);
    }
    return rawData;
}

static inline bool hasKey(const data::console::Parameter& p_parameter)
{
    return !p_parameter.first.empty();
}

static inline bool isKey(const std::string& p_text)
{
    return !p_text.empty() && *p_text.begin() == utils::KEY_MARKER;
}

void removeDashes(std::string* p_parameterKey)
{
    if (!p_parameterKey) {
        std::cout << "Program logic error: nullptr as p_parameter @ removeDashes\n";
        return;
    }
    std::string& key = *p_parameterKey;
    key.erase(key.begin(), key.begin() + key.find_first_not_of(utils::KEY_MARKER));
}

} // namespace parser
} // namespace csvvalidator
