class Node : public ClusterObject {
    HNODE mPNode;
public:
    CLUSTER_NODE_STATE state;

    Node(const PCluster pCluster, const PCLUSTER_ENUM_ITEM pWinStruct)
        : ClusterObject(pCluster, pWinStruct) {
        mPNode = OpenClusterNode(pCluster->mPCluster, pWinStruct->lpszName);
        state = GetClusterNodeState(mPNode);
    }
    ~Node() {
        CloseClusterNode(mPNode);
    }
};
