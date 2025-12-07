#pragma once

#include "Log/ILog.hpp"

class App
{
public:
    App(ILog* log = nullptr);
    ~App();
    void run();

private:
    ILog* m_log;
    void log(const std::string& message);
};

inline void App::log(const std::string& message)
{
    if (m_log)
    {
        m_log->write(message);
    }
}