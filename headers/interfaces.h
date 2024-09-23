#include <windows.h>
#include <iostream>

#include "ClusAPI.h"
#include "cluadmex.h"
#include "classes.h"

class IClusDataProvider
{
    PCluster mCluster;
    ULONG mRefCount;

public:
    IClusDataProvider() : mRefCount(1)
    {
        HCLUSTER hCluster = OpenCluster(NULL);
        mCluster = new Cluster(hCluster, (L"localhost"));
    }

    IClusDataProvider(std::wstring clusterName) : mRefCount(1)
    {
        HCLUSTER hCluster = OpenCluster(clusterName.c_str());
        mCluster = new Cluster(hCluster, clusterName);
    }

    ~IClusDataProvider() 
    {
        delete mCluster;
    }

    virtual HCLUSTER GetClusterHandle() const 
    {
        return mCluster->mPCluster;
    }

    HRESULT GetClusterInfo(std::wstring& clusterName, LPCLUSTERVERSIONINFO) const
    {
        clusterName = mCluster->mCName;
        return S_OK;
    }

    HRESULT GetClusterName(std::wstring& clusterName) const
    {
        clusterName = mCluster->mCName;
        return S_OK;
    }

    HRESULT GetClusterState(DWORD* pdwClusterState) const
    {
        if (pdwClusterState == nullptr) {
            return E_POINTER;
        }

        DWORD objectErrorCode = GetNodeClusterState(mCluster->mCName.c_str(), pdwClusterState);

        if (!pdwClusterState) 
        {
            std::wcout << "Error with cluster status!" << std::endl;
            return HRESULT_FROM_WIN32(objectErrorCode);
        }

        return S_OK;
    }

    HRESULT GetClusterNodes(std::list<Node>& clusterNodes) const
    {
        clusterNodes = mCluster->mNodes;
        return S_OK;
    }

    HRESULT GetClusterResources(std::list<Resource>& clusterNodes) const
    {
        clusterNodes = mCluster->mResources;
        return S_OK;
    }

    HRESULT GetClusterGroups(std::list<Group>& clusterNodes) const
    {
        clusterNodes = mCluster->mGroups;
        return S_OK;
    }

    HRESULT GetClusterResTypes(std::list<ResType>& clusterResTypes) const
    {
        clusterResTypes = mCluster->mResTypes;
        return S_OK;
    }

    HRESULT GetClusterNetworks(std::list<Network>& clusterNetworks) const
    {
        clusterNetworks = mCluster->mNetworks;
        return S_OK;
    }

    HRESULT GetClusterNetInterfaces(std::list<NetInterface>& clusterNetInterfaces) const
    {
        clusterNetInterfaces = mCluster->mNetInterfaces;
        return S_OK;
    }

    HRESULT GetClusterSharedVolumes(std::list<SharedVolume>& clusterSharedVolumes) const
    {
        clusterSharedVolumes = mCluster->mCSVs;
        return S_OK;
    }
};

