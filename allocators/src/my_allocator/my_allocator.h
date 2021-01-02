#pragma once

#include <iostream>
#include <memory>

namespace my_allocator
{

template <class T>
class MyAllocator
{
  public:
    using value_type = T;
    MyAllocator(std::size_t n);
    ~MyAllocator();
    template <class U> MyAllocator (const MyAllocator<U>& other);
    T* allocate(std::size_t n);
    void deallocate(T* p, std::size_t n);
    std::size_t GetReservedSize() const;

  private:
    std::size_t n_{0U};
    std::size_t counter_{0U};
    void* p_{nullptr};
    T* current_pointer_{nullptr};
};


template <class T> 
std::size_t MyAllocator<T>::GetReservedSize() const
{
  return n_;
}

template <class T>
MyAllocator<T>::~MyAllocator()
{
  current_pointer_ = nullptr;
  if(!p_)
  {
    free(p_);
  }
}

template <class T>
MyAllocator<T>::MyAllocator(std::size_t n)
:
n_{n},
counter_{0U}
{
  if(n_ > 0U)
  {  
    p_ = std::malloc(n_ * sizeof(T));
  }
}

template <class T>
template <class U>
MyAllocator<T>::MyAllocator(const MyAllocator<U>& other)
:
n_(other.GetReservedSize()),
counter_{0U}
{
  if(n_ > 0U)
  {  
    p_ = std::malloc(n_ * sizeof(T));
  }
}

template <class T>
T* MyAllocator<T>::allocate(std::size_t)
{
	if (!p_ || (counter_ >= n_))
  {
		throw std::bad_alloc();
  }

  if(counter_ == 0U)
  {
    current_pointer_ = reinterpret_cast<T *>(p_);
  }
  else
  {
    current_pointer_ += sizeof(T);
  }

  ++counter_; 

	return current_pointer_;
};

template <class T>
void MyAllocator<T>::deallocate(T*, std::size_t)
{};

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