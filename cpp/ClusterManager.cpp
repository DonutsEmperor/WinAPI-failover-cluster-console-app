#include "IClusterManager.h"
#include "INodeProvider.h"
#include "IGroupProvider.h"
#include "IResourceProvider.h"
#include "IClusterProvider.h"
#include "ILogger.h"
#include "LoggerFactory.h"
#include "ItemLogger.h"

ClusterManager::ClusterManager(const std::wstring* input) : mClusterPtr(nullptr) {
    if (input == nullptr) {
        MyOpenCluster(L"localhost");
    }
    else {
        MyOpenCluster(*input);
    }
}
ClusterManager::~ClusterManager() {
    delete mClusterPtr;
}

void ClusterManager::MyCloseCluster() const {
    CloseCluster(mClusterPtr->mPCluster);
}

const LoggerFactory* ClusterManager::GetLoggerFactory() const {
    return mLoggerFactory.get();
}

const ClusterProvider* ClusterManager::GetClusterProvider() const {
    return mClusterProvider.get();
}

const NodeProvider* ClusterManager::GetNodeProvider() const {
    return mNodeProvider.get();
}

const ResourceProvider* ClusterManager::GetResourceProvider() const {
    return mResourceProvider.get();
}

const GroupProvider* ClusterManager::GetGroupProvider() const {
    return mGroupProvider.get();
}

HRESULT ClusterManager::GetResourceTypes(std::list<ResourceType>& clusterResTypes) const {
    clusterResTypes = mClusterPtr->mResTypes;
    return S_OK;
}

HRESULT ClusterManager::GetNetworks(std::list<Network>& clusterNetworks) const {
    clusterNetworks = mClusterPtr->mNetworks;
    return S_OK;
}

HRESULT ClusterManager::GetNetInterfaces(std::list<NetInterface>& clusterNetInterfaces) const {
    clusterNetInterfaces = mClusterPtr->mNetInterfaces;
    return S_OK;
}

HRESULT ClusterManager::GetSharedVolumeList(std::list<SharedVolume>& clusterSharedVolumes) const {
    clusterSharedVolumes = mClusterPtr->mCSVs;
    return S_OK;
}

void ClusterManager::MyOpenCluster(const std::wstring& name) {

    HCLUSTER hCluster = OpenCluster(name.c_str());
    if (hCluster == nullptr) {
        return;
    }
    mClusterPtr = new Cluster(hCluster, name);
}

void ClusterManager::InitProviders() {
    mLoggerFactory = std::make_unique<LoggerFactory>();
    mClusterProvider = std::make_unique<ClusterProvider>(mClusterPtr);
    mNodeProvider = std::make_unique<NodeProvider>(mClusterPtr);
    mResourceProvider = std::make_unique<ResourceProvider>(mClusterPtr);
    mGroupProvider = std::make_unique<GroupProvider>(mClusterPtr);
}

