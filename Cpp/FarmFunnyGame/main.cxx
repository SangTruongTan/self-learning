#include <iostream>

#include "Animal.h"
#include "Chicken.h"
#include "Logger.h"
#include "MacDonald.h"
#include "TimeManager.h"

/* To eliminate the warning, we can either mark it as [[maybe_unused]] or
 * casting it to void. */
int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    static_cast<void>(argc);
    static_cast<void>(argv);
    Farm::Logger::getInstance().setLogLevel(Farm::LogLevel::DEBUG);
    Farm::Logger::getInstance().setAppContext("Farm", "Farm1");
    Farm::MacDonald *Mac = new Farm::MacDonald();

    Mac->start();
    return EXIT_SUCCESS;
}
