
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
HRESULT Provider<T>::GetItem(const std::wstring& name, T*& item) const {

    T* required = nullptr;
    HRESULT hr = this->GetIterator(name, required);

    if constexpr (!std::is_same_v<T, Cluster>) {
        std::wcout << L" LOG GetItem\n" << std::endl;
        std::wcout << L"Version: " << required->properties.version << std::endl;
        std::wcout << L"Type: " << required->properties.type << std::endl;
        std::wcout << L"Item Name: " << required->properties.itemName << L" (Length: " << required->properties.itemName.length() << L")" << std::endl;
        std::wcout << L"Item ID: " << required->properties.itemId << L" (Length: " << required->properties.itemId.length() << L")" << std::endl;
    }

    if (SUCCEEDED(hr))
        if constexpr (!std::is_same_v<T, Cluster>) {
            item = const_cast<T*>(&*required);
            std::wcout << L" LOG required after\n" << std::endl;
            std::wcout << required->properties.version << std::endl;
            std::wcout << required->properties.type << std::endl;
            std::wcout << required->properties.itemName << std::endl;
            std::wcout << required->properties.itemId << std::endl;

            std::wcout << L"LOG item" << std::endl;
            std::wcout << item->properties.version << std::endl;
            std::wcout << item->properties.type << std::endl;
            std::wcout << item->properties.itemName << std::endl;
            std::wcout << item->properties.itemId << std::endl;

            return S_OK;
        }

    return S_FALSE;
}

template <typename T>
HRESULT Provider<T>::GetIterator(const std::wstring& name, T*& iter) const {

    std::list<T> items;
    HRESULT hr = this->GetAll(items);

    if (FAILED(hr)) 
        return hr;

    typename std::list<T>::iterator iterator = std::find_if(items.begin(), items.end(),
        [&name](const T& item) {
            if constexpr (!std::is_same_v<T, Cluster>) {
                return (item.properties.itemName == name);
            }
            return false;
        });

    if (iterator == items.end())
        return S_FALSE;

    if constexpr (!std::is_same_v<T, Cluster>) {
        iter = &(*iterator);

        std::wcout << L" LOG GetItem\n" << std::endl;
        std::wcout << L"Version: " << iter->properties.version << std::endl;
        std::wcout << L"Type: " << iter->properties.type << std::endl;
        std::wcout << L"Item Name: " << iter->properties.itemName << L" (Length: " << iter->properties.itemName.length() << L")" << std::endl;
        std::wcout << L"Item ID: " << iter->properties.itemId << L" (Length: " << iter->properties.itemId.length() << L")" << std::endl;
    }

    return S_OK;
};