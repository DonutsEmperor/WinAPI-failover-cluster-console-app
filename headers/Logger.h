#pragma once

#ifndef LOGGER_H
#define LOGGER_H

template <typename T>
class Logger : public ILogger<T> {
public:
    virtual ~Logger() = default;

    virtual void LogBase(const T& item) const override;
    virtual void LogList(const std::list<T>& items) const override;

private:
    void DisplayItems(const std::list<T>& items) const;
    void IterateItems(const std::list<T>&, std::function<void(const T&)>) const;
};

#include "Logger.inl"
#endif