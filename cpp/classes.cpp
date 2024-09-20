#include <list>
#include "..//headers/classes.h"

// Define fetchNodes function after the Node class has been declared
void Cluster::fetchAnyItems(const int typeofEnum)
{
    HCLUSENUMEX hClusterEnum = ClusterOpenEnumEx(m_pCluster, typeofEnum, PVOID(NULL));
    DWORD objectErrorCode;

    PCLUSTER_ENUM_ITEM pItem = new CLUSTER_ENUM_ITEM();
    LPDWORD itemSize = new DWORD(1);

    int enumLenght = ClusterGetEnumCountEx(hClusterEnum), iterator = 0;

    //std::wcout << "Item count enum   [" << enumLenght << "]\n";

    while (iterator < enumLenght)
    {
        std::wcout << "Current item: " << iterator << "\n" << std::endl;
        /*std::wcout << "Bytes has in struct [" << sizeof(*pItem) << "]" << std::endl;
        std::wcout << "Bytes has           [" << sizeof(pItem) << "]" << std::endl;
        std::wcout << "Bytes size          [" << *itemSize << "]" << std::endl;*/

        objectErrorCode = ClusterEnumEx(hClusterEnum, iterator++, pItem, itemSize);

        /*std::wcout << "Item with Type    [" << pItem->dwType << "]\n";
        std::wcout << "Item name           [" << pItem->lpszName << "]\n";
        std::wcout << "Bytes needs         [" << *itemSize << "]\n" << std::endl;*/

        if (objectErrorCode == ERROR_SUCCESS)
        {
            //std::wcout << "ERROR_SUCCESS" << "\n" << std::endl;

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
                std::wcout << pItem->lpszName << std::endl;

                /*if (m_resourses.empty()) break;
                std::list<Resource>::iterator resIter = std::next(m_resourses.begin(), iterator);
                resIter->resTypeName = pItem->lpszName;*/
            }
            break;

            case CLUSTER_ENUM_SHARED_VOLUME_GROUP:
            {
                std::wcout << pItem->lpszName << std::endl;

               /* if (m_groups.empty()) break;
                std::list<Group>::iterator groupIter = std::next(m_groups.begin(), iterator);
                groupIter->csvName = pItem->lpszName;*/
            }
            break;

            case CLUSTER_ENUM_SHARED_VOLUME_RESOURCE:
            {
                std::wcout << pItem->lpszName << std::endl;

                /*if (m_resourses.empty()) break;
                std::list<Resource>::iterator resIter = std::next(m_resourses.begin(), iterator);
                resIter->csvName = pItem->lpszName;*/
            }
            break;

            default:
                break;
            }

            memset(pItem, 0, sizeof(*pItem));
            continue;
        }
        else if (objectErrorCode == ERROR_MORE_DATA)
        {
            //std::wcout << "ERROR_MORE_DATA !!!" << std::endl << std::endl;

            memset(pItem, 0, sizeof(*pItem)); iterator--;
            continue;
        }

        //std::wcout << "ERROR_NO_MORE_ITEMS" << "\n" << std::endl;
        break;
    }

    //std::wcout << "FINISH TRACK THE CHAR ISSUE!!!" << std::endl << std::endl;

    delete itemSize, pItem;
    ClusterCloseEnumEx(hClusterEnum);
}