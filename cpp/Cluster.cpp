#include "pch.h"

void Cluster::FetchEnumerations(const DWORD typeofEnum) 
{
    HCLUSENUMEX hClusterEnum = ClusterOpenEnumEx(mPCluster, typeofEnum, nullptr);
    DWORD objectErrorCode;

    LPDWORD itemSize = new DWORD(1);
    PCLUSTER_ENUM_ITEM pItem = (PCLUSTER_ENUM_ITEM)malloc(*itemSize);
    DWORD enumLength = ClusterGetEnumCountEx(hClusterEnum), iterator = 0;

    while (iterator < enumLength) 
    {
        objectErrorCode = ClusterEnumEx(hClusterEnum, iterator++, pItem, itemSize);

        if (objectErrorCode == ERROR_SUCCESS) 
        {
            switch (typeofEnum) 
            {
                case CLUSTER_ENUM_NODE: 
                    HandleNode(pItem); break;
                case CLUSTER_ENUM_GROUP: 
                    HandleGroup(pItem); break;
                case CLUSTER_ENUM_RESOURCE: 
                    HandleResource(pItem); break;
                case CLUSTER_ENUM_RESTYPE: 
                    HandleResType(pItem); break;
                case CLUSTER_ENUM_NETWORK: 
                    HandleNetwork(pItem); break;
                case CLUSTER_ENUM_NETINTERFACE: 
                    HandleNetInterface(pItem); break;
                case CLUSTER_ENUM_SHARED_VOLUME_RESOURCE: 
                    HandleSharedVolume(pItem); break;
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

void Cluster::HandleNode(const PCLUSTER_ENUM_ITEM pItem) 
{
    Node node(this, pItem);
    mNodes.push_back(node);
}

void Cluster::HandleGroup(const PCLUSTER_ENUM_ITEM pItem)
{
    Group group(this, pItem);
    mGroups.push_back(group);
}

void Cluster::HandleResource(const PCLUSTER_ENUM_ITEM pItem)
{
    Resource resource(this, pItem);
    mResources.push_back(resource);
}

void Cluster::HandleResType(const PCLUSTER_ENUM_ITEM pItem)
{
    ResourceType restype(this, pItem);
    mResTypes.push_back(restype);
}

void Cluster::HandleNetwork(const PCLUSTER_ENUM_ITEM pItem)
{
    Network network(this, pItem);
    mNetworks.push_back(network);
}

void Cluster::HandleNetInterface(const PCLUSTER_ENUM_ITEM pItem)
{
    NetInterface netinterface(this, pItem);
    mNetInterfaces.push_back(netinterface);
}

void Cluster::HandleSharedVolume(const PCLUSTER_ENUM_ITEM pItem)
{
    SharedVolume sharedvolume(this, pItem);
    mCSVs.push_back(sharedvolume);
}