#pragma once

#include "IServerDiscovery.hpp"

#include <optional>
#include <string>

class ServerDiscovery : public IServerDiscovery
{
public:
    ServerDiscovery();
    ~ServerDiscovery() override;
    std::optional<std::string> discover() override;

private:
    const int m_broadcast_port = 4242;
    const std::string m_discovery_message = "raspi-ic are you there?";
    int m_socket_fd = -1; // Socket file descriptor
};