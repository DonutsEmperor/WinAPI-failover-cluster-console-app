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
    HRESULT AllocateResource(const Resource& resource) override {
        return S_OK;
    };
};