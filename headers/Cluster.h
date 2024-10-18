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

#include "Properties.h"
#include "BaseObject.h"

class Cluster {
public:
    const HCLUSTER mHandler;
    const std::wstring mCName;

    // Containers for cluster items
    std::list<Node> mNodes;
    std::list<Group> mGroups;
    std::list<Resource> mResources;
    std::list<ResourceType> mResTypes;
    std::list<Network> mNetworks;
    std::list<NetInterface> mNetInterfaces;
    std::list<SharedVolume> mCSVs;

    Cluster() = default;
    Cluster(const HCLUSTER, const std::wstring&);
    ~Cluster();

    void UpdateLists();
    void UpdateSpecificList(const DWORD);
private:
    void ClearLists();
    void ClearSpecificList(const DWORD);
    void FetchEnumerations(const DWORD);

    void HandleNode(PCLUSTER_ENUM_ITEM );
    void HandleGroup(PCLUSTER_ENUM_ITEM );
    void HandleResource(PCLUSTER_ENUM_ITEM );
    void HandleResType(PCLUSTER_ENUM_ITEM );
    void HandleNetwork(PCLUSTER_ENUM_ITEM );
    void HandleNetInterface(PCLUSTER_ENUM_ITEM );
    void HandleSharedVolume(PCLUSTER_ENUM_ITEM );
};

#include "Node.h"
#include "Resource.h"
#include "Group.h"

// Cluster-specific classes
class ResourceType : public BaseObject {
public:
    ResourceType(PCluster pCluster, PCLUSTER_ENUM_ITEM pWinStruct)
        : BaseObject(pCluster, pWinStruct) {}
protected:
    HRESULT OpenHandler() override { return S_OK; }
    HRESULT CloseHandler() override { return S_OK; }
};

class Network : public BaseObject {
public:
    Network(PCluster pCluster, PCLUSTER_ENUM_ITEM pWinStruct)
        : BaseObject(pCluster, pWinStruct) {}
protected:
    HRESULT OpenHandler() override { return S_OK; }
    HRESULT CloseHandler() override { return S_OK; }
};

class NetInterface : public BaseObject {
public:
    NetInterface(PCluster pCluster, PCLUSTER_ENUM_ITEM pWinStruct)
        : BaseObject(pCluster, pWinStruct) {}
protected:
    HRESULT OpenHandler() override { return S_OK; }
    HRESULT CloseHandler() override { return S_OK; }
};

class SharedVolume : public BaseObject {
public:
    SharedVolume(PCluster pCluster, PCLUSTER_ENUM_ITEM pWinStruct)
        : BaseObject(pCluster, pWinStruct) {}
protected:
    HRESULT OpenHandler() override { return S_OK; }
    HRESULT CloseHandler() override { return S_OK; }
};