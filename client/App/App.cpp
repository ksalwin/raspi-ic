#include "App.hpp"

App::App(ILog* log) : m_log(log)
{
}

App::~App()
{
}

void App::run()
{
    m_log->write("App is running");
    m_log->write("App is shutting down");
}