#pragma once

class INodeProvider {
public:
    virtual ~INodeProvider() {}
    virtual HRESULT GetClusterNodes(std::list<Node>&) const = 0;
    virtual HRESULT GetNodeStatus(const std::wstring&, DWORD*) const = 0;
};

//class NodeProvider;
