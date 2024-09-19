#include <windows.h>

#include <list>
#include <iterator>

#include <iostream>
#include <fcntl.h>
#include <io.h>

#include "ClusAPI.h"
#include "cluadmex.h"
#include "interfaces.h"

#pragma comment(lib, "ClusAPI.lib")

// Define fetchNodes function after the Node class has been declared
void Cluster::fetchAnyItems(const int typeofEnum)
{
    HCLUSENUMEX hClusterEnum = ClusterOpenEnumEx(m_pCluster, typeofEnum, PVOID(NULL));
    DWORD objectErrorCode;

    PCLUSTER_ENUM_ITEM pItem = new CLUSTER_ENUM_ITEM();
    LPDWORD itemSize = new DWORD(1);

    int enumLenght = ClusterGetEnumCountEx(hClusterEnum), iterator = 0;

    std::wcout << "Item count enum   [" << enumLenght << "]\n";

    while (iterator < enumLenght)
    {
        std::wcout << "Current item: " << iterator << "\n" << std::endl;
        /*std::wcout << "Bytes has in struct [" << sizeof(*pItem) << "]" << std::endl;
        std::wcout << "Bytes has           [" << sizeof(pItem) << "]" << std::endl;
        std::wcout << "Bytes size          [" << *itemSize << "]" << std::endl;*/

        objectErrorCode = ClusterEnumEx(hClusterEnum, iterator++, pItem, itemSize);

        /*std::wcout << "Item with Type    [" << pItem->dwType << "]\n";
        std::wcout << "Item name         [" << pItem->lpszName << "]\n";
        std::wcout << "Bytes needs         [" << *itemSize << "]\n" << std::endl;*/
        
        if (objectErrorCode == ERROR_SUCCESS)
        {
            std::wcout << "ERROR_SUCCESS" << "\n" << std::endl;

            switch (typeofEnum)
            {
                case CLUSTER_ENUM_NODE: 
                    {
                        Node node(this, pItem);
                        m_nodes.push_back(node);
                    }
                    break;

                case CLUSTER_ENUM_GROUP: 
                    {
                        Group group(this, pItem);
                        m_groups.push_back(group);
                    }
                    break;

                case CLUSTER_ENUM_RESOURCE:
                {
                    Resource resource(this, pItem);
                    m_resourses.push_back(resource);
                }
                    break;

                case CLUSTER_ENUM_RESTYPE:
                {
                    if (m_resourses.empty()) break;

                    std::list<Resource>::iterator resIter = std::next(m_resourses.begin(), iterator);
                    resIter->resTypeName = pItem->lpszName;
                }
                    break;

                case CLUSTER_ENUM_SHARED_VOLUME_GROUP:
                {
                    if (m_groups.empty()) break;

                    std::list<Group>::iterator groupIter = std::next(m_groups.begin(), iterator);
                    groupIter->csvName = pItem->lpszName;
                }
                    break;

                case CLUSTER_ENUM_SHARED_VOLUME_RESOURCE:
                {
                    if (m_resourses.empty()) break;
                    
                    std::list<Resource>::iterator resIter = std::next(m_resourses.begin(), iterator);
                    resIter->csvName = pItem->lpszName;
                }
                    break;

                default:
                    break;
            }

            //*itemSize = initialNameSize;
            continue;
        }
        else if (objectErrorCode == ERROR_MORE_DATA)
        {
            std::wcout << "ERROR_MORE_DATA !!!" << std::endl << std::endl;

            //*itemSize += initialNameSize;
            //memset(pItem, 0, sizeof(*pItem));
            iterator--;
            continue;
        }

        std::wcout << "ERROR_NO_MORE_ITEMS" << "\n" << std::endl;
        break;
    }

    std::wcout << "FINISH TRACK THE CHAR ISSUE!!!" << std::endl << std::endl;

    delete itemSize, pItem;
    ClusterCloseEnumEx(hClusterEnum);
}

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

    return 0;

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