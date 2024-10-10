
template <typename T>
HRESULT Provider<T>::GetAll(std::list<T>& items) const {
    return S_OK;
}

template <typename T>
HRESULT Provider<T>::GetById(const std::wstring& id, T& item) const {
    return S_OK;
}