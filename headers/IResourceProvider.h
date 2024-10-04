#pragma once

class IResourceProvider {
public:
    virtual ~IResourceProvider() {}
    virtual HRESULT GetClusterResources(std::list<Resource>&) const = 0;
    virtual HRESULT AllocateResource(const Resource&) = 0;
};

class ResourceProvider : public IResourceProvider {
    PCluster mCluster;
public:
    ResourceProvider(PCluster);
    ~ResourceProvider() override;

    HRESULT GetClusterResources(std::list<Resource>& ) const override;
    HRESULT GetResourceDisksInfo(MyDiskInfo& , Resource& ) const;
    HRESULT AllocateResource(const Resource& ) override;
};
