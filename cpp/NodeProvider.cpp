#include "Cluster.h"
#include "NodeProvider.h"

NodeProvider::NodeProvider(PCluster cluster) : Provider<Node>(cluster) {}

HRESULT NodeProvider::GetNodeStatus(const std::wstring& nodeName, DWORD* status) const {
    return S_OK;
}