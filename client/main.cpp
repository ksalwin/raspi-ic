#include "App/App.hpp"
#include "Log/ILog.hpp"
#include "Log/Log.hpp"

int main()
{
    // Create logger
    ILog* log = new Log();

    // Create app and pass logger to it
    App app(log);

    // Run app
    app.run();

    return 0;
}