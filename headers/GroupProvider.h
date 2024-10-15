#pragma once
#include "Provider.h"

class GroupProvider : public Provider<Group> {
public:
    explicit GroupProvider(PCluster);

    HRESULT AddNewGroup(const std::wstring&, const CLUSGROUP_TYPE) const;
    HRESULT DeleteGroup(Group*&) const;
};