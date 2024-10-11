#include "Cluster.h"
#include "GroupProvider.h"

GroupProvider::GroupProvider(PCluster cluster) : Provider<Group>(cluster) {}

void GroupProvider::AddNewGroup(std::wstring name, CLUSGROUP_TYPE type) {

    CLUSTER_CREATE_GROUP_INFO clusterInfo = {
        .dwVersion = 1,
        .groupType = type
    };

	HGROUP handler = CreateClusterGroupEx(mCluster->mHandler, name.c_str(), &clusterInfo);

    //Group(mCluster, )
}
