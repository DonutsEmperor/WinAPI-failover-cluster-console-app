#pragma once

template <typename T>
class IProvider {
public:
    virtual ~IProvider() = default;

    virtual HRESULT GetAll(std::list<T>& ) const = 0;
    virtual HRESULT GetItem(const std::wstring& , T& ) const = 0;

protected:
    virtual HRESULT GetAllPtr(std::list<T>*&) const = 0;
    virtual HRESULT GetIterator(const std::wstring&, std::list<T>::iterator& ) const = 0;
};