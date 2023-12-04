///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  FileHandler.cpp
/// @brief Function definitions of the FileHandler class
///

#include "FileHandler.h"

#include <fstream>
#include <iostream>
#include <string>

namespace csvhelper {
namespace utils {

FileHandler::FileHandler(const std::string& p_fileName) :
    m_fileName(p_fileName),
    m_file(p_fileName)
{
    if (!m_file.good()) {
        std::cout << "Failed to open file: " << p_fileName << "\n";
    } else {
        std::cout << "File opened successfull: " << p_fileName << "\n";
    }
}

FileHandler::~FileHandler()
{
    if (m_file.good()) {
        m_file.close();
        std::cout << "File closed.\n";
    }
}

} // namespace utils
} // namespace csvhelper
