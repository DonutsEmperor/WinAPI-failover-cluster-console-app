#include <windows.h>
#include <iostream>
#include "ClusAPI.h"

class ClusterObject;
class Node; class Resource; class Group;

class Cluster 
{
public:
    const HCLUSTER m_pCluster;
    std::wstring m_clusterName;

    //items containers
    std::list<Node> m_nodes;
    std::list<Group> m_groups;
    std::list<Resource> m_resourses;

    Cluster(const HCLUSTER pCluster, std::wstring clusterName)
        : m_pCluster(pCluster), m_clusterName(clusterName) {

        fetchAnyItems(CLUSTER_ENUM_NODE);
        fetchAnyItems(CLUSTER_ENUM_GROUP);
        fetchAnyItems(CLUSTER_ENUM_RESOURCE);
        //fetchAnyItems(CLUSTER_ENUM_RESTYPE);
        //fetchAnyItems(CLUSTER_ENUM_SHARED_VOLUME_GROUP);
        //fetchAnyItems(CLUSTER_ENUM_SHARED_VOLUME_RESOURCE);
    }
    ~Cluster() {
        CloseCluster(m_pCluster); // be or not to be
    }

private:
    void fetchAnyItems(const int typeofEnum);
};


struct ClusterEnumProperties
{
    DWORD version;
    DWORD type;
    DWORD byteSizeId;
    std::wstring itemId;
    DWORD byteSizeName;
    std::wstring itemName;

    ClusterEnumProperties() : version(0), type(0), byteSizeId(0), byteSizeName(0) {}
    ClusterEnumProperties(const CLUSTER_ENUM_ITEM& winStruct)
    {
        version = winStruct.dwVersion;
        type = winStruct.dwType;

        byteSizeId = winStruct.cbId;
        itemId = winStruct.lpszId;
        
        byteSizeName = winStruct.cbName;
        itemName = winStruct.lpszName;
    }
    ~ClusterEnumProperties() {}

    ClusterEnumProperties& operator=(const ClusterEnumProperties& other)
    {
        if (this != &other) {
            version = other.version;
            type = other.type;
            byteSizeId = other.byteSizeId;
            itemId = other.itemId;
            byteSizeName = other.byteSizeName;
            itemName = other.itemName;
        }
        return *this;
    }
};


class ClusterObject {
protected:
    DWORD m_errorHandler;
public:
    const Cluster* cluster;
    const ClusterEnumProperties properties;

    ClusterObject(const Cluster* hCluster, const PCLUSTER_ENUM_ITEM lProperties)
        : cluster(hCluster), properties(*lProperties), m_errorHandler(0) {}
    ~ClusterObject() {}
};

class Node : public ClusterObject
{
    HNODE m_pNode;
public:
    CLUSTER_NODE_STATE state;

    Node(const Cluster* pCluster, const PCLUSTER_ENUM_ITEM pWinStruct) : ClusterObject(pCluster, pWinStruct)
    {
        m_pNode = OpenClusterNode(pCluster->m_pCluster, pWinStruct->lpszName);
        state = GetClusterNodeState(m_pNode);
    }
    ~Node() {
        CloseClusterNode(m_pNode);
    }
};

class Group : public ClusterObject
{
    HGROUP m_pGroup;
public:
    std::wstring csvName; // shared volume
    //CLUSTER_GROUP_STATE state;

    Group(const Cluster* pCluster, const PCLUSTER_ENUM_ITEM pWinStruct) : ClusterObject(pCluster, pWinStruct)
    {
        m_pGroup = OpenClusterGroup(pCluster->m_pCluster, pWinStruct->lpszName);
        //state = GetClusterGroupState(m_pGroup...);
    }
    ~Group() {
        CloseClusterGroup(m_pGroup);
    }
};

class Resource : public ClusterObject
{
    HRESOURCE m_pResource;
public:
    std::wstring resTypeName;
    std::wstring csvName; // shared volume

    //CLUSTER_GROUP_STATE state;

    Resource(const Cluster* pCluster, const PCLUSTER_ENUM_ITEM pWinStruct) : ClusterObject(pCluster, pWinStruct)
    {
        m_pResource = OpenClusterResource(pCluster->m_pCluster, pWinStruct->lpszName);
        //state = GetClusterGroupState(m_pGroup...);
    }

    ~Resource() {
        CloseClusterResource(m_pResource);
    }
};