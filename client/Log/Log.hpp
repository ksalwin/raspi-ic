#pragma once

#include "ILog.hpp"
#include <fstream>

class Log : public ILog
{
public:
    Log(bool write_to_console = true, bool write_to_file = true);
    ~Log() override;

    void write(const std::string& message) override;

private:
    bool m_write_to_console = true; // Write to console by default
    bool m_write_to_file = true; // Write to file by default
    
    std::ofstream m_file;

    void write_to_console(const std::string& log_message);
    void write_to_file(const std::string& log_message);
};