#pragma once
#include <fstream>
#include <string>

namespace csvhelper::utils {

struct FileHandler
{
public:
    explicit FileHandler(const std::string& p_fileName);
    ~FileHandler();
    std::fstream& get() { return m_file; }

private:
    std::fstream m_file;
};

} // namespace csvhelper::utils
