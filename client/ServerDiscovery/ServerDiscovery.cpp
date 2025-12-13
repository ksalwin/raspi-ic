#include "ServerDiscovery.hpp"

ServerDiscovery::ServerDiscovery()
{
}

ServerDiscovery::~ServerDiscovery()
{
}

/*
 * Function to discover the server.
 * @return The server address if found, otherwise std::nullopt.
 *
 * Steps:
 * - Create a UDP socket.
 * - Enable broadcast on the socket.
 * - Send a discovery message to the broadcast address (e.g. 255.255.255.255:PORT).
 * - Wait for a response from the server (with timeout).
 * - If a response is received, return the server address.
 * - If no response is received, return std::nullopt.
*/
std::optional<std::string> ServerDiscovery::discover()
{
    // Create a UDP socket
    m_socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_socket_fd == -1)
    {
        return std::nullopt;
    }

    // Enable broadcast on the socket
    int broadcast_enable = 1;
    if (setsockopt(m_socket_fd, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable)) == -1)
    {
        close(m_socket_fd);
        return std::nullopt;
    }

    // Send a discovery message to the broadcast address (e.g. 255.255.255.255:PORT)
    if (sendto(m_socket_fd, m_discovery_message.c_str(), m_discovery_message.size(), 0, (struct sockaddr*)&broadcast_addr, sizeof(broadcast_addr)) == -1)
    {
        close(m_socket_fd);
        return std::nullopt;
    }

    // Wait for a response from the server (with timeout)
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    if (setsockopt(m_socket_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1)
    {
        close(m_socket_fd);
        return std::nullopt;
    }
    
    // Receive a response from the server
    char buffer[1024];
    socklen_t addr_len = sizeof(m_broadcast_addr);
    if (recvfrom(m_socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&m_broadcast_addr, &addr_len) == -1)
    {
        close(m_socket_fd);
        return std::nullopt;
    }

    // Close the socket
    close(m_socket_fd);

    // Return the server address
    return std::string(buffer);
}