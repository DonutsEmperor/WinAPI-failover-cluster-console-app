#pragma once
#include "IProvider.h"

#ifndef PROVIDER_H
#define PROVIDER_H

template <typename T>
class Provider : public IProvider<T> {

protected:
    PCluster mCluster;

public:
    explicit Provider(PCluster cluster) : mCluster(cluster) {}
    virtual ~Provider() = default;

    HRESULT GetAll(std::list<T>&) const override;
    HRESULT GetItem(const std::wstring&, T*&) const override;

protected:
    HRESULT GetIterator(const std::wstring& name, T*& iter) const;
};

#include "Provider.inl"
#endif