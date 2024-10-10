#pragma once

class Resource : public BaseObject {
    HRESOURCE mPResource;
public:
    std::wstring resTypeName;

    Resource(const PCluster pCluster, const PCLUSTER_ENUM_ITEM pWinStruct) 
        : BaseObject(pCluster, pWinStruct) {
        mErrorHandler = GetClusterType();
    }
    ~Resource() {}
    HRESULT GetClusterType();
};