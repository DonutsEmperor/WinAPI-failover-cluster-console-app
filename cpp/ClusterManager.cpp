#include <windows.h>
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include "ClusApi.h"

#include "../headers/IClusterManager.h"

#include "NodeProvider.cpp"
#include "ResourceProvider.cpp"
#include "GroupProvider.cpp"

class ClusterManager : public IClusterManager {
    PCluster mCluster;

    std::unique_ptr<NodeProvider> mNodeProvider;
    std::unique_ptr<ResourceProvider> mResourceProvider;
    std::unique_ptr<GroupProvider> mGroupProvider;

public:
    ClusterManager() : mCluster(nullptr) {
        HCLUSTER hCluster = OpenCluster(NULL);
        mCluster = new Cluster(hCluster, L"localhost");
        InitProviders();
    }
    ~ClusterManager() override {
        delete mCluster;
    }

    HRESULT MyOpenCluster(const std::wstring& clusterName) override {

        HCLUSTER hCluster = OpenCluster(clusterName.c_str());
        if (hCluster == nullptr) {
            return E_FAIL;
        }

        mCluster = new Cluster(hCluster, clusterName);
        InitProviders();
        return S_OK;
    }

    void MyCloseCluster() const override {
        CloseCluster(mCluster->mPCluster);
    }

    HCLUSTER GetClusterHandle() const override {
        return mCluster ? mCluster->mPCluster : nullptr;
    }

    HRESULT GetClusterName(std::wstring& clusterName) const override {
        clusterName = mCluster->mCName;
        return S_OK;
    }

    HRESULT GetClusterState(DWORD* pdwClusterState) const override {
        if (pdwClusterState == nullptr) {
            return E_FAIL;
        }

        DWORD objectErrorCode = GetNodeClusterState(mCluster->mCName.c_str(), pdwClusterState);

        if (!pdwClusterState) {
            std::wcout << "Error with cluster status!" << std::endl;
            return HRESULT_FROM_WIN32(objectErrorCode);
        }

        return S_OK;
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

    NodeProvider* GetNodeProvider() {
        return mNodeProvider.get();
    }

    ResourceProvider* GetResourceProvider() {
        return mResourceProvider.get();
    }

    GroupProvider* GetGroupProvider() {
        return mGroupProvider.get();
    }

private:
    HRESULT InitProviders() override {
        /*mNodeProvider = std::make_unique<NodeProvider>(mCluster);
        mResourceProvider = std::make_unique<ResourceProvider>(mCluster);
        mGroupProvider = std::make_unique<GroupProvider>(mCluster);*/
        return S_OK;
    }
};

