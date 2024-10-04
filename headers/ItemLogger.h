#pragma once

class ClusterManager;

template <typename T>
class ItemLogger : public ILogger<T> {
public:
    void Log(const T& ) const override;
    void LogList(const std::list<T>& ) const override;

private:
    void DisplayClusterInfo(const ClusterManager& ) const;
    void DisplayItems(const std::list<T>& ) const;
    void DisplayNodes(const std::list<Node>& ) const;
    void DisplayResources(const std::list<Resource>& ) const;
    void DisplayGroups(const std::list<Group>& ) const;
    void DisplayResourceTypes(const std::list<ResourceType>& ) const;
    void DisplayNetworks(const std::list<Network>& ) const;
    void DisplayNetInterfaces(const std::list<NetInterface>& ) const;
    void DisplaySharedVolumes(const std::list<SharedVolume>& ) const;

};


//#pragma once
//
//template <typename T>
//class ItemLogger : public ILogger<T> {
//public:
//    void Log(const T&) const override;
//    void LogList(const std::list<T>&) const override;
//    void DisplayClusterInfo(const ClusterManager&) const override;
//
//private:
//    void DisplayItems(const std::list<T>&) const;
//    void IterateItems(const std::list<T>& items, std::function<void(const T&)> displayFunc) const;
//};
