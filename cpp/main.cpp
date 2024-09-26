#include <windows.h>
#include <iostream>
#include <fcntl.h>
#include <io.h>

#include "ClusApi.h"
#include "../headers/IClusterManager.h"

#include "ClusterManager.cpp"

#pragma comment(lib, "ClusAPI.lib")

void SetConsoleMode() 
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);
}

std::wstring GetClusterNodeName() 
{
    std::wcout << "Hello Enter ClusterNodeName!\n";
    std::wstring input;
    std::wcin >> input;
    return input;
}

void DisplayClusterInfo(ClusterManager& provider)
{

    HCLUSTER hCluster = provider.GetClusterHandle();
    std::wstring clusName;
    provider.GetClusterName(clusName);

    std::wcout << "Handle       [" << hCluster << "]\n";
    std::wcout << "Cluster Name [" << clusName << "]\n";

    DWORD state = 0;
    provider.GetClusterState(&state);
    std::wcout << "Cluster state[" << state << "]. Must be 19\n" << std::endl;
}

template <typename T>
void DisplayNodes(const std::list<T>& nodes) {
    std::wcout << "Start iteration of nodes! \n" << std::endl;
    for (const T& node : nodes) {
        std::wcout << "Node Id   [" << node.properties.itemId << "]\n";
        std::wcout << "Node Name [" << node.properties.itemName << "]\n";
        std::wcout << "Name Size [" << node.properties.byteSizeName << "]\n" << std::endl;
    }
    std::wcout << "Finish! \n" << std::endl;
}

template <typename T>
void DisplayResources(const std::list<T>& resources) {
    std::wcout << "Start iteration of resources! \n" << std::endl;
    for (const T& resource : resources) {
        std::wcout << "Resource Name         [" << resource.properties.itemName << "]\n";
        std::wcout << "Resource ResType Name [" << resource.resTypeName << "]\n" << std::endl;
    }
    std::wcout << "Finish! \n" << std::endl;
}

template <typename T>
void DisplayGroups(const std::list<T>& groups) {
    std::wcout << "Start iteration of groups! \n" << std::endl;
    for (const T& group : groups) {
        std::wcout << "Group Name [" << group.properties.itemName << "] \n";
    }
    std::wcout << "Finish! \n" << std::endl;
}

template <typename T>
void DisplayResTypes(const std::list<T>& restypes) {
    std::wcout << "Start iteration of restypes! \n" << std::endl;
    for (const T& restype : restypes) {
        std::wcout << "ResType Name [" << restype.properties.itemName << "] \n";
    }
    std::wcout << "Finish! \n" << std::endl;
}

template <typename T>
void DisplayNetworks(const std::list<T>& networks) {
    std::wcout << "Start iteration of networks! \n" << std::endl;
    for (const T& network : networks) {
        std::wcout << "Network Name [" << network.properties.itemName << "] \n";
    }
    std::wcout << "Finish! \n" << std::endl;
}

template <typename T>
void DisplayNetInterfaces(const std::list<T>& netinterfaces) {
    std::wcout << "Start iteration of netinterfaces! \n" << std::endl;
    for (const T& netinterface : netinterfaces) {
        std::wcout << "NetInterface Name [" << netinterface.properties.itemName << "] \n";
    }
    std::wcout << "Finish! \n" << std::endl;
}

template <typename T>
void DisplaySharedVolumes(const std::list<T>& sharedvolumes) {
    if (!sharedvolumes.empty()) {
        std::wcout << "Start iteration of sharedvolumes! \n" << std::endl;
        for (const T& sharedvolume : sharedvolumes) {
            std::wcout << "SharedVolumes Name [" << sharedvolume.properties.itemName << "] \n";
        }
        std::wcout << "Finish! \n" << std::endl;
    }
}

int main() 
{
    SetConsoleMode();
    std::wstring input = GetClusterNodeName();
    std::wcout << "You've entered in cluster: [" << input << "]!\n";

    ClusterManager manager;
    DisplayClusterInfo(manager);

    NodeProvider* nodeProvider = manager.GetNodeProvider();
    std::list<Node> nodes;
    nodeProvider->GetClusterNodes(nodes);
    DisplayNodes(nodes);

    ResourceProvider* resourceProvider = manager.GetResourceProvider();
    std::list<Resource> resources;
    resourceProvider->GetClusterResources(resources);
    DisplayResources(resources);

    GroupProvider* groupProvider = manager.GetGroupProvider();
    std::list<Group> groups;
    groupProvider->GetClusterGroups(groups);
    DisplayGroups(groups);

    std::list<ResourceType> restypes;
    manager.GetResourceTypes(restypes);
    DisplayResTypes(restypes);

    std::list<Network> networks;
    manager.GetNetworks(networks);
    DisplayNetworks(networks);

    std::list<NetInterface> netinterfaces;
    manager.GetNetInterfaces(netinterfaces);
    DisplayNetInterfaces(netinterfaces);

    std::list<SharedVolume> sharedvolumes;
    manager.GetSharedVolumeList(sharedvolumes);
    DisplaySharedVolumes(sharedvolumes);

    return 0;
}