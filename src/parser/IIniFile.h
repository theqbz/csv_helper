/**
 * CSV HELPER by QBZ
 *
 * @file  IIniFile.h
 * @brief Interface fefinition of IniFile class of csvhelper
 */

#pragma once

#include "../utils/datastructure/IniData.h"

namespace csvhelper{
namespace parser{

class IIniFile
{
public:
    IIniFile() = default;
    virtual ~IIniFile();
    virtual inline const csvhelper::utils::ini::File get() const = 0;
};

}
}
