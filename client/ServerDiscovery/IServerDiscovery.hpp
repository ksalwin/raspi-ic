#pragma once

#include <optional>
#include <string>

class IServerDiscovery
{
public:
    virtual std::optional<std::string> discover() = 0;
    virtual ~IServerDiscovery() = default;
};