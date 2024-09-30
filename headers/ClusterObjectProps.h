class ClusterObjectProps {
public:
    DWORD version;
    DWORD type;
    DWORD byteSizeId;
    std::wstring itemId;
    DWORD byteSizeName;
    std::wstring itemName;

    ClusterObjectProps() : version(0), type(0), byteSizeId(0), byteSizeName(0) {}
    ClusterObjectProps(const CLUSTER_ENUM_ITEM& winStruct)
        : version(winStruct.dwVersion), type(winStruct.dwType),
        byteSizeId(winStruct.cbId), byteSizeName(winStruct.cbName) {
        itemId = winStruct.lpszId;
        itemName = winStruct.lpszName;
    }
};
