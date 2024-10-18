#pragma once

class ResourceProvider;

enum DiskType {
    MRB = 1,
    GPT = 2,
    UNKNOWN = 3
};

struct PhysicalDiskInfo {
    DWORD dwType;
    std::variant<DWORD, std::wstring> data;

    CLUSPROP_SCSI_ADDRESS scsi;
    CLUSPROP_ULARGE_INTEGER diskSize;
    CLUSPROP_DISK_NUMBER diskNumb;
    std::shared_ptr<CLUSPROP_PARTITION_INFO_EX> partitionInfo;
};

class Resource : public BaseObject {
    HRESOURCE mPResource;
public:
    std::wstring resTypeName;
    std::shared_ptr<PhysicalDiskInfo> diskInfo;

    Resource() : BaseObject(), mPResource(nullptr) {}
    Resource(const PCluster, const PCLUSTER_ENUM_ITEM);
    ~Resource();

private:
    HRESULT OpenHandler() override;
    HRESULT CloseHandler() override;

    HRESULT FetchResourceType();
    HRESULT FetchClusterDiskInfo();

    void DeterminationOf_FileStructure(PhysicalDiskInfo& , const BYTE*&) const;
    void MakingUp_DiskValueList(PhysicalDiskInfo& , const BYTE*&) const;

    friend class ResourceProvider;
};