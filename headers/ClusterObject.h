class ClusterObject {
protected:
    DWORD mErrorHandler;
public:
    PCluster cluster;
    ClusterObjectProps properties;

    ClusterObject(const PCluster hCluster, const PCLUSTER_ENUM_ITEM lProperties)
        : cluster(hCluster), properties(*lProperties), mErrorHandler(0) {}
};