class Group : public ClusterObject {
    HGROUP mPGroup;
public:
    std::wstring csvName;

    Group(const PCluster pCluster, const PCLUSTER_ENUM_ITEM pWinStruct) 
        : ClusterObject(pCluster, pWinStruct) {
        mPGroup = OpenClusterGroup(pCluster->mPCluster, pWinStruct->lpszName);
    }
    ~Group() {
        CloseClusterGroup(mPGroup);
    }
};
