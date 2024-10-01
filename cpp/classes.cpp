#include <list>
#include <vector>
#include <variant>
#include <memory>
#include <iostream>
#include <string>
#include <iterator>
#include "..//headers/classes.h"

// Define fetchNodes function after the Node class has been declared
void Cluster::fetchItemsWithType(const DWORD typeofEnum)
{
    HCLUSENUMEX hClusterEnum = ClusterOpenEnumEx(mPCluster, typeofEnum, nullptr);
    DWORD objectErrorCode;

    LPDWORD itemSize = new DWORD(1);
    PCLUSTER_ENUM_ITEM pItem = (PCLUSTER_ENUM_ITEM)malloc(*itemSize);

    DWORD enumLenght = ClusterGetEnumCountEx(hClusterEnum), iterator = 0;

    while (iterator < enumLenght)
    {
        objectErrorCode = ClusterEnumEx(hClusterEnum, iterator++, pItem, itemSize);

        if (objectErrorCode == ERROR_SUCCESS)
        {
            switch (typeofEnum)
            {
                case CLUSTER_ENUM_NODE:
                {
                    Node node(this, pItem);
                    mNodes.push_back(node);
                }
                break;

                case CLUSTER_ENUM_GROUP:
                {
                    Group group(this, pItem);
                    mGroups.push_back(group);
                }
                break;

                case CLUSTER_ENUM_RESOURCE:
                {
                    Resource resource(this, pItem);
                    mResources.push_back(resource);
                }
                break;

                case CLUSTER_ENUM_RESTYPE:
                {
                    ResType restype(this, pItem);
                    mResTypes.push_back(restype);
                }
                break;

                case CLUSTER_ENUM_NETWORK:
                {
                    Network network(this, pItem);
                    mNetworks.push_back(network);
                }
                break;

                case CLUSTER_ENUM_NETINTERFACE:
                {
                    NetInterface netinterface(this, pItem);
                    mNetInterfaces.push_back(netinterface);
                }
                break;

                case CLUSTER_ENUM_SHARED_VOLUME_RESOURCE:
                {
                    SharedVolume sharedvolume(this, pItem);
                    mCSVs.push_back(sharedvolume);
                }
                break;
            }
            continue;
        }
        else if (objectErrorCode == ERROR_MORE_DATA)
        {
            pItem = (PCLUSTER_ENUM_ITEM)realloc(pItem, *itemSize);
            iterator--;

            continue;
        }
        break;
    }

    delete itemSize;
    free(pItem);

    ClusterCloseEnumEx(hClusterEnum);
}

HRESULT Resource::GetClusterType() 
{
    mPResource = OpenClusterResource(cluster->mPCluster, properties.itemName.c_str());

    DWORD returnedSizeOfBuffer = 0;
    LPVOID buffer = malloc(sizeof(WCHAR) * 1);

    DWORD errorcode = ClusterResourceControl(mPResource, nullptr, CLUSCTL_RESOURCE_GET_RESOURCE_TYPE,
        nullptr, 0, buffer, sizeof(buffer), &returnedSizeOfBuffer);

    /*std::wcout << "Error [" << errorcode << "]" << std::endl;
    std::wcout << "Need bytes [" << returnedSizeOfBuffer << "]" << std::endl;*/

    if (errorcode)
    {
        buffer = realloc(buffer, returnedSizeOfBuffer);
        errorcode = ClusterResourceControl(mPResource, nullptr, CLUSCTL_RESOURCE_GET_RESOURCE_TYPE,
            nullptr, 0, buffer, returnedSizeOfBuffer, &returnedSizeOfBuffer);
    }

    /*std::wcout << "Bytes now [" << returnedSizeOfBuffer << "]" << std::endl;
    std::wcout << "Error [" << errorcode << "]" << std::endl << std::endl;*/

    if (!errorcode && buffer) {
        //std::wcout << "Success!" << std::endl;
        resTypeName = reinterpret_cast<LPCWSTR>(buffer);
    }
    else
    {
        free(buffer);
        CloseClusterResource(mPResource);
        return S_FALSE;
    }

    free(buffer);
    CloseClusterResource(mPResource);
    return S_OK;
}

enum MyDiskType {
    MRB = 1,
    GPT = 2,
    UNKNOWN = 3
};

struct MyDiskInfo {
    DWORD dwType;
    std::variant<DWORD, std::wstring> data;
};

