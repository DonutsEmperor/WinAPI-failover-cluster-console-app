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

class Resource : public BaseObject {
    HRESOURCE mPResource;
public:
    std::wstring resTypeName;
    MyDiskInfo diskInfo;

    Resource(const PCluster, const PCLUSTER_ENUM_ITEM);
    ~Resource();

private:
    HRESULT FetchResourceType();
    HRESULT FetchClusterDiskInfo();

    void DeterminationOf_FileStructure(MyDiskInfo& , const BYTE*&) const;
    void MakingUp_DiskValueList(MyDiskInfo& , const BYTE*&) const;
};