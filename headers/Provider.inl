
template <typename T>
HRESULT Provider<T>::GetAll(std::list<T>& items) const {
    if constexpr (std::is_same_v<T, Node>) {
        items = mCluster->mNodes;
    }
    else if constexpr (std::is_same_v<T, Resource>) {
        items = mCluster->mResources;
    }
    else if constexpr (std::is_same_v<T, Group>) {
        items = mCluster->mGroups;
    }
    else if constexpr (std::is_same_v<T, ResourceType>) {
        items = mCluster->mResTypes;
    }
    else if constexpr (std::is_same_v<T, Network>) {
        items = mCluster->mNetworks;
    }
    else if constexpr (std::is_same_v<T, NetInterface>) {
        items = mCluster->mNetInterfaces;
    }
    else if constexpr (std::is_same_v<T, SharedVolume>) {
        items = mCluster->mCSVs;
    }
    else {
        return S_FALSE;
    }
    return S_OK;
}

template <typename T>
HRESULT Provider<T>::GetAllPtr(std::list<T>*& items) const {
    if constexpr (std::is_same_v<T, Node>) {
        items = &mCluster->mNodes;
    }
    else if constexpr (std::is_same_v<T, Resource>) {
        items = &mCluster->mResources;
    }
    else if constexpr (std::is_same_v<T, Group>) {
        items = &mCluster->mGroups;
    }
    else if constexpr (std::is_same_v<T, ResourceType>) {
        items = &mCluster->mResTypes;
    }
    else if constexpr (std::is_same_v<T, Network>) {
        items = &mCluster->mNetworks;
    }
    else if constexpr (std::is_same_v<T, NetInterface>) {
        items = &mCluster->mNetInterfaces;
    }
    else if constexpr (std::is_same_v<T, SharedVolume>) {
        items = &mCluster->mCSVs;
    }
    else {
        return S_FALSE;
    }
    return S_OK;
}

template <typename T>
HRESULT Provider<T>::GetItem(const std::wstring& name, T& item) const {

    if constexpr (!std::is_same_v<T, Cluster>) {
        typename std::list<T>::iterator required;
        HRESULT hr = this->GetIterator(name, required);

        if (SUCCEEDED(hr)) {
            item = *required;
            return S_OK;
        }
    }

    return S_FALSE;
}

template <typename T>
HRESULT Provider<T>::GetIterator(const std::wstring& name, std::list<T>::iterator& iter) const {
    std::list<T>* items = nullptr;
    HRESULT hr = this->GetAllPtr(items);

    if (FAILED(hr)) 
        return hr;

    typename std::list<T>::iterator iterator = std::find_if(items->begin(), items->end(),
        [&name](const T& item) {
            if constexpr (!std::is_same_v<T, Cluster>) {
                return (item.properties.itemName == name);
            }
            return false;
        });

    if (iterator == items->end())
        return S_FALSE;

    if constexpr (!std::is_same_v<T, Cluster>) {
        iter = iterator;
    }

    return S_OK;
};