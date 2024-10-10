#pragma once

#ifndef LOGGERFACTORY_H
#define LOGGERFACTORY_H

class LoggerFactory {
public:
    template <typename T>
    static std::unique_ptr<ILogger<T>> CreateLogger();
};

#include "LoggerFactory.inl"

#endif LOGGERFACTORY_H