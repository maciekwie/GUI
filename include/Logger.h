/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <ostream>
#include <fstream>

namespace gui
{

class Logger
{
    public:
        Logger();
        Logger(std::string filePath);

        ~Logger();

        inline std::ostream & getStream() { return logStream; };

    protected:

    private:
        std::ostream logStream;
        std::ofstream *fileStream;
};

}

#endif // LOGGER_H
