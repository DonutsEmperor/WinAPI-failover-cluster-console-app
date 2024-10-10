#pragma once

#ifndef PROVIDERFACTORY_H
#define PROVIDERFACTORY_H

class ProviderFactory {
public:
    template <typename T>
    static std::unique_ptr<IProvider<T>> CreateProvider(PCluster);
};

#include "ProviderFactory.inl"
#endif