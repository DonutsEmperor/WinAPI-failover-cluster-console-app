#include "../headers/Cluster.h"
#include "../headers/IResourceProvider.h"

class ResourceProvider : public IResourceProvider {
    PCluster mCluster;
public:
    ResourceProvider(PCluster pCluster) : mCluster(pCluster) {}
    ~ResourceProvider() override {}

    HRESULT GetClusterResources(std::list<Resource>& resources) const override {
        resources = mCluster->mResources;
        return S_OK;
    }

    HRESULT GetResourceDisksInfo(MyDiskInfo& diskInfo, Resource& resource) const {
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

    HRESULT AllocateResource(const Resource& resource) override {
        return S_OK;
    };
};