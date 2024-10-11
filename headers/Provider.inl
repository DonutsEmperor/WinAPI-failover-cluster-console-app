
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
HRESULT Provider<T>::GetById(const std::wstring& id, T& item) const {
    return S_OK;
}