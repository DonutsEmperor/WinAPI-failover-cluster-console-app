#include "IClusterManager.h"

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

int main() 
{
    SetConsoleMode();
    std::wstring input = GetClusterNodeName();
    std::wcout << "You've entered in cluster: [" << input << "]!\n";

    const ClusterManager manager(&input);
    const LoggerFactory* logFactory = manager.GetLoggerFactory();
    const NodeProvider* nodeProvider = manager.GetNodeProvider();

    std::wcout << "\n LISTING OF HAMSTER !\n\n";

    std::list<Node> nodes;
    nodeProvider->GetClusterNodes(nodes);

    auto logger = logFactory->CreateLogger<Node>();

    // Attempt to cast the ILogger<Node> to ItemLogger<Node>
    //auto itemLog = dynamic_cast<ItemLogger<Node>*>(logger.get());
    //itemLog->DisplayClusterInfo(manager);
    logger->LogList(nodes);

    return 0;

    ////DisplayClusterInfo(manager);

    //const NodeProvider* nodeProvider = manager.GetNodeProvider();
    //std::list<Node> nodes;
    //nodeProvider->GetClusterNodes(nodes);
    ////DisplayNodes(nodes);

    //const ResourceProvider* resourceProvider = manager.GetResourceProvider();
    //std::list<Resource> resources;
    //resourceProvider->GetClusterResources(resources);

    //for (Resource& res : resources)
    //{
    //    MyDiskInfo diskInfo;
    //    resourceProvider->GetResourceDisksInfo(diskInfo, res);
    //    //DisplayResourceDiskInfo(diskInfo);
    //}
    //DisplayResources(resources);

    //const GroupProvider* groupProvider = manager.GetGroupProvider();
    //std::list<Group> groups;
    //groupProvider->GetClusterGroups(groups);
    //DisplayGroups(groups);

    //std::list<ResourceType> restypes;
    //manager.GetResourceTypes(restypes);
    //DisplayResTypes(restypes);

    //std::list<Network> networks;
    //manager.GetNetworks(networks);
    //DisplayNetworks(networks);

    //std::list<NetInterface> netinterfaces;
    //manager.GetNetInterfaces(netinterfaces);
    //DisplayNetInterfaces(netinterfaces);

    //std::list<SharedVolume> sharedvolumes;
    //manager.GetSharedVolumeList(sharedvolumes);
    //DisplaySharedVolumes(sharedvolumes);

    return 0;
}