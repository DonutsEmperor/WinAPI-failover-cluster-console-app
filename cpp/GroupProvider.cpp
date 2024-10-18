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
    //std::wcout << "Old handler: " << group.mPGroup << std::endl;
    //group.OpenHandler();

    std::list<Group>::iterator required;
    HRESULT hr = this->GetIterator(group.properties.itemName, required);

    if (SUCCEEDED(hr))
        if (required != mCluster->mGroups.end()) {
            // fix this logic
            //std::wcout << "New handler: " << group.mPGroup << std::endl;
            //hr = DestroyClusterGroup(group.mPGroup);
            //hr = DeleteClusterGroup(group.mPGroup);
            mCluster->mGroups.erase(required);
        }

    group.CloseHandler();

    if (SUCCEEDED(hr))
        return S_OK;

    return hr;
}