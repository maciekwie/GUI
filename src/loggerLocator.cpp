/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#include "loggerLocator.h"

#include "Logger.h"

namespace gui{

std::ostream & getLogStr()
{
    static Logger *logger = NULL;

    if(!logger)
    {
        logger = new Logger();
    }

    return logger->getStream();
}

}
