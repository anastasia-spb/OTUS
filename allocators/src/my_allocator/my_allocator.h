#pragma once

#include <iostream>
#include <memory>
#include <cstring>

namespace my_allocator
{

template <class T, std::size_t N>
class MyAllocator
{
  public:
    static_assert((N != 0U), "Couldn't allocate memory for zero elements");

    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<class M>
    struct rebind
    {
        using other = MyAllocator<M, N>;
    };

    MyAllocator();
    ~MyAllocator();

    template <class U, std::size_t N1>
    MyAllocator (const MyAllocator<U, N1>& other) = delete;

    MyAllocator (MyAllocator<T, N>&& other);

    template <class U, std::size_t N1>
    MyAllocator (MyAllocator<U, N1>&& other) = delete;

    template <class U, std::size_t N1>
    MyAllocator& operator=(const MyAllocator<U, N1>& other) = delete;

    MyAllocator& operator=(MyAllocator<T, N>&& other);

    template <class U, std::size_t N1>
    MyAllocator& operator=(MyAllocator<U, N1>&& other) = delete;

    T* allocate(std::size_t n);
    void deallocate(T* p, std::size_t n);

  private:
    std::size_t counter_{0U};
    T* p_{nullptr};
    std::size_t block_size_{0U};
};

template <class T, std::size_t N>
MyAllocator<T, N>::~MyAllocator()
{
  counter_ = 0U;
  free(p_);
}

template <class T, std::size_t N>
MyAllocator<T, N>::MyAllocator()
{
  block_size_ = sizeof(T) + (alignof(T) - sizeof(T) % alignof(T));
  p_ = static_cast<T*>(std::malloc(N * block_size_));
}

template <class T, std::size_t N>
MyAllocator<T, N>& MyAllocator<T, N>::operator=(MyAllocator<T, N>&& other)
{
  if (this != &other)
  {
    free(p_);

    counter_ = other.counter_;
    p_ = other.p_;
    block_size_ = other.block_size_;

    other.p_ = nullptr;
    other.counter_ = 0U;
  }

  return *this;
}

template <class T, std::size_t N>
MyAllocator<T, N>::MyAllocator(MyAllocator<T, N>&& other)
{
  counter_ = other.counter_;
  p_ = other.p_;
  block_size_ = other.block_size_;

  other.p_ = nullptr;
  other.counter_ = 0U;
}

template <class T, std::size_t N>
T* MyAllocator<T, N>::allocate(std::size_t n)
{
	if (!p_ || ((counter_ + n) > N))
  {
		throw std::bad_alloc();
  }

  T* current_pointer{p_ + counter_};
  counter_ += n;

  //std::cout << "Allocate at: " << current_pointer << " " << "\n";

	return current_pointer;
};

template <class T, std::size_t N>
void MyAllocator<T, N>::deallocate(T*, std::size_t)
{};

template <class T, class U, std::size_t N, std::size_t N1>
constexpr bool operator== (const MyAllocator<T, N>&, const MyAllocator<U, N1>&) noexcept
{
  return false;
}

template <class T, class U, std::size_t N, std::size_t N1>
constexpr bool operator!= (const MyAllocator<T, N>&, const MyAllocator<U, N1>&) noexcept
{
  return false;
}

} // my_allocator