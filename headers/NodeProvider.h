#pragma once
#include "Provider.h"

class NodeProvider : public Provider<Node> {
public:
    explicit NodeProvider(PCluster cluster);
    HRESULT GetNodeStatus(const std::wstring& nodeName, DWORD* status) const;
};