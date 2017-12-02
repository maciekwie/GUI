/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

/**
 *  \file loggerLocator.h
 *
 *  Provides function accessing global Logger object.
 */

#ifndef LOGGERLOCATOR_H
#define LOGGERLOCATOR_H

#include <ostream>

namespace gui
{

std::ostream & getLogStr();

}

#endif // LOGGERLOCATOR_H
