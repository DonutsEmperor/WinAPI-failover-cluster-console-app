#pragma once

class NodeProvider;

class Node : public BaseObject {
    HNODE mPNode;
public:
    CLUSTER_NODE_STATE state;

    Node() : BaseObject(), mPNode(nullptr) {}
    Node(const PCluster pCluster, const PCLUSTER_ENUM_ITEM pWinStruct);
    ~Node();

    friend class NodeProvider;
};
