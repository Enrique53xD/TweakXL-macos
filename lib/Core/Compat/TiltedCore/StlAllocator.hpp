#pragma once
// Minimal TiltedCore stub for macOS — falls back to standard new/delete.
#include <memory>
#include <type_traits>

namespace TiltedPhoques
{
template<class T>
using StlAllocator = std::allocator<T>;

template<class T, class... Args>
T* New(Args&&... args)
{
    return new T(std::forward<Args>(args)...);
}

template<class T>
void Delete(T* ptr)
{
    delete ptr;
}

template<class T>
void Delete(T* ptr, std::size_t)
{
    delete[] ptr;
}
} // namespace TiltedPhoques
