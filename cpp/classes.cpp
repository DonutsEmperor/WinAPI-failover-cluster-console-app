#include <list>
#include "..//headers/classes.h"

// Define fetchNodes function after the Node class has been declared
void Cluster::fetchItemsWithType(const DWORD typeofEnum)
{
    HCLUSENUMEX hClusterEnum = ClusterOpenEnumEx(mPCluster, typeofEnum, nullptr);
    DWORD objectErrorCode;

    LPDWORD itemSize = new DWORD(1);
    PCLUSTER_ENUM_ITEM pItem = (PCLUSTER_ENUM_ITEM)malloc(*itemSize);

    DWORD enumLenght = ClusterGetEnumCountEx(hClusterEnum), iterator = 0;

    while (iterator < enumLenght)
    {
        objectErrorCode = ClusterEnumEx(hClusterEnum, iterator++, pItem, itemSize);

        if (objectErrorCode == ERROR_SUCCESS)
        {
            switch (typeofEnum)
            {
                case CLUSTER_ENUM_NODE:
                {
                    Node node(this, pItem);
                    mNodes.push_back(node);
                }
                break;

                case CLUSTER_ENUM_GROUP:
                {
                    Group group(this, pItem);
                    mGroups.push_back(group);
                }
                break;

                case CLUSTER_ENUM_RESOURCE:
                {
                    Resource resource(this, pItem);
                    mResources.push_back(resource);
                }
                break;

                case CLUSTER_ENUM_RESTYPE:
                {
                    std::wcout << pItem->lpszName << std::endl;
                }
                break;

                case CLUSTER_ENUM_SHARED_VOLUME_GROUP:
                {
                    std::wcout << pItem->lpszName << std::endl;
                }
                break;

                case CLUSTER_ENUM_SHARED_VOLUME_RESOURCE:
                {
                    std::wcout << pItem->lpszName << std::endl;
                }
                break;
            }
            continue;
        }
        else if (objectErrorCode == ERROR_MORE_DATA)
        {
            pItem = (PCLUSTER_ENUM_ITEM)realloc(pItem, *itemSize);
            iterator--;

            continue;
        }
        break;
    }

    delete itemSize;
    free(pItem);

    ClusterCloseEnumEx(hClusterEnum);
}


