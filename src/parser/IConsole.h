///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  IConsole.h
/// @brief Interface declaration of the console argument parser class for
///        csvhelper
///

#pragma once

#include "../utils/datastructure/Arguments.h"

namespace csvhelper {
namespace parser {

typedef csvhelper::utils::console::Arguments Arguments;

///
/// @brief Interface for console argument parser
class IConsole
{
public:
    IConsole()          = default;
    virtual ~IConsole() = default;

    ///
    /// Get the stored console arguments
    ///
    /// @param (void)
    /// @return console::Arguments datastructure
    ///
    virtual inline const Arguments get() const = 0;
};

} // namespace parser
} // namespace csvhelper
