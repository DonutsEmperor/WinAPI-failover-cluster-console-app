#include <windows.h>
#include <iostream>

#include "ClusAPI.h"
#include "cluadmex.h"
#include "classes.h"

class GetClusterDataInfo : public IGetClusterDataInfo
{
    const Cluster* m_cluster;
    ULONG m_refCount;
public:

    GetClusterDataInfo() : m_refCount(1)    //const_cast<LPWSTR>(L"localhost") 
    {
        HCLUSTER hCluster = OpenCluster((L"localhost"));
        m_cluster = new Cluster(hCluster, (L"localhost"));
    }

    GetClusterDataInfo(std::wstring clusterName) : m_refCount(1)
    {
        HCLUSTER hCluster = OpenCluster(clusterName.c_str());
        m_cluster = new Cluster(hCluster, clusterName);
    }

    ~GetClusterDataInfo() 
    {
        CloseCluster(m_cluster->m_pCluster);
        delete m_cluster;
    }

    virtual HRESULT __stdcall GetClusterName(BSTR lpszName, LONG* pcchName) override
    {
        size_t sizeOfClus = m_cluster->m_clusterName.size();

        for (unsigned int i = 0; i < sizeOfClus; ++i)
            lpszName[i] = m_cluster->m_clusterName[i];

        *pcchName = sizeOfClus;
        return S_OK;
    }

    virtual HCLUSTER __stdcall GetClusterHandle() override
    {
        return m_cluster->m_pCluster;
    }

    virtual LONG __stdcall GetObjectCount() override
    {
        return 1;
    }

    HRESULT GetClusterState(DWORD& pdwClusterState) const
    {
        DWORD objectErrorCode = GetNodeClusterState(m_cluster->m_clusterName.c_str(), &pdwClusterState);

        if (!pdwClusterState) 
        {
            std::wcout << "ERROR CLUSTER STATE!!!" << std::endl;
            return S_FALSE;
        }

        return S_OK;
    }

    HRESULT GetClusterNodes(const std::list<Node>* clusterNodes) const
    {
        clusterNodes = &(m_cluster->m_nodes);
        return S_OK;
    }

    HRESULT GetClusterResources(const std::list<Resource>* clusterNodes) const
    {
        clusterNodes = &(m_cluster->m_resourses);
        return S_OK;
    }

    HRESULT GetClusterGroups(const std::list<Group>* clusterNodes) const
    {
        clusterNodes = &(m_cluster->m_groups);
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
        return InterlockedIncrement(&m_refCount); // Increment reference count and return the new value
    }

    // Override the Release function of IUnknown
    virtual ULONG __stdcall Release() override
    {
        ULONG count = InterlockedDecrement(&m_refCount); // Decrement reference count
        if (count == 0)
        {
            delete this; // If reference count reaches 0, delete the object
        }
        return count;
    }
};

