#pragma once

#include "Cluster.h"
#include "IClusterProvider.h"
#include "IGroupProvider.h"
#include "IResourceProvider.h"
#include "INodeProvider.h"

class IClusterManager 
{
public:
    virtual ~IClusterManager() {};
    virtual void MyOpenCluster(const std::wstring&) = 0;

    virtual const IClusterProvider* GetClusterProvider() const = 0;
    virtual const INodeProvider* GetNodeProvider() const = 0;
    virtual const IResourceProvider* GetResourceProvider() const = 0;
    virtual const IGroupProvider* GetGroupProvider() const = 0;

    virtual HRESULT GetResourceTypes(std::list<ResourceType>&) const = 0;
    virtual HRESULT GetNetworks(std::list<Network>&) const = 0;
    virtual HRESULT GetNetInterfaces(std::list<NetInterface>&) const = 0;
    virtual HRESULT GetSharedVolumeList(std::list<SharedVolume>&) const = 0;

private:
    virtual void MyCloseCluster() const = 0;
    virtual void InitProviders() = 0;
};

