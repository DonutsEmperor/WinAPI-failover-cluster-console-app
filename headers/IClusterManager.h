#pragma once

#include "Cluster.h"
#include "IClusterProvider.h"
#include "IGroupProvider.h"
#include "IResourceProvider.h"
#include "INodeProvider.h"

class IClusterManager 
{
public:
    virtual ~IClusterManager() {}

    virtual const ClusterProvider* GetClusterProvider() const = 0;
    virtual const NodeProvider* GetNodeProvider() const = 0;
    virtual const ResourceProvider* GetResourceProvider() const = 0;
    virtual const GroupProvider* GetGroupProvider() const = 0;

    virtual HRESULT GetResourceTypes(std::list<ResourceType>&) const = 0;
    virtual HRESULT GetNetworks(std::list<Network>&) const = 0;
    virtual HRESULT GetNetInterfaces(std::list<NetInterface>&) const = 0;
    virtual HRESULT GetSharedVolumeList(std::list<SharedVolume>&) const = 0;

private:
    virtual HRESULT InitProviders() = 0;
};

class ClusterManager;

