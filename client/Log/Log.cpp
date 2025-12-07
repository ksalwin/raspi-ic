#include "Log.hpp"

Log::~Log()
{
    m_file.close();
}

/*
 * Write a message to the log file.
 * @param message The message to write to the log file.
 * If file is not open, open it.
 * If file is open, write the message to the file.
 */
void Log::write(const std::string& message)
{
    if (!m_file.is_open())
    {
        m_file.open("file.log");
    }

    m_file << message << std::endl;
}