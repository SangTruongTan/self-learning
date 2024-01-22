#include <iostream>

#include "Animal.h"
#include "Chicken.h"
#include "Logger.h"
#include "MacDonald.h"
#include "TimeManager.h"

int main(int argc, char **argv) {

    Farm::Logger::getInstance().setLogLevel(Farm::LogLevel::INFO);
    Farm::Logger::getInstance().setAppContext("Farm", "Farm1");
    Farm::MacDonald *Mac = new Farm::MacDonald();

    Mac->start();
    return EXIT_SUCCESS;
}
