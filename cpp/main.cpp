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
    std::wcout << "Hello Enter ClusterNodeName!" << std::endl;
    std::wstring input;
    std::wcin >> input;
    std::wcout << "You've entered in cluster: [" << input << "]!" << std::endl;
    return input;
}

int main() 
{
    SetConsoleMode();

    std::wstring input = GetClusterNodeName();

    const ClusterManager manager(&input);
    const LoggerFactory* logFactory = manager.GetLoggerFactory();

    const NodeProvider* nodeProvider = manager.GetNodeProvider();
    std::list<Node> nodes;
    nodeProvider->GetClusterNodes(nodes);
    auto loggerNodes = logFactory->CreateLogger<Node>();
    loggerNodes->DisplayClusterInfo(manager);
    loggerNodes->LogList(nodes);

    const ResourceProvider* resProvider = manager.GetResourceProvider();
    std::list<Resource> resources;
    resProvider->GetClusterResources(resources);
    auto loggerRes = logFactory->CreateLogger<Resource>();
    loggerRes->LogList(resources);

    const GroupProvider* groupProvider = manager.GetGroupProvider();
    std::list<Group> groups;
    groupProvider->GetClusterGroups(groups);
    auto loggerGroups = logFactory->CreateLogger<Group>();
    loggerGroups->LogList(groups);

    return 0;
}