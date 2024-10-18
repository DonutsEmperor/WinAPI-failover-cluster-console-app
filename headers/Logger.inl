
template <typename T>
void Logger<T>::LogOneBase(const T& item) const {
    if constexpr (!std::is_same_v<T, Cluster>) {
        std::wcout << "Item Id        [" << item.properties.itemId << "]\n";
        std::wcout << "Item Name      [" << item.properties.itemName << "]\n";
        std::wcout << "Item Size      [" << item.properties.byteSizeName << "]\n";
        std::wcout << "Item Version   [" << item.properties.version << "]\n\n";
    }
}

template <typename T>
void Logger<T>::LogOneSpecial(const T& item) const {
    if constexpr (std::is_same_v<T, Node>) {
        std::wcout << "Node Id   [" << item.properties.itemId << "]\n";
        std::wcout << "Node Name [" << item.properties.itemName << "]\n";
        std::wcout << "Name Size [" << item.properties.byteSizeName << "]\n\n";
    }
    else if constexpr (std::is_same_v<T, Resource>) {
        std::wcout << "Resource Name         [" << item.properties.itemName << "]\n";
        std::wcout << "Resource ResType Name [" << item.resTypeName << "]\n\n";
    }
    else if constexpr (std::is_same_v<T, Group>) {
        std::wcout << "Group Name [" << item.properties.itemName << "] \n";
    }
    else if constexpr (std::is_same_v<T, ResourceType>) {
        std::wcout << "ResType Name [" << item.properties.itemName << "] \n";
    }
    else if constexpr (std::is_same_v<T, Network>) {
        std::wcout << "Network Name [" << item.properties.itemName << "] \n";
    }
    else if constexpr (std::is_same_v<T, NetInterface>) {
        std::wcout << "NetInterface Name [" << item.properties.itemName << "] \n";
    }
    else if constexpr (std::is_same_v<T, SharedVolume>) {
        std::wcout << "SharedVolume Name [" << item.properties.itemName << "] \n";
    }
}

template <typename T>
void Logger<T>::LogListBase(const std::list<T>& items) const {
    if constexpr (!std::is_same_v<T, Cluster>) {
        IterateItems(items, [this](const T& item) {
            LogOneBase(item);
            });
    }
}

template <typename T>
void Logger<T>::LogListSpecial(const std::list<T>& items) const {
    if constexpr (!std::is_same_v<T, Cluster>) {
        IterateItems(items, [this](const T& item) {
            LogOneSpecial(item);
            });
    }
}

template <typename T>
void Logger<T>::IterateItems(const std::list<T>& items, std::function<void(const T&)> displayFunc) const {
    std::wcout << "Start iteration of items! \n";
    for (const T& item : items) {
        displayFunc(item);
    }
    std::wcout << "Finish! \n" << std::endl;
}