/**
 * CSV HELPER by QBZ
 *
 * @file  IFileHandler.h
 * @brief Interface definition of the file handler class for csvhelper
 */

#pragma once

#include <fstream>

namespace csvhelper::utils {

class IFileHandler
{
public:
    IFileHandler()          = default;
    virtual ~IFileHandler() = default;

    /**
     * Get a reference to the file.
     *
     * @param (void)
     * @return a reference to the file
     */
    virtual std::fstream& get() = 0;
};

} // namespace csvhelper::utils
