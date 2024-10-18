#pragma once

template <typename T>
class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void LogOneBase(const T& item) const = 0;
    virtual void LogOneSpecial(const T& item) const = 0;
    virtual void LogListBase(const std::list<T>& items) const = 0;
    virtual void LogListSpecial(const std::list<T>& items) const = 0;
};