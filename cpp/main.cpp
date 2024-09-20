#include <windows.h>

#include <list>
#include <iterator>

#include <iostream>
#include <fcntl.h>
#include <io.h>

#include "ClusAPI.h"
#include "cluadmex.h"
#include "..//headers/interfaces.h"

#pragma comment(lib, "ClusAPI.lib")

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);

    //  information about cluster
    std::wcout << "Hello Enter ClusterNodeName!\n";

    std::wstring input;

    std::wcin >> input;
    std::wcout << "You've entered in cluster: [" << input << "]!\n";

    GetClusterDataInfo clusData(input);

    HCLUSTER hCluster = clusData.GetClusterHandle();
    LPWSTR clusterName = new WCHAR[64];
    LONG* clusterNameSize = new LONG(1);

    clusData.GetClusterName(clusterName, clusterNameSize);

    std::wcout << "Handle       [" << hCluster << "]\n";
    std::wcout << "Cluster Name [" << clusterName << "]\n";
    std::wcout << "Name Size    [" << *clusterNameSize << "]\n" << std::endl;

    //  information about cluster state (to be 19)

    DWORD state = 0;
    clusData.GetClusterState(state);

    std::wcout << "Cluster state[" << state << "]. Must be 19\n" << std::endl;

    //  information about nodes ///////////////////////////////////////////////////

    std::list<Node> nodes;
    clusData.GetClusterNodes(&nodes);

    std::wcout << "Start iteration of nodes! \n" << std::endl;
    // trying to iterate list of obtained nodes

    for (Node& node : nodes)
    {
        std::wcout << "Node Id   [" << node.properties.itemId << "]\n";
        std::wcout << "Node Name [" << node.properties.itemName << "]\n";
        std::wcout << "Name Size [" << node.properties.byteSizeName << "]\n" << std::endl;
    }

    std::wcout << "Finish! \n" << std::endl;

    //  information about resources ///////////////////////////////////////////////////

    std::list<Resource> resources;
    clusData.GetClusterResources(&resources);

    std::wcout << "Start iteration of resources! \n" << std::endl;
    // trying to iterate list of obtained resources

    for (Resource& resource : resources)
    {
        std::wcout << "Resource Name [" << resource.properties.itemName << "]\n";
        std::wcout << "Resource ResType [" << resource.resTypeName << "]\n";
        //std::wcout << "Resource CsvName? [" << resource.csvName << "]\n" << std::endl;
    }

    std::wcout << "Finish! \n" << std::endl;

    //  information about groups ///////////////////////////////////////////////////

    std::list<Group> groups;
    clusData.GetClusterGroups(&groups);

    std::wcout << "Start iteration of groups! \n" << std::endl;
    // trying to iterate list of obtained groups

    for (Group& group : groups)
    {
        std::wcout << "Group Name [" << group.properties.itemName << "] \n";
        //std::wcout << "Group CsvName? [" << group.csvName << "]\n" << std::endl;
    }

    std::wcout << "Finish! \n" << std::endl;

    delete[] clusterName;
    delete clusterNameSize;

    return 0;
}