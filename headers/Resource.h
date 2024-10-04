#pragma once

enum MyDiskType {
    MRB = 1,
    GPT = 2,
    UNKNOWN = 3
};

struct MyDiskInfo {
    DWORD dwType;
    std::variant<DWORD, std::wstring> data;

    CLUSPROP_SCSI_ADDRESS scsi;
    CLUSPROP_ULARGE_INTEGER diskSize;
    CLUSPROP_DISK_NUMBER diskNumb;
};

class Resource : public ClusterObject {
    HRESOURCE mPResource;
public:
    std::wstring resTypeName;
    MyDiskInfo diskInfo;

    Resource(const PCluster pCluster, const PCLUSTER_ENUM_ITEM pWinStruct) 
        : ClusterObject(pCluster, pWinStruct) {
        mErrorHandler = FetchResourceType();
        mErrorHandler = FetchClusterDiskInfo();
    }
    ~Resource() {}

private:
    HRESULT FetchResourceType();
    HRESULT FetchClusterDiskInfo();

    void DeterminationOf_FileStructure(MyDiskInfo& info, const BYTE* ptr) const;
    void MakingUp_DiskValueList(MyDiskInfo& info, const BYTE* ptr) const;


};