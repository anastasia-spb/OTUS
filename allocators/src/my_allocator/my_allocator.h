#pragma once

#include <iostream>
#include <memory>

namespace my_allocator
{

template <class T>
struct MyAllocator
{
  using value_type = T;
  MyAllocator();
  template <class U> MyAllocator (const MyAllocator<U>&);
  T* allocate(std::size_t n);
  void deallocate(T* p, std::size_t n);
};

template <class T>
MyAllocator<T>::MyAllocator() {}

template <class T>
template <class U>
MyAllocator<T>::MyAllocator(const MyAllocator<U>& ) {}

template <class T>
T* MyAllocator<T>::allocate(std::size_t n)
{
	auto p = std::malloc(n * sizeof(T));
	if (!p)
		throw std::bad_alloc();
	return reinterpret_cast<T *>(p);
};

template <class T>
void MyAllocator<T>::deallocate(T* p, std::size_t )
{
	std::free(p);
};

template <class T, class U>
constexpr bool operator== (const MyAllocator<T>&, const MyAllocator<U>&) noexcept
{
  return false;
}

template <class T, class U>
constexpr bool operator!= (const MyAllocator<T>&, const MyAllocator<U>&) noexcept
{
  return false;
}

} // my_allocator