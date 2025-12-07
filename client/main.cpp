#include "App/App.hpp"
#include "Log/Log.hpp"

int main()
{
    // Create logger
    Log log;

    // Create app and pass pointer to logger to it
    App app(&log);

    // Run app
    app.run();

    return 0;
}