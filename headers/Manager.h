#pragma once

#include "Cluster.h"

#include "ILogger.h"
#include "Logger.h"
#include "ClusterLogger.h"
#include "NodeLogger.h"
#include "ResourceLogger.h"
#include "GroupLogger.h"
#include "LoggerFactory.h"

#include "IProvider.h"
#include "Provider.h"
#include "ClusterProvider.h"
#include "NodeProvider.h"
#include "ResourceProvider.h"
#include "GroupProvider.h"
#include "ProviderFactory.h"

class Manager {
    std::unique_ptr<Cluster> mCluster;

    std::unique_ptr<IProvider<Cluster>> mClusterProvider;
    std::unique_ptr<IProvider<Node>> mNodeProvider;
    std::unique_ptr<IProvider<Resource>> mResourceProvider;
    std::unique_ptr<IProvider<Group>> mGroupProvider;

    std::unique_ptr<ILogger<Cluster>> mClusterLogger;
    std::unique_ptr<ILogger<Node>> mNodeLogger;
    std::unique_ptr<ILogger<Resource>> mResourceLogger;
    std::unique_ptr<ILogger<Group>> mGroupLogger;

    std::unique_ptr<ProviderFactory> mProviderFactory;
    std::unique_ptr<LoggerFactory> mLoggerFactory;

public:
    Manager(const std::wstring*);
    ~Manager();

    // Getters for loggers
    const ClusterLogger* GetClusterLogger() const;
    const NodeLogger* GetNodeLogger() const;
    const ResourceLogger* GetResourceLogger() const;
    const GroupLogger* GetGroupLogger() const;

    // Getters for providers
    const ClusterProvider* GetClusterProvider() const;
    const NodeProvider* GetNodeProvider() const;
    const ResourceProvider* GetResourceProvider() const;
    const GroupProvider* GetGroupProvider() const;

    HRESULT GetResourceTypes(std::list<ResourceType>& ) const;
    HRESULT GetNetworks(std::list<Network>& ) const;
    HRESULT GetNetInterfaces(std::list<NetInterface>& ) const;
    HRESULT GetSharedVolumeList(std::list<SharedVolume>& ) const;

private:
    void DefOpenCluster(const std::wstring*);
    void DefCloseCluster() const;

    void InitFabrics();
    void InitProviders();
    void InitLoggers();
};

//////////////////// global Manager

//std::unique_ptr<Manager> g_Manager;
//
//void InitializeGlobalManager(const std::wstring* input);
//Manager* GetGlobalManager();
