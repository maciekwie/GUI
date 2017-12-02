/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#include "Logger.h"

#include <iostream>

using namespace gui;

Logger::Logger() :
    logStream(std::cout.rdbuf()),
    fileStream(NULL)
{
    logStream.tie(&std::cout);
}

Logger::Logger(std::string filePath) :
    logStream(NULL),
    fileStream(NULL)
{
    fileStream = new std::ofstream(filePath.c_str());

    logStream.rdbuf(fileStream->rdbuf());
    logStream.tie(fileStream);
}

Logger::~Logger()
{
    if(fileStream != NULL)
        delete fileStream;
}
