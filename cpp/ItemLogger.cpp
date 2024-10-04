#include "Cluster.h"
#include "ILogger.h"
#include "ItemLogger.h"
#include "IClusterManager.h"


template <typename T>
void ItemLogger<T>::Log(const T& item) const {
    std::wcout << "Item Id   [" << item.properties.itemId << "]\n";
    std::wcout << "Item Name [" << item.properties.itemName << "]\n";
    std::wcout << "Item Size [" << item.properties.byteSizeName << "]\n" << std::endl;
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
        DisplayNodes(items);
    }
    else if constexpr (std::is_same_v<T, Resource>) {
        DisplayResources(items);
    }
    else if constexpr (std::is_same_v<T, Group>) {
        DisplayGroups(items);
    }
    else if constexpr (std::is_same_v<T, ResourceType>) {
        DisplayResourceTypes(items);
    }
    else if constexpr (std::is_same_v<T, Network>) {
        DisplayNetworks(items);
    }
    else if constexpr (std::is_same_v<T, NetInterface>) {
        DisplayNetInterfaces(items);
    }
    else if constexpr (std::is_same_v<T, SharedVolume>) {
        DisplaySharedVolumes(items);
    }
}

template <typename T>
void ItemLogger<T>::DisplayNodes(const std::list<Node>& nodes) const {
    std::wcout << "Start iteration of nodes! \n" << std::endl;
    for (const Node& node : nodes) {
        std::wcout << "Node Id   [" << node.properties.itemId << "]\n";
        std::wcout << "Node Name [" << node.properties.itemName << "]\n";
        std::wcout << "Name Size [" << node.properties.byteSizeName << "]\n" << std::endl;
    }
    std::wcout << "Finish! \n" << std::endl;
}

template <typename T>
void ItemLogger<T>::DisplayResources(const std::list<Resource>& resources) const {
    std::wcout << "Start iteration of resources! \n" << std::endl;
    for (const Resource& resource : resources) {
        std::wcout << "Resource Name         [" << resource.properties.itemName << "]\n";
        std::wcout << "Resource ResType Name [" << resource.resTypeName << "]\n" << std::endl;
    }
    std::wcout << "Finish! \n" << std::endl;
}

template <typename T>
void ItemLogger<T>::DisplayGroups(const std::list<Group>& groups) const {
    std::wcout << "Start iteration of groups! \n" << std::endl;
    for (const Group& group : groups) {
        std::wcout << "Group Name [" << group.properties.itemName << "] \n";
    }
    std::wcout << "Finish! \n" << std::endl;
}

template <typename T>
void ItemLogger<T>::DisplayResourceTypes(const std::list<ResourceType>& restypes) const {
    std::wcout << "Start iteration of restypes! \n" << std::endl;
    for (const ResourceType& restype : restypes) {
        std::wcout << "ResType Name [" << restype.properties.itemName << "] \n";
    }
    std::wcout << "Finish! \n" << std::endl;
}

template <typename T>
void ItemLogger<T>::DisplayNetworks(const std::list<Network>& networks) const {
    std::wcout << "Start iteration of networks! \n" << std::endl;
    for (const Network& network : networks) {
        std::wcout << "Network Name [" << network.properties.itemName << "] \n";
    }
    std::wcout << "Finish! \n" << std::endl;
}

template <typename T>
void ItemLogger<T>::DisplayNetInterfaces(const std::list<NetInterface>& netinterfaces) const {
    std::wcout << "Start iteration of netinterfaces! \n" << std::endl;
    for (const NetInterface& netinterface : netinterfaces) {
        std::wcout << "NetInterface Name [" << netinterface.properties.itemName << "] \n";
    }
    std::wcout << "Finish! \n" << std::endl;
}

template <typename T>
void ItemLogger<T>::DisplaySharedVolumes(const std::list<SharedVolume>& sharedvolumes) const {
    if (!sharedvolumes.empty()) {
        std::wcout << "Start iteration of sharedvolumes! \n" << std::endl;
        for (const SharedVolume& sharedvolume : sharedvolumes) {
            std::wcout << "SharedVolumes Name [" << sharedvolume.properties.itemName << "] \n";
        }
        std::wcout << "Finish! \n" << std::endl;
    }
}


