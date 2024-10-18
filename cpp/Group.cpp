#include "Cluster.h"

Group::Group(const PCluster pCluster, const PCLUSTER_ENUM_ITEM pWinStruct)
    : BaseObject(pCluster, pWinStruct) {
    mPGroup = OpenClusterGroup(pCluster->mHandler, pWinStruct->lpszName);
}
Group::~Group() {
    CloseClusterGroup(mPGroup);
}