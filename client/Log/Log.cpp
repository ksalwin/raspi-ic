#include "Log.hpp"
#include <chrono>
#include <format>
#include <string>

/*
 * Destructor
 * If file is open, close it.
 */
Log::~Log()
{
    if (m_file.is_open())
    {
        m_file.close();
    }
}

/*
 * Write a message to the log file.
 * @param message The message to write to the log file.
 * If file is not open, open it.
 * The file name is the current timestamp in the format YYYY-MM-DD_HH:MM:SS.log.
 * Time with full seconds precision floored to the nearest second.
 * If file is open, write the message to the file.
 */
void Log::write(const std::string& message)
{
    // Get current timestamp and format as YYYY-MM-DD_HH:MM:SS
    std::string timestamp_str = std::format("{:%Y-%m-%d_%H:%M:%S}",
        std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now()));

    if (!m_file.is_open())
    {
        // Open file with timestamp in name
        m_file.open(timestamp_str + ".log");
    }

    if (m_file.is_open())
    {
        m_file  << '[' << timestamp_str << "] "
                << message << std::endl;
    }
}