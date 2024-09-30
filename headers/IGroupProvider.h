class IGroupProvider {
public:
    virtual ~IGroupProvider() {}
    virtual HRESULT GetClusterGroups(std::list<Group>&) const = 0;
    virtual HRESULT AddGroup(const Group&) = 0;
};

class GroupProvider;
