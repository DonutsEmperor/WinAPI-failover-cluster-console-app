#pragma once
#include "Provider.h"

class ResourceProvider : public Provider<Resource> {
public:
    explicit ResourceProvider(PCluster cluster);
    HRESULT GetResourceDisksInfo(MyDiskInfo& diskInfo, Resource& resource) const;
};
