#include "../headers/IClusterManager.h"
#include "../headers/ILogger.h"

#include "ClusterProvider.cpp"
#include "NodeProvider.cpp"
#include "ResourceProvider.cpp"
#include "GroupProvider.cpp"
#include "Logger.cpp"

class ClusterManager : public IClusterManager {
    PCluster mClusterPtr;

    std::unique_ptr<LoggerFactory> mLoggerFactory;
    std::unique_ptr<ClusterProvider> mClusterProvider;
    std::unique_ptr<NodeProvider> mNodeProvider;
    std::unique_ptr<ResourceProvider> mResourceProvider;
    std::unique_ptr<GroupProvider> mGroupProvider;

public:
    ClusterManager(const std::wstring* input) : mClusterPtr(nullptr) {
        if (input == nullptr) {
            MyOpenCluster(L"localhost");
        }
        else {
            MyOpenCluster(*input);
        }
    }
    ~ClusterManager() override {
        delete mClusterPtr;
    }

    void MyCloseCluster() const override {
        CloseCluster(mClusterPtr->mPCluster);
    }

    const LoggerFactory* GetLoggerFactory() const override {
        return mLoggerFactory.get();
    }

    const ClusterProvider* GetClusterProvider() const override {
        return mClusterProvider.get();
    }

    const NodeProvider* GetNodeProvider() const override {
        return mNodeProvider.get();
    }

    const ResourceProvider* GetResourceProvider() const override {
        return mResourceProvider.get();
    }

    const GroupProvider* GetGroupProvider() const override {
        return mGroupProvider.get();
    }

    HRESULT GetResourceTypes(std::list<ResourceType>& clusterResTypes) const override {
        clusterResTypes = mClusterPtr->mResTypes;
        return S_OK;
    }

    HRESULT GetNetworks(std::list<Network>& clusterNetworks) const override {
        clusterNetworks = mClusterPtr->mNetworks;
        return S_OK;
    }

    HRESULT GetNetInterfaces(std::list<NetInterface>& clusterNetInterfaces) const override {
        clusterNetInterfaces = mClusterPtr->mNetInterfaces;
        return S_OK;
    }

    HRESULT GetSharedVolumeList(std::list<SharedVolume>& clusterSharedVolumes) const override {
        clusterSharedVolumes = mClusterPtr->mCSVs;
        return S_OK;
    }

private:
    void MyOpenCluster(const std::wstring& name) override {

        HCLUSTER hCluster = OpenCluster(name.c_str());
        if (hCluster == nullptr) {
            return;
        }
        mClusterPtr = new Cluster(hCluster, name);
    }

    void InitProviders() override {
        mLoggerFactory = std::make_unique<LoggerFactory>();
        mClusterProvider = std::make_unique<ClusterProvider>(mClusterPtr);
        mNodeProvider = std::make_unique<NodeProvider>(mClusterPtr);
        mResourceProvider = std::make_unique<ResourceProvider>(mClusterPtr);
        mGroupProvider = std::make_unique<GroupProvider>(mClusterPtr);
    }
};

