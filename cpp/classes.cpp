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
                    ResType restype(this, pItem);
                    mResTypes.push_back(restype);
                }
                break;

                case CLUSTER_ENUM_NETWORK:
                {
                    Network network(this, pItem);
                    mNetworks.push_back(network);
                }
                break;

                case CLUSTER_ENUM_NETINTERFACE:
                {
                    NetInterface netinterface(this, pItem);
                    mNetInterfaces.push_back(netinterface);
                }
                break;

                case CLUSTER_ENUM_SHARED_VOLUME_RESOURCE:
                {
                    SharedVolume sharedvolume(this, pItem);
                    mCSVs.push_back(sharedvolume);
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

HRESULT Resource::GetClusterType() 
{
    mPResource = OpenClusterResource(cluster->mPCluster, properties.itemName.c_str());

    DWORD initialSizeOfBuffer = 64, returnedSizeOfBuffer = 0;
    LPVOID buffer = malloc(sizeof(WCHAR) * initialSizeOfBuffer);

    DWORD errorcode = ClusterResourceControl(mPResource, nullptr, CLUSCTL_RESOURCE_GET_RESOURCE_TYPE, nullptr, 0, buffer, initialSizeOfBuffer, &returnedSizeOfBuffer);

    /*std::wcout << "Error [" << errorcode << "]" << std::endl;
    std::wcout << "Need bytes [" << returnedSizeOfBuffer << "]" << std::endl;*/

    if (returnedSizeOfBuffer > initialSizeOfBuffer)
    {
        buffer = realloc(buffer, returnedSizeOfBuffer);
        DWORD errorcode = ClusterResourceControl(mPResource, nullptr, CLUSCTL_RESOURCE_GET_RESOURCE_TYPE, nullptr, 0, buffer, returnedSizeOfBuffer, &returnedSizeOfBuffer);
    }

    //std::wcout << "Bytes now [" << returnedSizeOfBuffer << "]" << std::endl;

    if (buffer) {
        //std::wcout << "Success!" << std::endl;
        resTypeName = reinterpret_cast<LPCWSTR>(buffer);
    }
    else
        return S_FALSE;

    free(buffer);
    CloseClusterResource(mPResource);

    return S_OK;
}


