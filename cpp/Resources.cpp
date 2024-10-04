#include "Cluster.h"

HRESULT Resource::FetchResourceType()
{
    mPResource = OpenClusterResource(cluster->mPCluster, properties.itemName.c_str());

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
    mPResource = OpenClusterResource(cluster->mPCluster, properties.itemName.c_str());

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
        MyDiskInfo mDI = MyDiskInfo();

        DeterminationOf_FileStructure(mDI, ptr);
        MakingUp_DiskValueList(mDI, ptr);

        diskInfo = mDI;
        return S_OK;
    }
    return S_FALSE;
}

void Resource::DeterminationOf_FileStructure(MyDiskInfo& mDI, const BYTE*& ptr) const {

    DWORD* dw = reinterpret_cast<DWORD*>(const_cast<BYTE*>(ptr));

    std::wcout << "FIRST BYTES " << std::hex << dw << std::dec << std::endl;
    std::wcout << "FIRST VALUE " << *dw << std::endl;

    switch ((CLUSTER_PROPERTY_SYNTAX)*dw)
    {
    case CLUSTER_PROPERTY_SYNTAX::CLUSPROP_SYNTAX_DISK_SIGNATURE:
    {
        mDI.dwType = MyDiskType::MRB;
        CLUSPROP_DWORD* prop = reinterpret_cast<CLUSPROP_DWORD*>(const_cast<BYTE*>(ptr));
        mDI.data = prop->dw;

        DWORD shift = prop->cbLength;
        ptr += sizeof(CLUSPROP_VALUE) + shift;
        std::wcout << "shift of " << sizeof(CLUSPROP_VALUE) + shift << " bytes" << std::endl;
        break;
    }

    case CLUSTER_PROPERTY_SYNTAX::CLUSPROP_SYNTAX_DISK_GUID:
    {
        mDI.dwType = MyDiskType::GPT;
        CLUSPROP_SZ* prop = reinterpret_cast<CLUSPROP_SZ*>(const_cast<BYTE*>(ptr));
        mDI.data = prop->sz;

        std::wcout << "Data: " << prop->sz << std::endl;
        std::wcout << "Lenght: " << prop->cbLength << std::endl;

        DWORD shift = prop->cbLength;
        ptr += sizeof(CLUSPROP_VALUE) + shift;
        std::wcout << "shift of " << sizeof(CLUSPROP_VALUE) + shift << " bytes" << std::endl;
        break;
    }

    default:
        mDI.dwType = MyDiskType::UNKNOWN;
        break;
    }

    std::wstring* str = std::get_if<std::wstring>(&mDI.data);
    DWORD* number = std::get_if<DWORD>(&mDI.data);

    std::wcout << "Type: " << mDI.dwType << std::endl;

    if (str) {
        std::wcout << "Variant Name wstring: " << *str << std::endl;
        std::wcout << "Variant size wstring: " << str->length() * sizeof(WCHAR) << std::endl;
    }

    if (number)
        std::wcout << "Variant Name dword: " << *number << std::endl;

    std::wcout << std::endl;
}

void Resource::MakingUp_DiskValueList(MyDiskInfo& mDI, const BYTE*& ptr) const {
    while (ptr) {

        DWORD* dw = reinterpret_cast<DWORD*>(const_cast<BYTE*>(ptr));

        std::wcout << "FIRST BYTES " << std::hex << dw << std::dec << std::endl;
        std::wcout << "FIRST VALUE " << *dw << std::endl;

        std::wcout << std::endl;

        switch ((CLUSTER_PROPERTY_SYNTAX)*dw)
        {
        case CLUSTER_PROPERTY_SYNTAX::CLUSPROP_SYNTAX_SCSI_ADDRESS:
        {
            CLUSPROP_SCSI_ADDRESS* prop = reinterpret_cast<CLUSPROP_SCSI_ADDRESS*>(const_cast<BYTE*>(ptr));
            mDI.scsi = *prop;

            std::wcout << "Dw?: " << prop->dw << std::endl;
            std::wcout << "Lun: " << prop->Lun << std::endl;
            std::wcout << "PathId: " << prop->PathId << std::endl;
            std::wcout << "PortNumber: " << prop->PortNumber << std::endl;
            std::wcout << "TargetId: " << prop->TargetId << std::endl;

            ptr += sizeof(CLUSPROP_SCSI_ADDRESS);
            std::wcout << "shift of " << sizeof(CLUSPROP_SCSI_ADDRESS) << " bytes" << std::endl;
            break;
        }
        case CLUSTER_PROPERTY_SYNTAX::CLUSPROP_SYNTAX_DISK_SIZE:
        {
            CLUSPROP_ULARGE_INTEGER* prop = reinterpret_cast<CLUSPROP_ULARGE_INTEGER*>(const_cast<BYTE*>(ptr));
            mDI.diskSize = *prop;

            std::wcout << "QuadPart: " << prop->li.QuadPart << std::endl;
            std::wcout << "HighPart: " << prop->li.HighPart << std::endl;

            DWORD shift = prop->cbLength;
            ptr += sizeof(CLUSPROP_VALUE) + shift;
            std::wcout << "shift of " << sizeof(ULARGE_INTEGER) + shift << " bytes" << std::endl;
            break;
        }
        case CLUSTER_PROPERTY_SYNTAX::CLUSPROP_SYNTAX_DISK_NUMBER:
        {
            CLUSPROP_DISK_NUMBER* prop = reinterpret_cast<CLUSPROP_DISK_NUMBER*>(const_cast<BYTE*>(ptr));
            mDI.diskNumb = *prop;

            std::wcout << "DiskNumber: " << prop->dw << std::endl;

            DWORD shift = prop->cbLength;
            ptr += sizeof(CLUSPROP_VALUE) + shift;
            std::wcout << "shift of " << sizeof(CLUSPROP_VALUE) + sizeof(DWORD) << " bytes" << std::endl;
            break;
        }
        case CLUSTER_PROPERTY_SYNTAX::CLUSPROP_SYNTAX_PARTITION_INFO_EX:
        {
            CLUSPROP_PARTITION_INFO_EX* prop = reinterpret_cast<CLUSPROP_PARTITION_INFO_EX*>(const_cast<BYTE*>(ptr));
            std::wcout << "DeviceNumber: " << prop->DeviceNumber << std::endl;

            DWORD shift = prop->cbLength;
            ptr += sizeof(CLUSPROP_VALUE) + shift;
            std::wcout << "shift of " << sizeof(CLUSPROP_VALUE) + shift << " bytes" << std::endl;
            break;
        }
        case CLUSTER_PROPERTY_SYNTAX::CLUSPROP_SYNTAX_ENDMARK:
        {
            std::wcout << "Correct finish? " << std::endl;
            return;
        }
        }

        std::wcout << std::endl;
    }
}