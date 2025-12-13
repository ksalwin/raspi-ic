#include "Log.hpp"
#include <chrono>
#include <format>
#include <iostream>
#include <string>

/*
 * Constructor
 * @param write_to_console Whether to write to console.
 * @param write_to_file Whether to write to file.
 */
Log::Log(bool write_to_console, bool write_to_file)
    : m_write_to_console(write_to_console), m_write_to_file(write_to_file)
{
}

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

    // Create log message with timestamp
    std::string log_message = '[' + timestamp_str + "] " + message;

    // Write to console and file if enabled
    if (m_write_to_console)
    {
        write_to_console(log_message);
    }
    if (m_write_to_file)
    {
        if (!m_file.is_open())
        {
            // Open file with timestamp in name
            m_file.open(timestamp_str + ".log");
        }

        write_to_file(log_message);
    }
}

void Log::write_to_console(const std::string& log_message)
{
    std::cout << log_message << std::endl;
}

void Log::write_to_file(const std::string& log_message)
{
    if (m_file.is_open())
    {
        m_file << log_message << std::endl;
    }
}