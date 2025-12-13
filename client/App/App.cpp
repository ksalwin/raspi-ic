#include "App.hpp"

#include "ServerDiscovery/ServerDiscovery.hpp"

App::App(ILog* log) : m_log(log)
{
}

App::~App()
{
}

void App::run()
{
    log("App is running");

    ServerDiscovery server_discovery;

    std::optional<std::string> server_address = server_discovery.discover();
    if (server_address.has_value())
    {
        log("Server address: " + server_address.value());
    }
    else
    {
        log("No server found");
    }

    log("App is shutting down");
}