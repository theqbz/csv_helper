/******************************************************************************
 * CSV HELPER by QBZ
 ******************************************************************************
 * IConsole
 * Interface definition of Console
 *****************************************************************************/

#pragma once

#include "../utils/datastructure/Arguments.h"

namespace csvhelper {
namespace parser {

typedef csvhelper::utils::console::Arguments Arguments;


class IConsole
{
public:
    IConsole()          = default;
    virtual ~IConsole() = default;

    virtual inline const Arguments get() const = 0;
};

} // namespace parser
} // namespace csvhelper
