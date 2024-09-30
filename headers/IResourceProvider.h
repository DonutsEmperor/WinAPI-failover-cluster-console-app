class IResourceProvider {
public:
    virtual ~IResourceProvider() {}
    virtual HRESULT GetClusterResources(std::list<Resource>&) const = 0;
    virtual HRESULT AllocateResource(const Resource&) = 0;
};

class ResourceProvider;
