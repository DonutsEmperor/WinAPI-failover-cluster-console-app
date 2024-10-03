#include <windows.h>
#include <string>

#include "ClusApi.h"
#include "../headers/Cluster.h"

HRESULT Resource::GetClusterType() 
{
    mPResource = OpenClusterResource(cluster->mPCluster, properties.itemName.c_str());

    DWORD initialSizeOfBuffer = 64, returnedSizeOfBuffer = 0;
    LPVOID buffer = malloc(sizeof(WCHAR) * initialSizeOfBuffer);

    DWORD errorcode = ClusterResourceControl(mPResource,
        nullptr, CLUSCTL_RESOURCE_GET_RESOURCE_TYPE,
        nullptr, 0, buffer,
        initialSizeOfBuffer,
        &returnedSizeOfBuffer);

    if (returnedSizeOfBuffer > initialSizeOfBuffer) 
    {
        buffer = realloc(buffer, returnedSizeOfBuffer);

        errorcode = ClusterResourceControl(mPResource,
            nullptr, CLUSCTL_RESOURCE_GET_RESOURCE_TYPE,
            nullptr, 0, buffer,
            returnedSizeOfBuffer,
            &returnedSizeOfBuffer);
    }

    if (buffer) {
        resTypeName = reinterpret_cast<LPCWSTR>(buffer);
    }
    else {
        return S_FALSE;
    }

    free(buffer);
    CloseClusterResource(mPResource);

    return S_OK;
}