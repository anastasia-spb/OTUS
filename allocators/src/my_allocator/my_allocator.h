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
    MyAllocator (const MyAllocator<U, N1>& other){};

    MyAllocator (MyAllocator<T, N>&& other);

    template <class U, std::size_t N1>
    MyAllocator (MyAllocator<U, N1>&& other){};

    template <class U, std::size_t N1>
    MyAllocator& operator=(const MyAllocator<U, N1>& other){};

    MyAllocator& operator=(MyAllocator<T, N>&& other){};

    template <class U, std::size_t N1>
    MyAllocator& operator=(MyAllocator<U, N1>&& other){};

    T* allocate(std::size_t n);
    void deallocate(T* p, std::size_t n);

  private:
    std::size_t counter_{0U};
    T* p_{nullptr};
};

template <class T, std::size_t N>
MyAllocator<T, N>::~MyAllocator()
{
  counter_ = 0U;
  free(p_);
  p_ = nullptr;
}

template <class T, std::size_t N>
MyAllocator<T, N>::MyAllocator()
{}

template <class T, std::size_t N>
MyAllocator<T, N>::MyAllocator(MyAllocator<T, N>&& other)
{
  counter_ = other.counter_;
  p_ = other.p_;

  other.p_ = nullptr;
  other.counter_ = 0U;
}

template <class T, std::size_t N>
T* MyAllocator<T, N>::allocate(std::size_t n)
{
  if(!p_)
  {
    p_ = static_cast<T*>(std::malloc(N * sizeof(T)));
  }

	if (!p_ || ((counter_ + n) > N))
  {
		throw std::bad_alloc();
  }

  T* current_pointer{p_ + counter_};
  counter_ += n;
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
  return true;
}
} // my_allocator