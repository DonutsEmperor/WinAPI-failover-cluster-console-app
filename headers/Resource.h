#pragma once

class Resource : public ClusterObject {
    HRESOURCE mPResource;
public:
    std::wstring resTypeName;
    Resource(const PCluster pCluster, const PCLUSTER_ENUM_ITEM pWinStruct) 
        : ClusterObject(pCluster, pWinStruct) {
        mErrorHandler = GetClusterType();
    }
    ~Resource() {}
    HRESULT GetClusterType();
};