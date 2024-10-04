#pragma once

#include "Cluster.h"
#include "IClusterProvider.h"
#include "IGroupProvider.h"
#include "IResourceProvider.h"
#include "INodeProvider.h"
#include "ILogger.h"
#include "ItemLogger.h"
#include "LoggerFactory.h"

class IClusterManager 
{
public:
    virtual ~IClusterManager() {};
    virtual void MyOpenCluster(const std::wstring&) = 0;

    virtual const LoggerFactory* GetLoggerFactory() const = 0;
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

class ClusterManager : public IClusterManager {
    PCluster mClusterPtr;

    std::unique_ptr<LoggerFactory> mLoggerFactory;
    std::unique_ptr<ClusterProvider> mClusterProvider;
    std::unique_ptr<NodeProvider> mNodeProvider;
    std::unique_ptr<ResourceProvider> mResourceProvider;
    std::unique_ptr<GroupProvider> mGroupProvider;

public:
    ClusterManager(const std::wstring*);
    ~ClusterManager() override;

    void MyCloseCluster() const override;

    const LoggerFactory* GetLoggerFactory() const override;
    const ClusterProvider* GetClusterProvider() const override;
    const NodeProvider* GetNodeProvider() const override;
    const ResourceProvider* GetResourceProvider() const override;
    const GroupProvider* GetGroupProvider() const override;

    HRESULT GetResourceTypes(std::list<ResourceType>& clusterResTypes) const override;
    HRESULT GetNetworks(std::list<Network>& clusterNetworks) const override;
    HRESULT GetNetInterfaces(std::list<NetInterface>& clusterNetInterfaces) const override;
    HRESULT GetSharedVolumeList(std::list<SharedVolume>& clusterSharedVolumes) const override;

private:
    void MyOpenCluster(const std::wstring& name) override;
    void InitProviders() override;
};
