/**
 * CSV HELPER by QBZ
 *
 * @file  Arguments.h
 * @brief Definition of the datastructure of command line arguments for csvhelper
 */

#pragma once

#include <map>
#include <string>
#include <utility>

namespace csvhelper::utils {
namespace console {

/**
 * A console argument type contains a pair of < key, value >
 */
typedef std::pair<std::string, std::string> Argument;

/**
 * Container for the argument list from commandline.
 * The Argument consists a pair of < key, value >
 */
struct Arguments : public std::map<std::string, std::string>
{ };

} // namespace console
} // namespace csvhelper::utils
