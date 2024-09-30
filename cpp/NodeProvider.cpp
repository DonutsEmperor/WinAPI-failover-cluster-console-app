#include "../headers/Cluster.h"
#include "../headers/INodeProvider.h"

class NodeProvider : public INodeProvider {
    PCluster mCluster;
public:
    NodeProvider(PCluster pCluster) : mCluster(pCluster) {}
    ~NodeProvider() override {};
    HRESULT GetClusterNodes(std::list<Node>& nodes) const override {
        nodes = mCluster->mNodes;
        return S_OK;
    }
    HRESULT GetNodeStatus(const std::wstring& nodeName, DWORD* status) const override {
        return S_OK;
    }
};