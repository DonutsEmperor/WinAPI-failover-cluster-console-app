#include "pch.h"

class GroupProvider : public IGroupProvider {
    PCluster mCluster;
public:
    GroupProvider(PCluster pCluster) : mCluster(pCluster) {}
    ~GroupProvider() override {};
    HRESULT GetClusterGroups(std::list<Group>& groups) const override {
        //groups = mCluster->mGroups;
        return S_OK;
    }
    HRESULT AddGroup(const Group& group) override = 0;
};