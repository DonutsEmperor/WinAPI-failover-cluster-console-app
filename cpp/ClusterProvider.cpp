#include "Cluster.h"
#include "ClusterProvider.h"

ClusterProvider::ClusterProvider(PCluster cluster) : Provider<Cluster>(cluster) {}

HCLUSTER ClusterProvider::GetClusterHandle() const {
    return mCluster ? mCluster->mHandler : nullptr;
}

HRESULT ClusterProvider::GetClusterName(std::wstring& clusterName) const {
    clusterName = mCluster->mCName;
    return S_OK;
}

HRESULT ClusterProvider::GetClusterState(DWORD* pdwClusterState) const {
    DWORD objectErrorCode = GetNodeClusterState(mCluster->mCName.c_str(), pdwClusterState);
    return S_OK;
}

HRESULT ClusterProvider::UpdateClusterLists() const {
    mCluster->UpdateLists();
}

HRESULT ClusterProvider::UpdateClusterListByType(DWORD type) const {
    mCluster->UpdateSpecificList(type);
}