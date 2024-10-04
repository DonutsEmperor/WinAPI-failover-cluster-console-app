#pragma once

class IGroupProvider {
public:
    virtual ~IGroupProvider() {}
    virtual HRESULT GetClusterGroups(std::list<Group>&) const = 0;
    virtual HRESULT AddGroup(const Group&) = 0;
};

class GroupProvider : public IGroupProvider {
    PCluster mCluster;
public:
    GroupProvider(PCluster);

    ~GroupProvider() override;
    HRESULT GetClusterGroups(std::list<Group>&) const override;
    HRESULT AddGroup(const Group&) override;
};
