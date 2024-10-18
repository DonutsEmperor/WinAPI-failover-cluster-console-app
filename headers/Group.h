#pragma once

class GroupProvider;

class Group : public BaseObject {
private:
    HGROUP mPGroup;
public:
    //std::wstring csvName;

    Group() : BaseObject(), mPGroup(nullptr) {};
    Group(const PCluster pCluster, const PCLUSTER_ENUM_ITEM pWinStruct);
    ~Group();

protected:
    HRESULT OpenHandler() override;
    HRESULT CloseHandler() override;

    friend class GroupProvider;
};
