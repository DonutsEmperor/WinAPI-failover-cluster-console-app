#include "../headers/Cluster.h"
#include "../headers/IClusterProvider.h"

class ClusterProvider : public IClusterProvider {
    PCluster mCluster;
public:
    ClusterProvider(PCluster pCluster) : mCluster(pCluster) {}
    ~ClusterProvider() override {};

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
};
