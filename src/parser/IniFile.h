///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  IniFile.h
/// @brief Definition of parsed .ini file handler class
///

#pragma once

#include "../utils/IFileHandler.h"
#include "../utils/datastructure/IniData.h"
#include "IIniFile.h"

namespace csvhelper {
namespace parser {

typedef csvhelper::utils::ini::File File;

extern const File read(std::fstream& p_iniFile);

///
/// @brief Store a parsed data of a .ini file
///
class IniFile : public IIniFile
{
public:
    IniFile(utils::IFileHandler& p_file) :
        m_iniFile(read(p_file.get()))
    {
    }
    
    ///
    /// Get the data, stored in a .ini file
    ///
    /// @param (void)
    /// @return a ini::File datastructure, contains ini records
    ///
    inline const File get() const final { return m_iniFile; }

private:
    File m_iniFile;
};

} // namespace parser
} // namespace csvhelper
