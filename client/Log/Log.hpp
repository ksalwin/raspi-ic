#pragma once

#include "ILog.hpp"
#include <fstream>

class Log : public ILog
{
public:
    void write(const std::string& message) override;
    ~Log() override;

private:
    std::ofstream m_file;
};