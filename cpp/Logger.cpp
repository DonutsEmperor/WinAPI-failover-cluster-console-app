#include "../headers/Cluster.h"
#include "../headers/ILogger.h"

template <typename T>
std::unique_ptr<ILogger<T>> LoggerFactory::CreateLogger() {
    return std::make_unique<ILogger<T>>();
}

template <typename T>
class Logger : public ILogger<T> {
public:

    void LogProperties(const T& item) const override {
        /*std::wcout << "Node Id   [" << node.properties.itemId << "]\n";
        std::wcout << "Node Name [" << node.properties.itemName << "]\n";
        std::wcout << "Name Size [" << node.properties.byteSizeName << "]\n" << std::endl;
        std::wcout << "Node Id   [" << node.properties.itemId << "]\n";
        std::wcout << "Node Name [" << node.properties.itemName << "]\n";
        std::wcout << "Name Size [" << node.properties.byteSizeName << "]\n" << std::endl;*/
    }

    void LogList(const std::list<T>& items) const override {
        DisplayItems(items);
    }

    /*void DisplayClusterInfo(const ClusterManager& manager) const {
        const ClusterProvider* provider = manager.GetClusterProvider();

        HCLUSTER hCluster = provider->GetClusterHandle();
        std::wstring clusName;
        provider->GetClusterName(clusName);

        std::wcout << "Handle       [" << hCluster << "]\n";
        std::wcout << "Cluster Name [" << clusName << "]\n";

        DWORD state = 0;
        provider->GetClusterState(&state);
        std::wcout << "Cluster state[" << state << "]. Must be 19\n" << std::endl;
    }*/

private:
    void DisplayItems(const std::list<T>& items) const {
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

    void DisplayNodes(const std::list<Node>& nodes) const {
        std::wcout << "Start iteration of nodes! \n" << std::endl;
        for (const Node& node : nodes) {
            std::wcout << "Node Id   [" << node.properties.itemId << "]\n";
            std::wcout << "Node Name [" << node.properties.itemName << "]\n";
            std::wcout << "Name Size [" << node.properties.byteSizeName << "]\n" << std::endl;
        }
        std::wcout << "Finish! \n" << std::endl;
    }
    void DisplayResources(const std::list<Resource>& resources) const {
        std::wcout << "Start iteration of resources! \n" << std::endl;
        for (const Resource& resource : resources) {
            std::wcout << "Resource Name         [" << resource.properties.itemName << "]\n";
            std::wcout << "Resource ResType Name [" << resource.resTypeName << "]\n" << std::endl;
        }
        std::wcout << "Finish! \n" << std::endl;
    }
    void DisplayGroups(const std::list<Group>& groups) const {
        std::wcout << "Start iteration of groups! \n" << std::endl;
        for (const Group& group : groups) {
            std::wcout << "Group Name [" << group.properties.itemName << "] \n";
        }
        std::wcout << "Finish! \n" << std::endl;
    }
    void DisplayResourceTypes(const std::list<ResourceType>& restypes) const {
        std::wcout << "Start iteration of restypes! \n" << std::endl;
        for (const ResourceType& restype : restypes) {
            std::wcout << "ResType Name [" << restype.properties.itemName << "] \n";
        }
        std::wcout << "Finish! \n" << std::endl;
    }
    void DisplayNetworks(const std::list<Network>& networks) const {
        std::wcout << "Start iteration of networks! \n" << std::endl;
        for (const Network& network : networks) {
            std::wcout << "Network Name [" << network.properties.itemName << "] \n";
        }
        std::wcout << "Finish! \n" << std::endl;
    }
    void DisplayNetInterfaces(const std::list<NetInterface>& netinterfaces) const {
        std::wcout << "Start iteration of netinterfaces! \n" << std::endl;
        for (const NetInterface& netinterface : netinterfaces) {
            std::wcout << "NetInterface Name [" << netinterface.properties.itemName << "] \n";
        }
        std::wcout << "Finish! \n" << std::endl;
    }
    void DisplaySharedVolumes(const std::list<SharedVolume>& sharedvolumes) const {
        if (!sharedvolumes.empty()) {
            std::wcout << "Start iteration of sharedvolumes! \n" << std::endl;
            for (const SharedVolume& sharedvolume : sharedvolumes) {
                std::wcout << "SharedVolumes Name [" << sharedvolume.properties.itemName << "] \n";
            }
            std::wcout << "Finish! \n" << std::endl;
        }
    }

};