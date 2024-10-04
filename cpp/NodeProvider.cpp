#include "Cluster.h"
#include "INodeProvider.h"

NodeProvider::NodeProvider(PCluster pCluster) : mCluster(pCluster) {}
NodeProvider::~NodeProvider() {};

HRESULT NodeProvider::GetClusterNodes(std::list<Node>& nodes) const {
    nodes = mCluster->mNodes;
    return S_OK;
}
HRESULT NodeProvider::GetNodeStatus(const std::wstring& nodeName, DWORD* status) const {
    return S_OK;
}