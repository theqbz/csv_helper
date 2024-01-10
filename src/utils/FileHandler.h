///
/// CSV HELPER by QBZ
/// ----------------------------------------------------------------------------
/// @file  FileHandler.h
/// @brief Declaration of the utils::fileHandler class
///

#pragma once

#include "IFileHandler.h"

#include <fstream>
#include <string>

namespace csvvalidator {
namespace utils {

///
/// @brief FileHandler class.
/// Opens, holds its stream and and manage the closing process to a given file.
///
class FileHandler final : public IFileHandler
{
public:
    ///
    /// Constructor for FileHandler.
    /// Opens the file and check if this process was succesfull.
    ///
    /// @param[in] fileName (required) : the path to file and filename as string
    ///
    explicit FileHandler(const std::string& p_fileName) noexcept;

    ///
    /// Constructor for FileHandler.
    /// Opens the file and check if this process was succesfull.
    ///
    /// @param[in] path (required) : the path to file as filesystem::path
    ///
    explicit FileHandler(const std::filesystem::path& p_path) noexcept;

    ///
    /// Destructor for FileHandler.
    /// Close the file what the actual FileHandler object was holded.
    ///
    ~FileHandler() final;

    ////
    /// Get a reference to the file.
    ///
    /// @param (void)
    /// @return a reference to the file
    ///
    inline std::fstream& get() final { return m_file; }

    ///
    /// Get the name of the file
    ///
    /// @param (void)
    /// @return the name of the file
    ///
    inline const std::string fileName() const final { return m_fileName; }

private:
    const std::string m_fileName;
    std::fstream m_file;

    void checkFile() const;
};

} // namespace utils
} // namespace csvvalidator
