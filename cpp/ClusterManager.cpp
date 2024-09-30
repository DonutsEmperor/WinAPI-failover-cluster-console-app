#include "pch.h"

class ClusterManager : public IClusterManager {
    PCluster mCluster;

    std::unique_ptr<ClusterProvider> mClusterProvider;
    std::unique_ptr<NodeProvider> mNodeProvider;
    std::unique_ptr<ResourceProvider> mResourceProvider;
    std::unique_ptr<GroupProvider> mGroupProvider;

public:
    ClusterManager() : mCluster(nullptr) {
        HCLUSTER hCluster = OpenCluster(NULL);
        mCluster = new Cluster(hCluster, L"localhost");
        InitProviders();
    }
    /*ClusterManager(const std::wstring& clusterName) : mCluster(nullptr) {
        HCLUSTER hCluster = OpenCluster(clusterName.c_str());
        mCluster = new Cluster(hCluster, clusterName);
        InitProviders();
    }*/
    ~ClusterManager() override {
        delete mCluster;
    }

    const ClusterProvider* GetClusterProvider() {
        return mClusterProvider.get();
    }

    const NodeProvider* GetNodeProvider() {
        return mNodeProvider.get();
    }

    const ResourceProvider* GetResourceProvider() {
        return mResourceProvider.get();
    }

    const GroupProvider* GetGroupProvider() {
        return mGroupProvider.get();
    }

    HRESULT GetResourceTypes(std::list<ResourceType>& clusterResTypes) const override {
        //clusterResTypes = mCluster->mResTypes;
        return S_OK;
    }

    HRESULT GetNetworks(std::list<Network>& clusterNetworks) const override {
        //clusterNetworks = mCluster->mNetworks;
        return S_OK;
    }

    HRESULT GetNetInterfaces(std::list<NetInterface>& clusterNetInterfaces) const override {
        //clusterNetInterfaces = mCluster->mNetInterfaces;
        return S_OK;
    }

    HRESULT GetSharedVolumeList(std::list<SharedVolume>& clusterSharedVolumes) const override {
        //clusterSharedVolumes = mCluster->mCSVs;
        return S_OK;
    }

private:
    HRESULT InitProviders() override {
        /*mNodeProvider = std::make_unique<NodeProvider>(mCluster);
        mResourceProvider = std::make_unique<ResourceProvider>(mCluster);
        mGroupProvider = std::make_unique<GroupProvider>(mCluster);*/
        return S_OK;
    }
};

