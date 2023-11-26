/**
 * CSV HELPER by QBZ
 *
 * @file  IniFile.h
 * @brief Definition of .ini file parser class of csvhelper
 */

#pragma once

#include "../utils/IFileHandler.h"
#include "../utils/datastructure/IniData.h"
#include "IIniFile.h"

namespace csvhelper {
namespace parser {

extern const csvhelper::utils::ini::File read(std::fstream& p_iniFile);

class IniFile : public IIniFile
{
public:
    IniFile(utils::IFileHandler& p_file) :
        m_iniFile(read(p_file.get()))
    {
    }
    inline const csvhelper::utils::ini::File get() const final { return m_iniFile; }

private:
    csvhelper::utils::ini::File m_iniFile;
};

} // namespace parser
} // namespace csvhelper
