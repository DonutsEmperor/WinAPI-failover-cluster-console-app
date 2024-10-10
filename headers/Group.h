#pragma once

class Group : public BaseObject {
    HGROUP mPGroup;
public:
    std::wstring csvName;

    Group(const PCluster pCluster, const PCLUSTER_ENUM_ITEM pWinStruct) 
        : BaseObject(pCluster, pWinStruct) {
        mPGroup = OpenClusterGroup(pCluster->mHandler, pWinStruct->lpszName);
    }
    ~Group() {
        CloseClusterGroup(mPGroup);
    }
};
