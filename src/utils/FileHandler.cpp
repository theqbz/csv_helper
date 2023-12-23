///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  FileHandler.cpp
/// @brief Function definitions of the FileHandler class
///

#include "FileHandler.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace csvvalidator {
namespace utils {

FileHandler::FileHandler(const std::string& p_fileName) noexcept :
    m_fileName(p_fileName),
    m_file(p_fileName)
{
    checkFile();
}

FileHandler::FileHandler(const std::filesystem::path& p_path) noexcept :
    m_fileName(p_path.string()),
    m_file(p_path)
{
    checkFile();
}

FileHandler::~FileHandler()
{
    m_file.close();
    std::cout << "File closed.\n";
}

void FileHandler::checkFile() const
{
    if (!m_file.good()) {
        std::cout << "Failed to open file: " << m_fileName << "\n";
    }
}

} // namespace utils
} // namespace csvvalidator
