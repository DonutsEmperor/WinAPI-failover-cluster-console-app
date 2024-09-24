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

    DWORD returnedSizeOfBuffer = 0;
    LPVOID buffer = malloc(sizeof(WCHAR) * 1);

    DWORD errorcode = ClusterResourceControl(mPResource, nullptr, CLUSCTL_RESOURCE_GET_RESOURCE_TYPE,
        nullptr, 0, buffer, sizeof(buffer), &returnedSizeOfBuffer);

    /*std::wcout << "Error [" << errorcode << "]" << std::endl;
    std::wcout << "Need bytes [" << returnedSizeOfBuffer << "]" << std::endl;*/

    if (errorcode)
    {
        buffer = realloc(buffer, returnedSizeOfBuffer);
        errorcode = ClusterResourceControl(mPResource, nullptr, CLUSCTL_RESOURCE_GET_RESOURCE_TYPE,
            nullptr, 0, buffer, returnedSizeOfBuffer, &returnedSizeOfBuffer);
    }

    /*std::wcout << "Bytes now [" << returnedSizeOfBuffer << "]" << std::endl;
    std::wcout << "Error [" << errorcode << "]" << std::endl << std::endl;*/

    if (!errorcode && buffer) {
        //std::wcout << "Success!" << std::endl;
        resTypeName = reinterpret_cast<LPCWSTR>(buffer);
    }
    else
    {
        free(buffer);
        CloseClusterResource(mPResource);
        return S_FALSE;
    }

    free(buffer);
    CloseClusterResource(mPResource);
    return S_OK;
}

HRESULT Resource::GetClusterDiskInfo()
{
    mPResource = OpenClusterResource(cluster->mPCluster, properties.itemName.c_str());

    DWORD size = 0;
    LPVOID buffer = malloc(sizeof(CLUSPROP_PARTITION_INFO_EX) * 1);

    DWORD errorcode = ClusterResourceControl(mPResource, nullptr, CLUSCTL_RESOURCE_STORAGE_GET_DISK_INFO_EX,
        nullptr, 0, buffer, sizeof(buffer), &size);

    //std::wcout << "Error [" << errorcode << "]" << std::endl;
    //std::wcout << "Need bytes [" << returnedSizeOfBuffer << "]" << std::endl;

    if (errorcode)
    {
        buffer = (LPVOID)realloc(buffer, size);
        errorcode = ClusterResourceControl(mPResource, nullptr, CLUSCTL_RESOURCE_STORAGE_GET_DISK_INFO_EX,
            nullptr, 0, buffer, size, &size);
    }

    //std::wcout << "Bytes now [" << returnedSizeOfBuffer << "]" << std::endl;
    //std::wcout << "Error [" << errorcode << "]" << std::endl;

    if (errorcode || !buffer)
    {
        free(buffer);
        CloseClusterResource(mPResource);
        return S_FALSE;
    }

    free(buffer);
    CloseClusterResource(mPResource);

    return S_OK;
}