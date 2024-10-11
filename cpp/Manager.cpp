#include "Manager.h"

Manager::Manager(const std::wstring* input) {
    DefOpenCluster(input);
    InitFabrics();
    InitProviders();
    InitLoggers();
}

Manager::~Manager() {
    DefCloseCluster();
}

void Manager::InitFabrics() {
    mProviderFactory = std::make_unique<ProviderFactory>();
    mLoggerFactory = std::make_unique<LoggerFactory>();
}

void Manager::InitProviders() {
    mClusterProvider = mProviderFactory->CreateProvider<Cluster>(mCluster.get());
    mNodeProvider = mProviderFactory->CreateProvider<Node>(mCluster.get());
    mResourceProvider = mProviderFactory->CreateProvider<Resource>(mCluster.get());
    mGroupProvider = mProviderFactory->CreateProvider<Group>(mCluster.get());
}

void Manager::InitLoggers() {
    mClusterLogger = mLoggerFactory->CreateLogger<Cluster>();
    mNodeLogger = mLoggerFactory->CreateLogger<Node>();
    mResourceLogger = mLoggerFactory->CreateLogger<Resource>();
    mGroupLogger = mLoggerFactory->CreateLogger<Group>();
}

const ClusterLogger* Manager::GetClusterLogger() const {
    return dynamic_cast<ClusterLogger*>(mClusterLogger.get());
}

const NodeLogger* Manager::GetNodeLogger() const {
    return dynamic_cast<NodeLogger*>(mNodeLogger.get());
}

const ResourceLogger* Manager::GetResourceLogger() const {
    return dynamic_cast<ResourceLogger*>(mResourceLogger.get());
}

const GroupLogger* Manager::GetGroupLogger() const {
    return dynamic_cast<GroupLogger*>(mGroupLogger.get());
}


const ClusterProvider* Manager::GetClusterProvider() const {
    return dynamic_cast<ClusterProvider*>(mClusterProvider.get());
}

const NodeProvider* Manager::GetNodeProvider() const {
    return dynamic_cast<NodeProvider*>(mNodeProvider.get());
}

const ResourceProvider* Manager::GetResourceProvider() const {
    return dynamic_cast<ResourceProvider*>(mResourceProvider.get());
}

const GroupProvider* Manager::GetGroupProvider() const {
    return dynamic_cast<GroupProvider*>(mGroupProvider.get());
}

// more abstractive implementation
//const Logger<Cluster>* Manager::GetClusterLogger() const {
//    return dynamic_cast<ClusterLogger*>(mClusterLogger.get());
//}
//
//const Logger<Node>* Manager::GetNodeLogger() const {
//    return dynamic_cast<NodeLogger*>(mNodeLogger.get());
//}
//
//const Logger<Resource>* Manager::GetResourceLogger() const {
//    return dynamic_cast<ResourceLogger*>(mResourceLogger.get());
//}
//
//
//const IProvider<Cluster>* Manager::GetClusterProvider() const {
//    return mClusterProvider.get();
//}
//
//const IProvider<Node>* Manager::GetNodeProvider() const {
//    return mNodeProvider.get();
//}
//
//const IProvider<Resource>* Manager::GetResourceProvider() const {
//    return mResourceProvider.get();
//}

HRESULT Manager::GetResourceTypes(std::list<ResourceType>& clusterResTypes) const {
    clusterResTypes = mCluster->mResTypes;
    return S_OK;
}

HRESULT Manager::GetNetworks(std::list<Network>& clusterNetworks) const {
    clusterNetworks = mCluster->mNetworks;
    return S_OK;
}

HRESULT Manager::GetNetInterfaces(std::list<NetInterface>& clusterNetInterfaces) const {
    clusterNetInterfaces = mCluster->mNetInterfaces;
    return S_OK;
}

HRESULT Manager::GetSharedVolumeList(std::list<SharedVolume>& clusterSharedVolumes) const {
    clusterSharedVolumes = mCluster->mCSVs;
    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////

void Manager::DefCloseCluster() const {
    CloseCluster(mCluster->mHandler);
}

void Manager::DefOpenCluster(const std::wstring* name) {
    HCLUSTER handler;

    std::wstring output;

    if (name != nullptr) {
        handler = OpenCluster((*name).c_str());
        output = *name;
    }
    else {
        handler = OpenCluster(NULL);
        output = L"localhost";
    }

    mCluster = std::make_unique<Cluster>(handler, output);
}

