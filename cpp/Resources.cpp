#include "Cluster.h"

Resource::Resource(const PCluster pCluster, const PCLUSTER_ENUM_ITEM pWinStruct)
    : BaseObject(pCluster, pWinStruct) {
    mErrorHandler = FetchResourceType();
    mErrorHandler = FetchClusterDiskInfo();
}
Resource::~Resource() {}

HRESULT Resource::FetchResourceType()
{
    mPResource = OpenClusterResource(cluster->mHandler, properties.itemName.c_str());

    DWORD initialSizeOfBuffer = 64, returnedSizeOfBuffer = 0;
    LPVOID buffer = malloc(sizeof(WCHAR) * initialSizeOfBuffer);

    DWORD errorcode = ClusterResourceControl(mPResource,
        nullptr, CLUSCTL_RESOURCE_GET_RESOURCE_TYPE,
        nullptr, 0, buffer,
        initialSizeOfBuffer,
        &returnedSizeOfBuffer);

    if (returnedSizeOfBuffer > initialSizeOfBuffer) 
    {
        buffer = realloc(buffer, returnedSizeOfBuffer);

        errorcode = ClusterResourceControl(mPResource,
            nullptr, CLUSCTL_RESOURCE_GET_RESOURCE_TYPE,
            nullptr, 0, buffer,
            returnedSizeOfBuffer,
            &returnedSizeOfBuffer);
    }

    if (buffer) {
        resTypeName = reinterpret_cast<LPCWSTR>(buffer);
    }
    else {
        return S_FALSE;
    }

    free(buffer);
    CloseClusterResource(mPResource);

    return S_OK;
}

HRESULT Resource::FetchClusterDiskInfo()
{
    mPResource = OpenClusterResource(cluster->mHandler, properties.itemName.c_str());

    DWORD size = 0;
    DWORD errorcode = ClusterResourceControl(mPResource, nullptr,
        CLUSCTL_RESOURCE_STORAGE_GET_DISK_INFO_EX,
        nullptr, 0, nullptr, 0, &size);

    if (!errorcode)
    {
        std::vector<BYTE> buffer(size);
        PVOID pBuffer = reinterpret_cast<PVOID>(buffer.data());

        errorcode = ClusterResourceControl(mPResource, nullptr,
            CLUSCTL_RESOURCE_STORAGE_GET_DISK_INFO_EX,
            nullptr, 0, pBuffer, size, &size);

        const BYTE* ptr = reinterpret_cast<BYTE*>(pBuffer);
        const BYTE* end = ptr + size;

        DWORD* dw = reinterpret_cast<DWORD*>(const_cast<BYTE*>(ptr));
        PhysicalDiskInfo mDI = PhysicalDiskInfo();

        DeterminationOf_FileStructure(mDI, ptr);
        MakingUp_DiskValueList(mDI, ptr);

        diskInfo = std::make_shared<PhysicalDiskInfo>(mDI);
        return S_OK;
    }
    return S_FALSE;
}

void Resource::DeterminationOf_FileStructure(PhysicalDiskInfo& pDI, const BYTE*& ptr) const {

    DWORD* dw = reinterpret_cast<DWORD*>(const_cast<BYTE*>(ptr));

    switch ((CLUSTER_PROPERTY_SYNTAX)*dw)
    {
        case CLUSTER_PROPERTY_SYNTAX::CLUSPROP_SYNTAX_DISK_SIGNATURE:
        {
            pDI.dwType = DiskType::MRB;
            CLUSPROP_DWORD* prop = reinterpret_cast<CLUSPROP_DWORD*>(const_cast<BYTE*>(ptr));
            pDI.data = prop->dw;

            DWORD shift = prop->cbLength;
            ptr += sizeof(CLUSPROP_VALUE) + shift;
            break;
        }
        case CLUSTER_PROPERTY_SYNTAX::CLUSPROP_SYNTAX_DISK_GUID:
        {
            pDI.dwType = DiskType::GPT;
            CLUSPROP_SZ* prop = reinterpret_cast<CLUSPROP_SZ*>(const_cast<BYTE*>(ptr));
            pDI.data = prop->sz;

            DWORD shift = prop->cbLength;
            ptr += sizeof(CLUSPROP_VALUE) + prop->cbLength;
            break;
        }
        default:
            pDI.dwType = DiskType::UNKNOWN;
            break;
    }
}

void Resource::MakingUp_DiskValueList(PhysicalDiskInfo& pDI, const BYTE*& ptr) const {
    while (ptr) {
        DWORD* dw = reinterpret_cast<DWORD*>(const_cast<BYTE*>(ptr));

        switch ((CLUSTER_PROPERTY_SYNTAX)*dw)
        {
            case CLUSTER_PROPERTY_SYNTAX::CLUSPROP_SYNTAX_SCSI_ADDRESS:
            {
                CLUSPROP_SCSI_ADDRESS* prop = reinterpret_cast<CLUSPROP_SCSI_ADDRESS*>(const_cast<BYTE*>(ptr));
                pDI.scsi = *prop;

                ptr += sizeof(CLUSPROP_SCSI_ADDRESS);
                break;
            }
            case CLUSTER_PROPERTY_SYNTAX::CLUSPROP_SYNTAX_DISK_SIZE:
            {
                CLUSPROP_ULARGE_INTEGER* prop = reinterpret_cast<CLUSPROP_ULARGE_INTEGER*>(const_cast<BYTE*>(ptr));
                pDI.diskSize = *prop;

                DWORD shift = prop->cbLength;
                ptr += sizeof(CLUSPROP_VALUE) + shift;
                break;
            }
            case CLUSTER_PROPERTY_SYNTAX::CLUSPROP_SYNTAX_DISK_NUMBER:
            {
                CLUSPROP_DISK_NUMBER* prop = reinterpret_cast<CLUSPROP_DISK_NUMBER*>(const_cast<BYTE*>(ptr));
                pDI.diskNumb = *prop;

                DWORD shift = prop->cbLength;
                ptr += sizeof(CLUSPROP_VALUE) + shift;
                break;
            }
            case CLUSTER_PROPERTY_SYNTAX::CLUSPROP_SYNTAX_PARTITION_INFO_EX:
            {
                CLUSPROP_PARTITION_INFO_EX* prop = reinterpret_cast<CLUSPROP_PARTITION_INFO_EX*>(const_cast<BYTE*>(ptr));
                pDI.partitionInfo = std::make_shared<CLUSPROP_PARTITION_INFO_EX>(*prop);

                DWORD shift = prop->cbLength;
                ptr += sizeof(CLUSPROP_VALUE) + shift;
                break;
            }
            case CLUSTER_PROPERTY_SYNTAX::CLUSPROP_SYNTAX_ENDMARK:
            {
                return;
            }
            default: {
                std::wcout << "Memory leakage" << std::endl;
                return;
            }
        }
    }
}