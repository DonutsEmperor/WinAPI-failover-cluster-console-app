
template <typename T>
static std::unique_ptr<IProvider<T>> ProviderFactory::CreateProvider(PCluster cluster) {
    if constexpr (std::is_same_v<T, Cluster>) {
        return std::make_unique<ClusterProvider>(cluster);
    }
    else if constexpr (std::is_same_v<T, Node>) {
        return std::make_unique<NodeProvider>(cluster);
    }
    else if constexpr (std::is_same_v<T, Resource>) {
        return std::make_unique<ResourceProvider>(cluster);
    }
    /*else if constexpr (std::is_same_v<T, Group>) {
        return std::make_unique<NodeLogger>();
    }
    else if constexpr (std::is_same_v<T, ResourceType>) {
        return std::make_unique<NodeLogger>();
    }
    else if constexpr (std::is_same_v<T, Network>) {
        return std::make_unique<NodeLogger>();
    }
    else if constexpr (std::is_same_v<T, NetInterface>) {
        return std::make_unique<NodeLogger>();
    }
    else if constexpr (std::is_same_v<T, SharedVolume>) {
        return std::make_unique<Logger<SharedVolume>>();
    }*/
    else {
        //static_assert(false, "Unsupported provider type");
        return std::unique_ptr<IProvider<T>>();
    }
}