#pragma once

template <typename T>
class IProvider {
public:
    virtual ~IProvider() = default;

    virtual HRESULT GetAll(std::list<T>& items) const = 0;
    virtual HRESULT GetById(const std::wstring& id, T& item) const = 0;
};