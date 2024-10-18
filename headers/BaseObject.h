#pragma once

class BaseObject {
protected:
    DWORD mErrorHandler;
public:
    PCluster cluster;
    Properties properties;

    BaseObject() = default;
    BaseObject(const PCluster hCluster, const PCLUSTER_ENUM_ITEM lProperties)
        : cluster(hCluster), properties(*lProperties), mErrorHandler(0) {}

protected:
    virtual HRESULT OpenHandler() = 0;
    virtual HRESULT CloseHandler() = 0;
};