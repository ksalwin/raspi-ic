#pragma once

#include "IServerDiscovery.hpp"

class ServerDiscovery : public IServerDiscovery
{
public:
    ServerDiscovery();
    ~ServerDiscovery() override;
    std::optional<std::string> discover() override;

private:
    // Server address to send the discovery message to
    const std::string m_broadcast_address = "255.255.255.255";
    // Discovery message to send to the server
    const std::string m_discovery_message = "raspi-ic where are you?";
    // Socket file descriptor
    int m_socket_fd = -1;
};