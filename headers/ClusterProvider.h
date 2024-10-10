#pragma once
#include "Provider.h"

class ClusterProvider : public Provider<Cluster>{
public:
    explicit ClusterProvider(PCluster cluster);

    HCLUSTER GetClusterHandle() const;
    HRESULT GetClusterName(std::wstring&) const;
    HRESULT GetClusterState(DWORD*) const;

    HRESULT UpdateClusterLists() const;/////////////////
    HRESULT UpdateClusterListByType(DWORD) const;///////
};
