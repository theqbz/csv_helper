///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  FileHandler.cpp
/// @brief Definition of the utils::fileHandler class
///
#include "FileHandler.h"

#include "Utility.h"

#include <filesystem>
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
    m_fileName(p_path.filename().string()),
    m_file(p_path)
{
    checkFile();
}

FileHandler::~FileHandler()
{
    m_file.close();
    LOG(m_fileName + " file closed\n", utils::verbose);
}

void FileHandler::checkFile() const
{
    if (!m_file.good()) {
        LOG("Failed to open file: " + m_fileName + "\n", true);
        return;
    }
    LOG(m_fileName + " file opened successfull\n", utils::verbose);
}

} // namespace utils
} // namespace csvvalidator
