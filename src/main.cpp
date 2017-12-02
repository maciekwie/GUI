/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#include <iostream>
#include <stdexcept>

#include "App.h"
#include "loggerLocator.h"

int main(int argc, char **argv)
{
    App app(argc, argv);

    try
    {
        app.initAllegro();
        app.init();
    }
    catch(std::exception &e)
    {
        getLogStr() << "App initialization error: " << e.what() << std::endl;
        return -1;
    }

    while(app.loop(true)) {};

    return 0;
}