HRESULT Resource::GetClusterDiskInfo()
{
    mPResource = OpenClusterResource(cluster->mPCluster, properties.itemName.c_str());

    DWORD size = 0;
    //PVOID buffer = malloc(sizeof(CLUSPROP_PARTITION_INFO_EX) * 1);

    DWORD errorcode = ClusterResourceControl(mPResource, nullptr, 
        CLUSCTL_RESOURCE_STORAGE_GET_DISK_INFO_EX,
        nullptr, 0, nullptr, 0, &size);

    if (errorcode == 1)
        return S_FALSE;

    std::wcout << "Error code [" << errorcode << "]" << std::endl;
    std::wcout << "Need bytes [" << size << "]" << std::endl;

    if (!errorcode)
    {
        std::vector<BYTE> buffer(size);
        PVOID pBuffer = reinterpret_cast<PVOID>(buffer.data());

        std::wcout << buffer.capacity() << std::endl;

        errorcode = ClusterResourceControl(mPResource, nullptr, 
            CLUSCTL_RESOURCE_STORAGE_GET_DISK_INFO_EX,
            nullptr, 0, pBuffer, size, &size);

        const BYTE* ptr = reinterpret_cast<BYTE*>(pBuffer);
        const BYTE* end = ptr + size;

        // first step

        DWORD* dw = reinterpret_cast<DWORD*>(const_cast<BYTE*>(ptr));

        std::wcout << "FIRST BYTES " << std::hex << dw << std::dec << std::endl;
        std::wcout << "FIRST VALUE " << *dw << std::endl;

        std::wcout << std::endl;

        MyDiskInfo mDI = MyDiskInfo();

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
                return S_FALSE;
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

        // second step

        while (ptr) {

            DWORD* dw = reinterpret_cast<DWORD*>(const_cast<BYTE*>(ptr));

            std::wcout << "FIRST BYTES " << std::hex << dw << std::dec << std::endl;
            std::wcout << "FIRST VALUE " << *dw << std::endl;

            std::wcout << std::endl;

            switch ((CLUSTER_PROPERTY_SYNTAX)*dw)
            {
                case CLUSTER_PROPERTY_SYNTAX::CLUSPROP_SYNTAX_SCSI_ADDRESS: //pass
                {
                    CLUSPROP_SCSI_ADDRESS* prop = reinterpret_cast<CLUSPROP_SCSI_ADDRESS*>(const_cast<BYTE*>(ptr));

                    std::wcout << "Dw?: " << prop->dw << std::endl;
                    std::wcout << "Lun: " << prop->Lun << std::endl;
                    std::wcout << "PathId: " << prop->PathId << std::endl;
                    std::wcout << "PortNumber: " << prop->PortNumber << std::endl;
                    std::wcout << "TargetId: " << prop->TargetId << std::endl;

                    ptr += sizeof(CLUSPROP_SCSI_ADDRESS);
                    std::wcout << "shift of " << sizeof(CLUSPROP_SCSI_ADDRESS) << " bytes" << std::endl;
                    break;
                }
                case CLUSTER_PROPERTY_SYNTAX::CLUSPROP_SYNTAX_DISK_SIZE: //pass  
                {
                    CLUSPROP_ULARGE_INTEGER* prop = reinterpret_cast<CLUSPROP_ULARGE_INTEGER*>(const_cast<BYTE*>(ptr));
                    std::wcout << "QuadPart: " << prop->li.QuadPart << std::endl;
                    std::wcout << "HighPart: " << prop->li.HighPart << std::endl;

                    DWORD shift = prop->cbLength;
                    ptr += sizeof(CLUSPROP_VALUE) + shift;
                    std::wcout << "shift of " << sizeof(ULARGE_INTEGER) + shift << " bytes" << std::endl;
                    break;
                }
                case CLUSTER_PROPERTY_SYNTAX::CLUSPROP_SYNTAX_DISK_NUMBER: //pass
                {
                    CLUSPROP_DISK_NUMBER* prop = reinterpret_cast<CLUSPROP_DISK_NUMBER*>(const_cast<BYTE*>(ptr));
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
                    return S_OK;
                }

            default:
                std::wcout << "kill yourself" << std::endl;
                std::wcout << std::endl;

                return S_FALSE;
            }

            std::wcout << std::endl;
        }

        return S_OK;
    }

    std::wcout << "fail" << std::endl;

    return S_FALSE;
}