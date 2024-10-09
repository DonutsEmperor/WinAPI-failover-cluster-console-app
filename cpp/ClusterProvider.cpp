#include "Cluster.h"
#include "IClusterProvider.h"

ClusterProvider::ClusterProvider(PCluster pCluster) : mCluster(pCluster) {}
ClusterProvider::~ClusterProvider() {};

HCLUSTER ClusterProvider::GetClusterHandle() const {
    return mCluster ? mCluster->mPCluster : nullptr;
}

HRESULT ClusterProvider::GetClusterName(std::wstring& clusterName) const {
    clusterName = mCluster->mCName;
    return S_OK;
}

HRESULT ClusterProvider::GetClusterState(DWORD* pdwClusterState) const {
    if (pdwClusterState == nullptr) {
        return E_FAIL;
    }

    DWORD objectErrorCode = GetNodeClusterState(mCluster->mCName.c_str(), pdwClusterState);

    if (!pdwClusterState) {
        return HRESULT_FROM_WIN32(objectErrorCode);
    }
    return S_OK;
}