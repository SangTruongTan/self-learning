#include <iostream>

#include "Animal.h"
#include "Chicken.h"
#include "Logger.h"
#include "MacDonald.h"
#include "TimeManager.h"

int main(int argc, char **argv) {

    Farm::Logger newLogger("Farm", "Farm1");
    Farm::MacDonald *Mac = new Farm::MacDonald(&newLogger);

    Mac->start();
    return EXIT_SUCCESS;
}
