#include <list>
#include "..//headers/classes.h"

// Define fetchNodes function after the Node class has been declared
void Cluster::fetchAnyItems(const int typeofEnum)
{
    HCLUSENUMEX hClusterEnum = ClusterOpenEnumEx(mPCluster, typeofEnum, PVOID(NULL));
    DWORD objectErrorCode;

    PCLUSTER_ENUM_ITEM pItem = new CLUSTER_ENUM_ITEM();
    LPDWORD itemSize = new DWORD(1);

    DWORD enumLenght = ClusterGetEnumCountEx(hClusterEnum), iterator = 0;

    std::wcout << "Item count enum   [" << enumLenght << "]\n";

    while (iterator < enumLenght)
    {
        std::wcout << "Current item: " << iterator << "\n" << std::endl;
        std::wcout << "Bytes has in struct [" << sizeof(*pItem) << "]" << std::endl;
        std::wcout << "Bytes has           [" << sizeof(pItem) << "]" << std::endl;
        std::wcout << "Bytes size          [" << *itemSize << "]" << std::endl;

        objectErrorCode = ClusterEnumEx(hClusterEnum, iterator++, pItem, itemSize);

        std::wcout << "Item with Type    [" << pItem->dwType << "]\n";
        std::wcout << "Item name         [" << pItem->lpszName << "]\n";
        std::wcout << "Bytes needs       [" << *itemSize << "]\n" << std::endl;

        if (objectErrorCode == ERROR_SUCCESS)
        {
            std::wcout << "ERROR_SUCCESS" << "\n" << std::endl;

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
            }

            memset(pItem, 0, sizeof(*pItem));
            continue;
        }
        else if (objectErrorCode == ERROR_MORE_DATA)
        {
            std::wcout << "ERROR_MORE_DATA !!!" << std::endl << std::endl;
            memset(pItem, 0, sizeof(*pItem)); iterator--;
            continue;
        }

        std::wcout << "ERROR_NO_MORE_ITEMS" << "\n" << std::endl;
        break;
    }

    std::wcout << "Finished enumerating items!" << std::endl << std::endl;

    delete itemSize; delete pItem;
    ClusterCloseEnumEx(hClusterEnum);
}