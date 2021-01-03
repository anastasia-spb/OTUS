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
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    
    MyContainer() = default;
    ~MyContainer() = default;
    MyContainer (const MyContainer<T, N, Allocator>& other);
    MyContainer operator=(const MyContainer<T, N, Allocator>& other){ /* @ todo Implement */ };
    MyContainer (MyContainer&& other);
    MyContainer operator=(MyContainer&& other){ /* @ todo Implement */ };

    void push_back(const T& element);
    T& operator[](size_type);

  private:
    Allocator container_allocator_{};
    // array of pointers to elements
    T* elements_pointers_[N];
    // current elements count
    std::size_t counter_{0U};
};

template <class T, std::size_t N, class Allocator>
MyContainer<T, N, Allocator>::MyContainer(const MyContainer<T, N, Allocator>& other)
{
  counter_ = other.counter_;
  for(std::size_t i{0U}; i < other.counter_; ++i)
  {
    elements_pointers_[i] = container_allocator_.allocate(1U);
    std::memcpy(elements_pointers_[i], other.elements_pointers_[i], sizeof(T));
  }
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

template <class T, std::size_t N, class Allocator>
void MyContainer<T, N, Allocator>::push_back(const T& element)
{
  elements_pointers_[counter_] = container_allocator_.allocate(1U);
  std::memcpy(elements_pointers_[counter_], &element, sizeof(element));
  ++counter_;
}

template <class T, std::size_t N, class Allocator>
T& MyContainer<T, N, Allocator>::operator[](MyContainer<T, N, Allocator>::size_type index)
{
  return *elements_pointers_[index];
}

} // my_container