#pragma once

class IClusterProvider {
public:
    virtual ~IClusterProvider() {}

    virtual HCLUSTER GetClusterHandle() const = 0;
    virtual HRESULT GetClusterName(std::wstring&) const = 0;
    virtual HRESULT GetClusterState(DWORD*) const = 0;
};

class ClusterProvider : public IClusterProvider {
    PCluster mCluster;
public:
    ClusterProvider(PCluster);
    ~ClusterProvider() override;

    HCLUSTER GetClusterHandle() const override;
    HRESULT GetClusterName(std::wstring&) const override;
    HRESULT GetClusterState(DWORD*) const override;
};
