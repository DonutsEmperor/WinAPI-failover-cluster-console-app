#pragma once

class ClusterManager;

template <typename T>
class ItemLogger : public ILogger<T> {
public:
    void LogBase(const T&) const override;
    void LogList(const std::list<T>&) const override;
    void DisplayClusterInfo(const ClusterManager&) const override;

private:
    void DisplayItems(const std::list<T>&) const;
    void IterateItems(const std::list<T>& items, std::function<void(const T&)> displayFunc) const;
};
