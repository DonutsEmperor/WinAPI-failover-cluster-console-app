#include "Manager.h"
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
    const Manager manager(&input);

    const ClusterProvider* clusProvider = manager.GetClusterProvider();
    const ClusterLogger* clusLogger = manager.GetClusterLogger();

    std::wstring cluster;
    clusProvider->GetClusterName(cluster);
    std::wcout << cluster << std::endl;
    clusLogger->DisplayClusterInfo(manager);

    const NodeProvider* nodeProvider = manager.GetNodeProvider();
    const NodeLogger* nodeLogger = manager.GetNodeLogger();
    std::list<Node> nodes;
    nodeProvider->GetAll(nodes);
    nodeLogger->LogListSpecial(nodes);

    const ResourceProvider* resourceProvider = manager.GetResourceProvider();
    const ResourceLogger* resourceLogger = manager.GetResourceLogger();
    std::list<Resource> resources;
    resourceProvider->GetAll(resources);
    resourceLogger->LogListBase(resources);
    resources.clear();

    resourceProvider->GetPhysicalDiskResources(resources);
    for (auto it : resources) {
        resourceLogger->LogBase(it);
        resourceLogger->LogPhysicalDiskInfo(it.diskInfo.get());
    }

    const GroupProvider* groupProvider = manager.GetGroupProvider();
    const GroupLogger* groupLogger = manager.GetGroupLogger();
    std::list<Group> groups;
    groupProvider->GetAll(groups);
    groupLogger->LogListSpecial(groups);

    return 0;

    ////////////// new demo logic 

    std::wcout << "\n New demo logic!!! \n" << std::endl;

    std::wstring newGroupName;
    std::wcin >> newGroupName;

    groupProvider->AddNewGroup(newGroupName, CLUSGROUP_TYPE::ClusGroupTypeVirtualMachine);
    groupProvider->GetAll(groups);
    groupLogger->LogListSpecial(groups);

    return 0; 

    //change this logic
    Group* group = nullptr;
    groupProvider->FindGroupByName(newGroupName, *group);
    groupProvider->DeleteGroup(*group);

    groupProvider->GetAll(groups);
    groupLogger->LogListSpecial(groups);


    return 0;
}