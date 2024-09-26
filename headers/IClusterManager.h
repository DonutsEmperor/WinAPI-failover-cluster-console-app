#pragma once

#include "Cluster.h"
#include "IGroupProvider.h"
#include "IResourceProvider.h"
#include "INodeProvider.h"

class IClusterManager 
{
public:
    virtual ~IClusterManager() {}
    virtual HRESULT MyOpenCluster(const std::wstring&) = 0;
    virtual void MyCloseCluster() const = 0;
    virtual HCLUSTER GetClusterHandle() const = 0;
    virtual HRESULT GetClusterName(std::wstring&) const = 0;
    virtual HRESULT GetClusterState(DWORD*) const = 0;

    virtual HRESULT GetResourceTypes(std::list<ResourceType>&) const = 0;
    virtual HRESULT GetNetworks(std::list<Network>&) const = 0;
    virtual HRESULT GetNetInterfaces(std::list<NetInterface>&) const = 0;
    virtual HRESULT GetSharedVolumeList(std::list<SharedVolume>&) const = 0;

private:
    virtual HRESULT InitProviders() = 0;
};

//class ClusterManager;

