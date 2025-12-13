#include "ServerDiscovery.hpp"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>


ServerDiscovery::ServerDiscovery()
{
}

ServerDiscovery::~ServerDiscovery()
{
    if (m_socket_fd != -1)
    {
        close(m_socket_fd);
        m_socket_fd = -1;
    }
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
    // Server address to send the discovery message to
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_broadcast_port);
    addr.sin_addr.s_addr = htonl(INADDR_BROADCAST); //255.255.255.255

    // Create a UDP socket
    m_socket_fd = socket(addr.sin_family, SOCK_DGRAM, IPPROTO_UDP);
    if (m_socket_fd == -1)
    {
        return std::nullopt;
    }

    // Enable broadcast on the socket
    int broadcast_enable = 1;

    const int rc1 = setsockopt(
        m_socket_fd,
        SOL_SOCKET,
        SO_BROADCAST,
        &broadcast_enable,
        sizeof(broadcast_enable));

    if (rc1 == -1)
    {
        close(m_socket_fd);
        m_socket_fd = -1;
        return std::nullopt;
    }

    // Send a discovery message to the broadcast address (e.g. 255.255.255.255:PORT)
    const ssize_t sent = sendto(
        m_socket_fd,
        m_discovery_message.data(),
        m_discovery_message.size(),
        0,
        reinterpret_cast<const sockaddr*>(&addr),
        sizeof(addr)
    );

    if (sent == -1) {
        close(m_socket_fd);
        m_socket_fd = -1;
        return std::nullopt;
    }

    // Wait for a response from the server (with timeout)
    timeval timeout{};
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    const int rc2 = setsockopt(
        m_socket_fd,
        SOL_SOCKET,
        SO_RCVTIMEO,
        &timeout,
        sizeof(timeout)
    );
    
    if (rc2 == -1) {
        close(m_socket_fd);
        m_socket_fd = -1;
        return std::nullopt;
    }
    
    // Receive a response from the server
    sockaddr_in sender{};
    socklen_t sender_len = sizeof(sender);
    char buffer[1024];

    const ssize_t n = recvfrom(
        m_socket_fd,
        buffer,
        sizeof(buffer),
        0,
        reinterpret_cast<sockaddr*>(&sender),
        &sender_len);

    if (n == -1)
    {
        close(m_socket_fd);
        m_socket_fd = -1;
        return std::nullopt;
    }

    // Close the socket
    close(m_socket_fd);
    m_socket_fd = -1;

    // Null terminate the buffer and return the server address
    return std::string(buffer, static_cast<size_t>(n));
}