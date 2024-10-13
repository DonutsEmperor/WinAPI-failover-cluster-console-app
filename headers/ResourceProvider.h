#pragma once
#include "Provider.h"

class ResourceProvider : public Provider<Resource> {
public:
    explicit ResourceProvider(PCluster );
    HRESULT GetPhysicalDiskResources(std::list<Resource>& ) const;
};
