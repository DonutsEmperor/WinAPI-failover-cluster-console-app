#include "Cluster.h"
#include "ResourceProvider.h"

ResourceProvider::ResourceProvider(PCluster cluster) : Provider<Resource>(cluster) {}

// just for fun now -> so simple condition -> remove this method
HRESULT ResourceProvider::GetPhysicalDiskResources(std::list<Resource>& resources) const {
    for (auto res : mCluster->mResources) {
        if (res.resTypeName == L"Physical Disk") {
            resources.push_back(res);
        }
    }
    return resources.empty() ? S_FALSE : S_OK;
}