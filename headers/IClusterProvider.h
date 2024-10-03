#pragma once

class IClusterProvider {
public:
    virtual ~IClusterProvider() {}

    virtual HCLUSTER GetClusterHandle() const = 0;
    virtual HRESULT GetClusterName(std::wstring&) const = 0;
    virtual HRESULT GetClusterState(DWORD*) const = 0;
};

class ClusterProvider;
