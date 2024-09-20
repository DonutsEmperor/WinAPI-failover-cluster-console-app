#include <windows.h>
#include <iostream>
#include "ClusAPI.h"

class ClusObject;
class Node; class Resource; class Group;

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

    Cluster(const HCLUSTER pCluster, std::wstring clusterName)
        : mPCluster(pCluster), mCName(clusterName) {

        fetchAnyItems(CLUSTER_ENUM_NODE);
        /*fetchAnyItems(CLUSTER_ENUM_GROUP);
        fetchAnyItems(CLUSTER_ENUM_RESOURCE);
        fetchAnyItems(CLUSTER_ENUM_RESTYPE);
        fetchAnyItems(CLUSTER_ENUM_SHARED_VOLUME_GROUP);
        fetchAnyItems(CLUSTER_ENUM_SHARED_VOLUME_RESOURCE);*/
    }
    ~Cluster() {
        CloseCluster(mPCluster);
    }

private:
    void fetchAnyItems(const int typeofEnum);
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
    std::wstring csvName;

    Resource(const PCluster pCluster, const PCLUSTER_ENUM_ITEM pWinStruct) : ClusObject(pCluster, pWinStruct)
    {
        mPResource = OpenClusterResource(pCluster->mPCluster, pWinStruct->lpszName);
    }
    ~Resource() {
        CloseClusterResource(mPResource);
    }
};