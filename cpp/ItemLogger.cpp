#include "Cluster.h"
#include "ILogger.h"
#include "ItemLogger.h"
#include "IClusterManager.h"


template <typename T>
void ItemLogger<T>::LogBase(const T& item) const {
    std::wcout << "Item Id   [" << item.properties.itemId << "]\n";
    std::wcout << "Item Name [" << item.properties.itemName << "]\n";
    std::wcout << "Item Size [" << item.properties.byteSizeName << "]\n\n";
}

template <typename T>
void ItemLogger<T>::LogList(const std::list<T>& items) const {
    DisplayItems(items);
}

template <typename T>
void ItemLogger<T>::DisplayClusterInfo(const ClusterManager& manager) const {
    const ClusterProvider* provider = manager.GetClusterProvider();

    HCLUSTER hCluster = provider->GetClusterHandle();
    std::wstring clusName;
    provider->GetClusterName(clusName);

    std::wcout << "Handle       [" << hCluster << "]\n";
    std::wcout << "Cluster Name [" << clusName << "]\n";

    DWORD state = 0;
    provider->GetClusterState(&state);
    std::wcout << "Cluster state[" << state << "]. Must be 19\n" << std::endl;
}

template <typename T>
void ItemLogger<T>::DisplayItems(const std::list<T>& items) const {
    if constexpr (std::is_same_v<T, Node>) {
        IterateItems(items, [this](const Node& node) {
            std::wcout << "Node Id   [" << node.properties.itemId << "]\n";
            std::wcout << "Node Name [" << node.properties.itemName << "]\n";
            std::wcout << "Name Size [" << node.properties.byteSizeName << "]\n\n";
            });
    }
    else if constexpr (std::is_same_v<T, Resource>) {
        IterateItems(items, [this](const Resource& resource) {
            std::wcout << "Resource Name         [" << resource.properties.itemName << "]\n";
            std::wcout << "Resource ResType Name [" << resource.resTypeName << "]\n\n";
            });
    }
    else if constexpr (std::is_same_v<T, Group>) {
        IterateItems(items, [this](const Group& group) {
            std::wcout << "Group Name [" << group.properties.itemName << "] \n";
            });
    }
    else if constexpr (std::is_same_v<T, ResourceType>) {
        IterateItems(items, [this](const ResourceType& restype) {
            std::wcout << "ResType Name [" << restype.properties.itemName << "] \n";
            });
    }
    else if constexpr (std::is_same_v<T, Network>) {
        IterateItems(items, [this](const Network& network) {
            std::wcout << "Network Name [" << network.properties.itemName << "] \n";
            });
    }
    else if constexpr (std::is_same_v<T, NetInterface>) {
        IterateItems(items, [this](const NetInterface& netinterface) {
            std::wcout << "NetInterface Name [" << netinterface.properties.itemName << "] \n";
            });
    }
    else if constexpr (std::is_same_v<T, SharedVolume>) {
        IterateItems(items, [this](const SharedVolume& sharvol) {
            std::wcout << "SharedVolume Name [" << sharvol.properties.itemName << "] \n";
            });
    }
}

template <typename T>
void ItemLogger<T>::IterateItems(const std::list<T>& items, std::function<void(const T&)> displayFunc) const {
    std::wcout << "Start iteration of items! \n";
    for (const auto& item : items) {
        displayFunc(item);
    }
    std::wcout << "Finish!\n";
}

template class ItemLogger<Node>;
template class ItemLogger<Resource>;
template class ItemLogger<Group>;