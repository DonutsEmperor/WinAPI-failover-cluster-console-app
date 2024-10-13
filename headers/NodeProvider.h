#pragma once
#include "Provider.h"

class NodeProvider : public Provider<Node> {
public:
    explicit NodeProvider(PCluster );
    HRESULT GetNodeStatus(const std::wstring& , DWORD* ) const;
};