#include "Cluster.h"

Group::Group(const PCluster pCluster, const PCLUSTER_ENUM_ITEM pWinStruct)
    : BaseObject(pCluster, pWinStruct) {
    OpenHandler();
}
Group::~Group() {
    CloseHandler();
}

HRESULT Group::OpenHandler() {
    mPGroup = OpenClusterGroup(cluster->mHandler, properties.itemName.c_str());
    return S_OK;
}
HRESULT Group::CloseHandler() {
    CloseClusterGroup(mPGroup);
    return S_OK;
}