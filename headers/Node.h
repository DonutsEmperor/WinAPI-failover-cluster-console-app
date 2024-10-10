#pragma once

class Node : public BaseObject {
    HNODE mPNode;
public:
    CLUSTER_NODE_STATE state;

    Node(const PCluster pCluster, const PCLUSTER_ENUM_ITEM pWinStruct)
        : BaseObject(pCluster, pWinStruct) {
        mPNode = OpenClusterNode(pCluster->mHandler, pWinStruct->lpszName);
        state = GetClusterNodeState(mPNode);
    }
    ~Node() {
        CloseClusterNode(mPNode);
    }
};
