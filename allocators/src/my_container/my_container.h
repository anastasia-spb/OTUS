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
    MyContainer& operator=(const MyContainer<T, N, Allocator>& other);
    MyContainer (MyContainer&& other);
    MyContainer& operator=(MyContainer&& other);

    void push_back(const T& element);
    T& at(size_type) const;

    size_type size() const;
    bool empty() const;

  private:
    Allocator container_allocator_{};
    // array of pointers to elements
    T* elements_pointers_[N];
    // current elements count
    size_type counter_{0U};
};

template <class T, std::size_t N, class Allocator>
MyContainer<T, N, Allocator>::MyContainer(const MyContainer<T, N, Allocator>& other)
{
  counter_ = other.counter_;
  for(std::size_t i{0U}; i < counter_; ++i)
  {
    elements_pointers_[i] = container_allocator_.allocate(1U);
    std::memcpy(elements_pointers_[i], other.elements_pointers_[i], sizeof(T));
  }
}

template <class T, std::size_t N, class Allocator>
MyContainer<T, N, Allocator>::MyContainer(MyContainer<T, N, Allocator>&& other)
{
  counter_ = other.counter_;
  std::memcpy(elements_pointers_, other.elements_pointers_, sizeof(other.elements_pointers_));
  container_allocator_ = std::move(other.container_allocator_);
  other.counter_ = 0U;
}

template <class T, std::size_t N, class Allocator>
MyContainer<T, N, Allocator>& MyContainer<T, N, Allocator>::operator=(const MyContainer<T, N, Allocator>& other)
{
  counter_ = other.counter_;

  for(std::size_t i{0U}; i < other.counter_; ++i)
  {
    elements_pointers_[i] = container_allocator_.allocate(1U);
    std::memcpy(elements_pointers_[i], other.elements_pointers_[i], sizeof(T));
  }
}

template <class T, std::size_t N, class Allocator>
MyContainer<T, N, Allocator>& MyContainer<T, N, Allocator>::operator=(MyContainer<T, N, Allocator>&& other)
{
  if (this != &other)
  {
    counter_ = other.counter_;
    std::memcpy(elements_pointers_, other.elements_pointers_, sizeof(other.elements_pointers_));
    container_allocator_ = std::move(other.container_allocator_);

    other.counter_ = 0U;
  }

  return *this;
}

template <class T, std::size_t N, class Allocator>
constexpr bool operator== (const MyContainer<T, N, Allocator>& lhs, const MyContainer<T, N, Allocator>& rhs) noexcept
{
  bool equal{false};

  if(lhs.size() == rhs.size())
  {
    equal = true;

    for(std::size_t i{0U}; i < lhs.size(); ++i)
    {
      if(lhs.at(i) != rhs.at(i))
      {
        equal = false;
        break;
      }
    }
  }

  return equal;
}

template <class T, std::size_t N, class Allocator>
constexpr bool operator!= (const MyContainer<T, N, Allocator>& lhs, const MyContainer<T, N, Allocator>& rhs) noexcept
{
  return (!(lhs == rhs));
}

template <class T, std::size_t N, class Allocator>
void MyContainer<T, N, Allocator>::push_back(const T& element)
{
  elements_pointers_[counter_] = container_allocator_.allocate(1U);
  std::memcpy(elements_pointers_[counter_], &element, sizeof(T));
  ++counter_;
}

template <class T, std::size_t N, class Allocator>
T& MyContainer<T, N, Allocator>::at(MyContainer<T, N, Allocator>::size_type index) const
{
  return *elements_pointers_[index];
}

template <class T, std::size_t N, class Allocator>
typename MyContainer<T, N, Allocator>::size_type MyContainer<T, N, Allocator>::size() const
{
  return counter_;
}

template <class T, std::size_t N, class Allocator>
bool MyContainer<T, N, Allocator>::empty() const
{
  return (counter_ == 0U);
}

} // my_container