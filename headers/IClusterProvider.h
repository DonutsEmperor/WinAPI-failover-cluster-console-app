class IClusterProvider {
public:
    virtual ~IClusterProvider() {}
    virtual HRESULT MyOpenCluster(const std::wstring&) = 0;
    virtual void MyCloseCluster() const = 0;

    virtual HCLUSTER GetClusterHandle() const = 0;
    virtual HRESULT GetClusterName(std::wstring&) const = 0;
    virtual HRESULT GetClusterState(DWORD*) const = 0;
};

class ClusterProvider;
