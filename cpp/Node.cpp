#include "Cluster.h"

Node::Node(const PCluster pCluster, const PCLUSTER_ENUM_ITEM pWinStruct)
    : BaseObject(pCluster, pWinStruct) {
    OpenHandler();
    state = GetClusterNodeState(mPNode);
}
Node::~Node() {
    CloseHandler();
}

HRESULT Node::OpenHandler() {
    mPNode = OpenClusterNode(cluster->mHandler, properties.itemName.c_str());
    return S_OK;
}
HRESULT Node::CloseHandler() {
    CloseClusterNode(mPNode);
    return S_OK;
}