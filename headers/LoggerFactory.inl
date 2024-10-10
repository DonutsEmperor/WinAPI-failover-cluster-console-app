

template <typename T>
static std::unique_ptr<ILogger<T>> LoggerFactory::CreateLogger() {
    if constexpr (std::is_same_v<T, Cluster>) {
        return std::make_unique<ClusterLogger>();
    }
    else if constexpr (std::is_same_v<T, Node>) {
        return std::make_unique<NodeLogger>();
    }
    else if constexpr (std::is_same_v<T, Resource>) {
        return std::make_unique<ResourceLogger>();
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
        //static_assert(false, "Unsupported logger type");
        return std::unique_ptr<ILogger<T>>();
    }
}
