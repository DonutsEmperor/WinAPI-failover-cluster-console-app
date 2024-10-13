#include "Cluster.h"
#include "GroupProvider.h"

GroupProvider::GroupProvider(PCluster cluster) : Provider<Group>(cluster) {}

HRESULT GroupProvider::AddNewGroup(const std::wstring& name, const CLUSGROUP_TYPE type) const {

    CLUSTER_CREATE_GROUP_INFO clusterInfo = {
        .dwVersion = 1,
        .groupType = type
    };
	HGROUP handler = CreateClusterGroupEx(mCluster->mHandler, name.c_str(), &clusterInfo);

    if (!handler)
        return S_FALSE;

    mCluster->UpdateSpecificList(CLUSTER_ENUM_GROUP);
    return S_OK;
}

HRESULT GroupProvider::DeleteGroup(Group& group) const {

    DWORD error = DeleteClusterGroup(group.mPGroup);

    if (!error)
        return S_FALSE;

    std::list<Group>::iterator required = std::find_if(mCluster->mGroups.begin(),
        mCluster->mGroups.end(), [&group](const Group& g) {
            return (g.properties.itemName == group.properties.itemName);
        });

    if (required == mCluster->mGroups.end()) {
        mCluster->mGroups.erase(required);
        return S_OK;
    }

    return S_FALSE;
}

HRESULT GroupProvider::FindGroupByName(const std::wstring& name, Group& group) const {

    std::list<Group>::iterator required = std::find_if(mCluster->mGroups.begin(), // rewrite as generic method for findign ITERATOR
        mCluster->mGroups.end(), [&name](const Group& g) {      
            return (g.properties.itemName == name);
        });

    if (required == mCluster->mGroups.end()) {
        group = *required;
        return S_OK;
    }

    return S_FALSE;
}