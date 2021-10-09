#pragma once

#include "array.h"

#include <cassert>
#include <utility>

namespace NRenderer {

template <typename T>
TPlain2DArray<T>::TPlain2DArray(int64_t width, int64_t height, T value) : Width_(width), Height_(height), Data_(Width_ * Height_, std::move(value)) {
}

template <typename T>
auto TPlain2DArray<T>::Data() -> T* {
    return Data_.data();
}

template <typename T>
auto TPlain2DArray<T>::Data() const -> const T* {
    return Data_.data();
}

template <typename T>
auto TPlain2DArray<T>::operator()(int64_t column, int64_t row) -> T& {
    return Data_[TransformIndex(column, row)];
}

template <typename T>
auto TPlain2DArray<T>::operator()(int64_t column, int64_t row) const -> const T& {
    return Data_[TransformIndex(column, row)];
}

template <typename T>
auto TPlain2DArray<T>::operator[](int64_t column) -> typename TPlain2DArray<T>::TRowProxy {
    assert(column < Width_);
    return {column, this};
}

template <typename T>
auto TPlain2DArray<T>::operator[](int64_t column) const -> typename TPlain2DArray<T>::TConstRowProxy {
    assert(column < Width_);
    return {column, this};
}

template <typename T>
auto TPlain2DArray<T>::TConstRowProxy::operator[](int64_t row) const -> const T& {
    return (*Arr)(Column, row);
}

template <typename T>
auto TPlain2DArray<T>::TRowProxy::operator[](int64_t row) const -> T& {
    return (*Arr)(Column, row);
}

template <typename T>
auto TPlain2DArray<T>::Begin() {
    return Data_.begin();
}

template <typename T>
auto TPlain2DArray<T>::Begin() const {
    return Data_.begin();
}

template <typename T>
auto TPlain2DArray<T>::End() {
    return Data_.end();
}

template <typename T>
auto TPlain2DArray<T>::End() const {
    return Data_.end();
}

template <typename T>
auto TPlain2DArray<T>::TransformIndex(int64_t column, int64_t row) const -> int64_t {
    assert(0 <= row && row < Height_ && 0 <= column && column < Width_);
    return column * Height_ + row;
}

}  // namespace NRenderer
