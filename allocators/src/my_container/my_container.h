#pragma once

#include <iostream>
#include <memory>
#include <cassert>
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

    class Iterator
    {
      public:
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(size_type current_idx, T** elements_pointers)
        :
        current_idx_(current_idx),
        elements_pointers_(elements_pointers)
        {};

        Iterator& operator++()
        { 
          current_idx_++;
          return *this;
        };

        Iterator& operator--()
        { 
          current_idx_--;
          return *this;
        };

        Iterator& operator++(int)
        { 
          current_idx_++;
          return *this;
        };

        Iterator& operator--(int)
        {
          current_idx_--;
          return *this;
        };

        T& operator*()
        { 
          return **(elements_pointers_ + current_idx_);
        };

        T* operator->()
        { 
          return *(elements_pointers_ + current_idx_);
        };

        bool operator==(const Iterator& rhs)
        { 
          bool equal{false};

          if(current_idx_ == rhs.current_idx_)
          {
            equal = true;
            for(std::size_t i{0U}; i <= std::min((N - 1U), current_idx_); ++i)
            { 
              const auto p{elements_pointers_ + i};
              const auto rhs_p{rhs.elements_pointers_ + i};
              if(*p != *rhs_p)
              {
                equal = false;
                break;
              }
            }
          }
          return equal;
        };

        bool operator!=(const Iterator& rhs)
        { 
          return (!(*this == rhs));
        };

        friend bool operator==(const Iterator& iter1, const Iterator& iter2)
        {
          bool equal{false};

          if(iter1.current_idx_ == iter2.current_idx_)
          {
            equal = true;

            for(std::size_t i{0U}; i <= std::min((N - 1U), iter1.current_idx_); ++i)
            { 
              const auto iter1_p{iter1.elements_pointers_ + i};
              const auto iter2_p{iter2.elements_pointers_ + i};   
              if(*iter1_p != *iter2_p)
              {
                equal = false;
                break;
              }
            }
          }
          return equal;
        };

        friend bool operator!=(const Iterator& iter1, const Iterator& iter2)
        {
          return !(iter1 == iter2);
        };

        private:
          size_type current_idx_;
          // Points to the first pointer in 
          // array where pointers to allocated blocks
          // are stored
          T** elements_pointers_;
      };
    
    MyContainer() = default;
    ~MyContainer()
    {
      for(auto i{0U}; i < counter_; ++i)
      {
        container_allocator_.deallocate(elements_pointers_[i], 1U);
      }
    }
    
    MyContainer (const MyContainer<T, N, Allocator>& other);
    MyContainer& operator=(const MyContainer<T, N, Allocator>& other);
    MyContainer (MyContainer&& other);
    MyContainer& operator=(MyContainer&& other);

    void push_back(const T& element);
    const T& at(size_type) const;

    size_type size() const;
    bool empty() const;

    const T& operator[](size_type index) const;
    T& operator[](size_type index);

    Iterator begin()
    {
        return Iterator(0U, elements_pointers_);
    }

    Iterator end()
    {
        return Iterator(counter_, elements_pointers_);
    }

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
const T& MyContainer<T, N, Allocator>::at(MyContainer<T, N, Allocator>::size_type index) const
{
  assert(index < counter_);
  return *(elements_pointers_[index]);
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

template <class T, std::size_t N, class Allocator>
T& MyContainer<T, N, Allocator>::operator[](MyContainer<T, N, Allocator>::size_type index)
{
    assert(index < counter_);
    return *(elements_pointers_[index]);
}

template <class T, std::size_t N, class Allocator>
const T& MyContainer<T, N, Allocator>::operator[](MyContainer<T, N, Allocator>::size_type index) const
{
    assert(index < counter_);
    return *(elements_pointers_[index]);
}

} // my_container