#pragma once

#include <string>

class ILog
{
public:
    virtual void write(const std::string& message) = 0;
    virtual ~ILog() = default;
};