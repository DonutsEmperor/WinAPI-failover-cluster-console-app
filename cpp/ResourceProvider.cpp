#include "Cluster.h"
#include "ResourceProvider.h"

ResourceProvider::ResourceProvider(PCluster cluster) : Provider<Resource>(cluster) {}

HRESULT ResourceProvider::GetResourceDisksInfo(MyDiskInfo& diskInfo, Resource& resource) const {
    if (resource.resTypeName != L"Physical Disk")
        return S_FALSE;

    std::list<Resource>::iterator required = std::find_if(mCluster->mResources.begin(),
        mCluster->mResources.end(), [resource](const Resource& res) {
            return (res.properties.itemId == resource.properties.itemId);
        });

    if (required != mCluster->mResources.end()) {
        diskInfo = required->diskInfo;
        return S_OK;
    }

    return S_FALSE;
}