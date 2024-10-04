#pragma once

#include <list>
#include <windows.h>
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <string>
#include <variant>
#include <vector>
#include <functional>

#include "ClusApi.h"

class Cluster;
typedef Cluster* PCluster;

class Resource; class Node; class Group;
class SharedVolume; class Network; class NetInterface; class ResourceType;

#include "ClusterObjectProps.h"
#include "ClusterObject.h"

class Cluster {
public:
    const HCLUSTER mPCluster;
    const std::wstring mCName;

    // Containers for cluster items
    std::list<Node> mNodes;
    std::list<Group> mGroups;
    std::list<Resource> mResources;
    std::list<ResourceType> mResTypes;
    std::list<Network> mNetworks;
    std::list<NetInterface> mNetInterfaces;
    std::list<SharedVolume> mCSVs;

    Cluster(const HCLUSTER pCluster, const std::wstring& clusterName)
        : mPCluster(pCluster), mCName(clusterName) {
        FetchEnumerations(CLUSTER_ENUM_NODE);
        FetchEnumerations(CLUSTER_ENUM_GROUP);
        FetchEnumerations(CLUSTER_ENUM_RESOURCE);
        FetchEnumerations(CLUSTER_ENUM_RESTYPE);
        FetchEnumerations(CLUSTER_ENUM_NETWORK);
        FetchEnumerations(CLUSTER_ENUM_NETINTERFACE);
        FetchEnumerations(CLUSTER_ENUM_SHARED_VOLUME_RESOURCE);
    }

    ~Cluster() {
        CloseCluster(mPCluster);
    }

private:
    void FetchEnumerations(const DWORD typeofEnum);

    void HandleNode(PCLUSTER_ENUM_ITEM pItem);
    void HandleGroup(PCLUSTER_ENUM_ITEM pItem);
    void HandleResource(PCLUSTER_ENUM_ITEM pItem);
    void HandleResType(PCLUSTER_ENUM_ITEM pItem);
    void HandleNetwork(PCLUSTER_ENUM_ITEM pItem);
    void HandleNetInterface(PCLUSTER_ENUM_ITEM pItem);
    void HandleSharedVolume(PCLUSTER_ENUM_ITEM pItem);
};

#include "Node.h"
#include "Resource.h"
#include "Group.h"

// Cluster-specific classes
class ResourceType : public ClusterObject {
public:
    ResourceType(PCluster pCluster, PCLUSTER_ENUM_ITEM pWinStruct)
        : ClusterObject(pCluster, pWinStruct) {}
};

class Network : public ClusterObject {
public:
    Network(PCluster pCluster, PCLUSTER_ENUM_ITEM pWinStruct)
        : ClusterObject(pCluster, pWinStruct) {}
};

class NetInterface : public ClusterObject {
public:
    NetInterface(PCluster pCluster, PCLUSTER_ENUM_ITEM pWinStruct)
        : ClusterObject(pCluster, pWinStruct) {}
};

class SharedVolume : public ClusterObject {
public:
    SharedVolume(PCluster pCluster, PCLUSTER_ENUM_ITEM pWinStruct)
        : ClusterObject(pCluster, pWinStruct) {}
};