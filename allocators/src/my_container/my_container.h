#pragma once

#include <iostream>
#include <memory>
#include "my_allocator.h"

namespace my_container
{

template <class T, std::size_t N, class Allocator = my_allocator::MyAllocator<T, N>>
class MyContainer
{
  public:
    MyContainer();
    ~MyContainer() = default;
    MyContainer (const MyContainer<T, N, Allocator>& other);
    MyContainer operator=(const MyContainer<T, N, Allocator>& other){ /* @ todo Implement */ };
    MyContainer (MyContainer&& other);
    MyContainer operator=(MyContainer&& other){ /* @ todo Implement */ };


  private:
    Allocator container_allocator_{};
    // array of pointers to elements
    std::uint32_t elements_[N];
    // current elements count
    std::size_t counter_{0U};
};

template <class T, std::size_t N, class Allocator>
MyContainer<T, N, Allocator>::MyContainer()
:
counter_(0U)
{}

template <class T, std::size_t N, class Allocator>
MyContainer<T, N, Allocator>::MyContainer(const MyContainer<T, N, Allocator>& other)
{
  //@ todo Implement
}

template <class T, std::size_t N, class Allocator>
MyContainer<T, N, Allocator>::MyContainer(MyContainer<T, N, Allocator>&& other)
{
  //@ todo Implement
}

template <class T, std::size_t N, class Allocator>
constexpr bool operator== (const MyContainer<T, N, Allocator>&, const MyContainer<T, N, Allocator>&) noexcept
{
  //@ todo Implement
  return false;
}

template <class T, std::size_t N, class Allocator>
constexpr bool operator!= (const MyContainer<T, N, Allocator>&, const MyContainer<T, N, Allocator>&) noexcept
{
  //@ todo Implement
  return false;
}

} // my_container