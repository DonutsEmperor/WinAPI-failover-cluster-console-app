#pragma once

template <typename T>
class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void LogBase(const T& ) const = 0;
    virtual void LogList(const std::list<T>& ) const = 0;
};