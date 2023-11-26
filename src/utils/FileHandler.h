/**
 * CSV HELPER by QBZ
 *
 * @file  FileHandler.h
 * @brief Definition of the file handler class for csvhelper
 */

#pragma once

#include "IFileHandler.h"

#include <fstream>
#include <string>

namespace csvhelper::utils {

/**
 * FileHandler class for csvhelper.
 * Opens, holds its stream and and manage the closing process to a given file.
 */
class FileHandler final : public IFileHandler
{
public:
    /**
     * Constructor for FileHandler.
     * Opens the file and check if this process was succesfull.
     *
     * @param[in] p_fileName (required) : the path to file and filename
     */
    explicit FileHandler(const std::string& p_fileName);

    /**
     * Destructor for FileHandler.
     * Close the file what the actual FileHandler object was holded.
     */
    ~FileHandler() final;

    /**
     * Get a reference to the file.
     *
     * @param (void)
     * @return a reference to the file
     */
    std::fstream& get() final { return m_file; }

private:
    std::fstream m_file;
};

} // namespace csvhelper::utils
