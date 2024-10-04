#include "Cluster.h"
#include "IGroupProvider.h"

GroupProvider::GroupProvider(PCluster pCluster) : mCluster(pCluster) {}
GroupProvider::~GroupProvider() {};

HRESULT GroupProvider::GetClusterGroups(std::list<Group>& groups) const {
    groups = mCluster->mGroups;
    return S_OK;
}
HRESULT GroupProvider::AddGroup(const Group& group) {
    return S_OK;
};