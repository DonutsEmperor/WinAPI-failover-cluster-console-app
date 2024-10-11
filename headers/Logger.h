#pragma once
#include "ILogger.h"

#ifndef LOGGER_H
#define LOGGER_H

template <typename T>
class Logger : public ILogger<T> {
public:
    explicit Logger() = default;
    virtual ~Logger() = default;

    virtual void LogBase(const T& item) const override;
    virtual void LogSpecial(const T& item) const override;
    virtual void LogListBase(const std::list<T>& items) const override;
    virtual void LogListSpecial(const std::list<T>& items) const override;

private:
    void IterateItems(const std::list<T>&, std::function<void(const T&)>) const;
};

#include "Logger.inl"
#endif