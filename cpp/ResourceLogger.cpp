#include "Cluster.h"
#include "ResourceLogger.h"

HRESULT ResourceLogger::LogPhysicalDiskInfo(const PhysicalDiskInfo* info) const {

    std::wcout << "Disk number " << info->diskNumb.dw << std::endl;
    switch (info->dwType)
    {
        case DiskType::MRB:
            std::wcout << "Disk type is MRB" << std::endl;
            break;
        case DiskType::GPT:
            std::wcout << "Disk type is GPT" << std::endl;
            break;
        case DiskType::UNKNOWN:
            std::wcout << "Disk type is Unknown" << std::endl;
            break;
        default:
            break;
    }

    std::wcout << std::endl << "Disk Variant" << std::endl;
    LogPhysicalDiskInfo_Variant(info->data);

    std::wcout << std::endl << "Disk Ularge" << std::endl;
    LogPhysicalDiskInfo_Ularge(info->diskSize.li);

    std::wcout << std::endl << "Disk PartiotionInfo" << std::endl;
    LogPhysicalDiskInfo_PartitionInfo(info->partitionInfo.get());

    std::wcout << std::endl << "Disk ScsiAddress" << std::endl;
    LogPhysicalDiskInfo_ScsiAddress(info->scsi);

    std::wcout << std::endl;

    return S_OK;
}

void ResourceLogger::LogPhysicalDiskInfo_Variant(const std::variant<DWORD, std::wstring>& variant) const {
    if (const std::wstring* str = std::get_if<std::wstring>(&variant)) {
        std::wcout << L"Variant wstring:    [" << *str << "]" << std::endl;
    }
    else {
        const DWORD* number = std::get_if<DWORD>(&variant);
        std::wcout << "Variant dword:       [" << *number << "]" << std::endl;
    }
}

void ResourceLogger::LogPhysicalDiskInfo_Ularge(const ULARGE_INTEGER& ularge) const {
    std::wcout << "QuadPart:          [" << ularge.QuadPart << "]" << std::endl;
    std::wcout << "HighPart:          [" << ularge.HighPart << "]" << std::endl;
    std::wcout << "LowPart:           [" << ularge.LowPart << "]" << std::endl;
}

void ResourceLogger::LogPhysicalDiskInfo_PartitionInfo(const CLUSPROP_PARTITION_INFO_EX* info) const {
    std::wcout << "DeviceNumber:      [" << info->DeviceNumber << "]" << std::endl;
    std::wcout << "DwFileSystemFlags: [" << info->dwFileSystemFlags << "]" << std::endl;
    std::wcout << "dwFlags:           [" << info->dwFlags << "]" << std::endl;
    std::wcout << "dwSerialNumber:    [" << info->dwSerialNumber << "]" << std::endl;
    LogPhysicalDiskInfo_Ularge(info->FreeSizeInBytes);

    std::wcout << "PartitionNumber:   [" << info->PartitionNumber << "]" << std::endl;
    std::wcout << "RgdwMaxCompLength: [" << info->rgdwMaximumComponentLength << "]" << std::endl;
    std::wcout << "szDeviceName:      [" << info->szDeviceName << "]" << std::endl;
    std::wcout << "szFileSystem:      [" << info->szFileSystem << "]" << std::endl;
    std::wcout << "szVolumeLabel:     [" << info->szVolumeLabel << "]" << std::endl;

    LogPhysicalDiskInfo_Ularge(info->TotalSizeInBytes);
    std::wcout << "VolumeGuid1:       [" << info->VolumeGuid.Data1 << "]" << std::endl;
    std::wcout << "VolumeGuid2:       [" << info->VolumeGuid.Data2 << "]" << std::endl;
    std::wcout << "VolumeGuid3:       [" << info->VolumeGuid.Data3 << "]" << std::endl;
    std::wcout << "VolumeGuid4:       [" << info->VolumeGuid.Data4 << "]" << std::endl;
}

void ResourceLogger::LogPhysicalDiskInfo_ScsiAddress(const CLUSPROP_SCSI_ADDRESS& scsi) const {
    std::wcout << "Lun:               [" << scsi.Lun << "]" << std::endl;
    std::wcout << "PathId:            [" << scsi.PathId << "]" << std::endl;
    std::wcout << "PortNumber:        [" << scsi.PortNumber << "]" << std::endl;
    std::wcout << "TargetId:          [" << scsi.TargetId << "]" << std::endl;
}