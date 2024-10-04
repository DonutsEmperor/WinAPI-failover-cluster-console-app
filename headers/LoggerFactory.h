#pragma once

class LoggerFactory {
public:
    template <typename T>
    static std::unique_ptr<ILogger<T>> CreateLogger();
};