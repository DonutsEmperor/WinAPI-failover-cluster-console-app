#pragma once
#include "Logger.h"

class ResourceLogger : public Logger<Resource> {
public:
	explicit ResourceLogger() = default;
	HRESULT LogPhysicalDiskInfo(const PhysicalDiskInfo* ) const;
private:
	void LogPhysicalDiskInfo_Variant(const std::variant<DWORD, std::wstring>&) const;
	void LogPhysicalDiskInfo_Ularge(const ULARGE_INTEGER& ) const;
	void LogPhysicalDiskInfo_PartitionInfo(const CLUSPROP_PARTITION_INFO_EX*) const;
	void LogPhysicalDiskInfo_ScsiAddress(const CLUSPROP_SCSI_ADDRESS&) const;
};