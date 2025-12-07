#pragma once

#include "ILog.hpp"
#include <fstream>

class Log : public ILog
{
public:
    ~Log() override;

    void write(const std::string& message) override;

private:
    std::ofstream m_file;
};