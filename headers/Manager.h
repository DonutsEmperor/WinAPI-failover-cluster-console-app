#pragma once

#include "Cluster.h"

#include "ILogger.h"
#include "Logger.h"
#include "ClusterLogger.h"
#include "NodeLogger.h"
#include "ResourceLogger.h"
#include "LoggerFactory.h"

#include "IProvider.h"
#include "Provider.h"
#include "ClusterProvider.h"
#include "NodeProvider.h"
#include "ResourceProvider.h"
#include "ProviderFactory.h"

class Manager {
    std::unique_ptr<Cluster> mCluster;

    std::unique_ptr<IProvider<Cluster>> mClusterProvider;
    std::unique_ptr<IProvider<Node>> mNodeProvider;
    std::unique_ptr<IProvider<Resource>> mResourceProvider;

    std::unique_ptr<ILogger<Cluster>> mClusterLogger;
    std::unique_ptr<ILogger<Node>> mNodeLogger;
    std::unique_ptr<ILogger<Resource>> mResourceLogger;

    std::unique_ptr<ProviderFactory> mProviderFactory;
    std::unique_ptr<LoggerFactory> mLoggerFactory;

public:
    Manager(const std::wstring*);
    ~Manager();

    // Getters for loggers
    const Logger<Cluster>* GetClusterLogger() const;
    const Logger<Node>* GetNodeLogger() const;
    const Logger<Resource>* GetResourceLogger() const;

    // Getters for providers
    const IProvider<Cluster>* GetClusterProvider() const;
    const IProvider<Node>* GetNodeProvider() const;
    const IProvider<Resource>* GetResourceProvider() const;

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
