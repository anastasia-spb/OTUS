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

    template<class M>
    struct rebind
    {
        using other = MyAllocator<M, N>;
    };

    MyAllocator();
    ~MyAllocator();

    MyAllocator (const MyAllocator<T, N>& other);

    template <class U, std::size_t N1>
    MyAllocator (const MyAllocator<U, N1>& other) = delete;

    MyAllocator operator=(const MyAllocator<T, N>& other);

    template <class U, std::size_t N1>
    MyAllocator operator=(const MyAllocator<U, N1>& other) = delete;

    // @todo Impelement move constructor and move assignment operator

    T* allocate(std::size_t n);
    void deallocate(T* p, std::size_t n);

  private:
    std::size_t counter_{0U};
    void* p_{nullptr};
};

template <class T, std::size_t N>
MyAllocator<T, N>::MyAllocator(const MyAllocator<T, N>& other)
:
counter_(other.counter_),
p_{nullptr}
{
 
  p_ = std::malloc(N * sizeof(T));

  if(counter_ > 0U)
  {
    std::memcpy(p_, other.p_, (counter_ * sizeof(T)));
  }
}

template <class T, std::size_t N>
MyAllocator<T, N> MyAllocator<T, N>::operator=(const MyAllocator<T, N>& other)
{
  if(&other == this)
  {
    return *this;
  }

  if(counter_ != other.counter_)
  {
    if(!p_)
    {
      free(p_);
    }
    
    counter_ = other.counter_;
    p_ = std::malloc(N * sizeof(T));
  }

  if(!p_ && (counter_ > 0U))
  {
    std::memcpy(p_, other.p_, (counter_ * sizeof(T)));
  }

  return *this;
}

template <class T, std::size_t N>
MyAllocator<T, N>::~MyAllocator()
{
  if(!p_)
  {
    free(p_);
  }
}

template <class T, std::size_t N>
MyAllocator<T, N>::MyAllocator()
:
counter_{0U}
{
  p_ = std::malloc(N * sizeof(T));
}

template <class T, std::size_t N>
T* MyAllocator<T, N>::allocate(std::size_t)
{
	if (!p_ || (counter_ >= N))
  {
		throw std::bad_alloc();
  }

  T* current_pointer{reinterpret_cast<T *>(p_) + counter_ * sizeof(T)};
  ++counter_; 

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