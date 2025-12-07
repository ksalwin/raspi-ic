#include "App.hpp"

App::App(ILog* log) : m_log(log)
{
}

App::~App()
{
}

void App::run()
{
    log("App is running");
    log("App is shutting down");
}