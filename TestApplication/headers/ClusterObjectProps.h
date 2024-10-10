#pragma once

class Properties {
public:
    DWORD version;
    DWORD type;
    DWORD byteSizeId;
    std::wstring itemId;
    DWORD byteSizeName;
    std::wstring itemName;

    Properties() : version(0), type(0), byteSizeId(0), byteSizeName(0) {}
    Properties(const CLUSTER_ENUM_ITEM& winStruct)
        : version(winStruct.dwVersion), type(winStruct.dwType),
        byteSizeId(winStruct.cbId), byteSizeName(winStruct.cbName) {
        itemId = winStruct.lpszId;
        itemName = winStruct.lpszName;
    }
};