template class ItemLogger<Node>;
template class ItemLogger<Resource>;
template class ItemLogger<Group>;
//
//
//#include "Cluster.h"
//#include "ILogger.h"
//#include "ItemLogger.h"
//#include "IClusterManager.h"
//
//
//template <typename T>
//void ItemLogger<T>::Log(const T& item) const {
//    std::wcout << "Item Id   [" << item.properties.itemId << "]\n";
//    std::wcout << "Item Name [" << item.properties.itemName << "]\n";
//    std::wcout << "Item Size [" << item.properties.byteSizeName << "]\n\n";
//}
//
//template <typename T>
//void ItemLogger<T>::LogList(const std::list<T>& items) const {
//    DisplayItems(items);
//}
//
//template <typename T>
//void ItemLogger<T>::DisplayClusterInfo(const ClusterManager& manager) const {
//    const ClusterProvider* provider = manager.GetClusterProvider();
//
//    HCLUSTER hCluster = provider->GetClusterHandle();
//    std::wstring clusName;
//    provider->GetClusterName(clusName);
//
//    std::wcout << "Handle       [" << hCluster << "]\n";
//    std::wcout << "Cluster Name [" << clusName << "]\n";
//
//    DWORD state = 0;
//    provider->GetClusterState(&state);
//    std::wcout << "Cluster state[" << state << "]. Must be 19\n" << std::endl;
//}
//
//template <typename T>
//void ItemLogger<T>::DisplayItems(const std::list<T>& items) const {
//    if constexpr (std::is_same_v<T, Node>) {
//        IterateItems(items, [this](const Node& node) {
//            std::wcout << "Node Id   [" << node.properties.itemId << "]\n";
//            std::wcout << "Node Name [" << node.properties.itemName << "]\n";
//            std::wcout << "Name Size [" << node.properties.byteSizeName << "]\n\n";
//            });
//    }
//    else if constexpr (std::is_same_v<T, Resource>) {
//        IterateItems(items, [this](const Resource& resource) {
//            std::wcout << "Resource Name         [" << resource.properties.itemName << "]\n";
//            std::wcout << "Resource ResType Name [" << resource.resTypeName << "]\n\n";
//            });
//    }
//    else if constexpr (std::is_same_v<T, Group>) {
//        IterateItems(items, [this](const Group& group) {
//            std::wcout << "Group Name [" << group.properties.itemName << "] \n";
//            });
//    }
//    else if constexpr (std::is_same_v<T, ResourceType>) {
//        IterateItems(items, [this](const ResourceType& restype) {
//            std::wcout << "ResType Name [" << restype.properties.itemName << "] \n";
//            });
//    }
//    else if constexpr (std::is_same_v<T, Network>) {
//        IterateItems(items, [this](const Network& network) {
//            std::wcout << "Network Name [" << network.properties.itemName << "] \n";
//            });
//    }
//    else if constexpr (std::is_same_v<T, NetInterface>) {
//        IterateItems(items, [this](const NetInterface& netinterface) {
//            std::wcout << "NetInterface Name [" << netinterface.properties.itemName << "] \n";
//            });
//    }
//    else if constexpr (std::is_same_v<T, SharedVolume>) {
//        IterateItems(items, [this](const SharedVolume& sharvol) {
//            std::wcout << "SharedVolume Name [" << sharvol.properties.itemName << "] \n";
//            });
//    }
//}
//
//template <typename T>
//void ItemLogger<T>::IterateItems(const std::list<T>& items, std::function<void(const T&)> displayFunc) const {
//    std::wcout << "Start iteration of items! \n\n";
//    for (const auto& item : items) {
//        displayFunc(item);
//    }
//    std::wcout << "Finish!\n\n";
//}
//
//template class ItemLogger<Node>;
//template class ItemLogger<Resource>;
//template class ItemLogger<Group>;