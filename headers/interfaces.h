#include <windows.h>
#include <iostream>

#include "ClusAPI.h"
#include "cluadmex.h"
#include "classes.h"

class IClusDataProvider : public IGetClusterDataInfo
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

    virtual HRESULT __stdcall GetClusterName(const BSTR lpszName, LONG* pcchName) override
    {
        if (lpszName == nullptr || pcchName == nullptr) {
            return E_POINTER;
        }

        size_t bufferSize = *pcchName;

        size_t mpcchName = mCluster->mCName.size() + 1; // Adding 1 for the null terminator
        if (bufferSize < mpcchName) {
            *pcchName = mpcchName;
            return HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER);
        }

        wcscpy_s(lpszName, bufferSize, mCluster->mCName.c_str());

        *pcchName = mpcchName - 1; // Excluding the null terminator
        return S_OK;
    }

    virtual HCLUSTER __stdcall GetClusterHandle() override
    {
        return mCluster->mPCluster;
    }

    virtual LONG __stdcall GetObjectCount() override
    {
        return 1;
    }

    HRESULT GetClusterState(DWORD* pdwClusterState) const
    {
        if (pdwClusterState == nullptr) {
            return E_POINTER;
        }

        DWORD objectErrorCode = GetNodeClusterState(mCluster->mCName.c_str(), pdwClusterState);

        if (!pdwClusterState) 
        {
            std::wcout << "ERROR GETTING CLUSTER STATE!!!" << std::endl;
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

    // Override the QueryInterface function of IUnknown
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override
    {
        // Implement QueryInterface as needed if you have additional interfaces to expose
        // ...
        return E_NOINTERFACE; // Replace with appropriate return value
    }

    // Override the AddRef function of IUnknown
    virtual ULONG __stdcall AddRef() override
    {
        return InterlockedIncrement(&mRefCount); // Increment reference count and return the new value
    }

    // Override the Release function of IUnknown
    virtual ULONG __stdcall Release() override
    {
        ULONG count = InterlockedDecrement(&mRefCount); // Decrement reference count
        if (count == 0)
        {
            delete this; // If reference count reaches 0, delete the object
        }
        return count;
    }
};

