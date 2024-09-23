#include <windows.h>
#include <iostream>
#include "ClusAPI.h"

class ClusObject; class Node; class Resource; class Group;
class SharedVolume; class Network; class NetInterface; class ResType;

typedef class Cluster* PCluster;

class Cluster 
{
public:
    const HCLUSTER mPCluster;
    const std::wstring mCName;

    //items containers
    std::list<Node> mNodes;
    std::list<Group> mGroups;
    std::list<Resource> mResources;
    std::list<ResType> mResTypes;
    std::list<Network> mNetworks;
    std::list<NetInterface> mNetInterfaces;
    std::list<SharedVolume> mCSVs;

    Cluster(const HCLUSTER pCluster, std::wstring clusterName)
        : mPCluster(pCluster), mCName(clusterName) 
    {
        fetchItemsWithType(CLUSTER_ENUM_NODE);
        fetchItemsWithType(CLUSTER_ENUM_GROUP);
        fetchItemsWithType(CLUSTER_ENUM_RESOURCE);
        fetchItemsWithType(CLUSTER_ENUM_RESTYPE);
        fetchItemsWithType(CLUSTER_ENUM_NETWORK);
        fetchItemsWithType(CLUSTER_ENUM_NETINTERFACE);
        fetchItemsWithType(CLUSTER_ENUM_SHARED_VOLUME_RESOURCE);
    }
    ~Cluster() {
        CloseCluster(mPCluster);
    }

private:
    void fetchItemsWithType(const DWORD typeofEnum);
};


struct ClusObjProperties
{
    DWORD version;
    DWORD type;
    DWORD byteSizeId;
    std::wstring itemId;
    DWORD byteSizeName;
    std::wstring itemName;

    ClusObjProperties() : version(0), type(0), byteSizeId(0), byteSizeName(0) {}

    ClusObjProperties(const CLUSTER_ENUM_ITEM& winStruct) 
        : version(winStruct.dwVersion), type(winStruct.dwType),  byteSizeId(winStruct.cbId), byteSizeName(winStruct.cbName)
    {
        itemId = winStruct.lpszId;
        itemName = winStruct.lpszName;
    }
};


class ClusObject {
protected:
    DWORD mErrorHandler;
public:
    PCluster cluster;
    ClusObjProperties properties;

    ClusObject(const PCluster hCluster, const PCLUSTER_ENUM_ITEM lProperties)
        : cluster(hCluster), properties(*lProperties), mErrorHandler(0) {}
};

class Node : public ClusObject
{
    HNODE mPNode;
public:
    CLUSTER_NODE_STATE state;

    Node(const PCluster pCluster, const PCLUSTER_ENUM_ITEM pWinStruct) : ClusObject(pCluster, pWinStruct)
    {
        mPNode = OpenClusterNode(pCluster->mPCluster, pWinStruct->lpszName);
        state = GetClusterNodeState(mPNode);
    }
    ~Node() {
        CloseClusterNode(mPNode);
    }
};

class Group : public ClusObject
{
    HGROUP mPGroup;
public:
    std::wstring csvName;

    Group(const PCluster pCluster, const PCLUSTER_ENUM_ITEM pWinStruct) : ClusObject(pCluster, pWinStruct)
    {
        mPGroup = OpenClusterGroup(pCluster->mPCluster, pWinStruct->lpszName);
    }
    ~Group() {
        CloseClusterGroup(mPGroup);
    }
};

class Resource : public ClusObject
{
    HRESOURCE mPResource;

public:
    std::wstring resTypeName;

    Resource(const PCluster pCluster, const PCLUSTER_ENUM_ITEM pWinStruct) : ClusObject(pCluster, pWinStruct)
    {
        mErrorHandler = GetClusterType();
    }
    ~Resource() {}
    HRESULT GetClusterType();
};

class ResType : public ClusObject
{
public:
    ResType(const PCluster pCluster, const PCLUSTER_ENUM_ITEM pWinStruct) : ClusObject(pCluster, pWinStruct) { }
    ~ResType() {}
};


class Network : public ClusObject
{
public:
    Network(const PCluster pCluster, const PCLUSTER_ENUM_ITEM pWinStruct) : ClusObject(pCluster, pWinStruct) { }
    ~Network() {}
};


class NetInterface : public ClusObject
{
public:
    NetInterface(const PCluster pCluster, const PCLUSTER_ENUM_ITEM pWinStruct) : ClusObject(pCluster, pWinStruct) { }
    ~NetInterface() {}
};

class SharedVolume : public ClusObject
{
public:
    SharedVolume(const PCluster pCluster, const PCLUSTER_ENUM_ITEM pWinStruct) : ClusObject(pCluster, pWinStruct) { }
    ~SharedVolume() {}
};