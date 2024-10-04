#pragma once

class ClusterManager;

template <typename T>
class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void LogList(const std::list<T>& items) const = 0;
};

class LoggerFactory {
public:
    template <typename T>
    static std::unique_ptr<ILogger<T>> CreateLogger();
};