#pragma once

#include "Log/ILog.hpp"

class App
{
public:
    App(ILog* log);
    ~App();
    void run();

private:
    ILog* m_log;
};