#include "Cluster.h"

Node::Node(const PCluster pCluster, const PCLUSTER_ENUM_ITEM pWinStruct)
    : BaseObject(pCluster, pWinStruct) {
    mPNode = OpenClusterNode(pCluster->mHandler, pWinStruct->lpszName);
    state = GetClusterNodeState(mPNode);
}
Node::~Node() {
    CloseClusterNode(mPNode);
}

HRESULT Node::UpdateHandler() {
    return S_OK;
}