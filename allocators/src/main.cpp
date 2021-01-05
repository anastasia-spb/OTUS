#include "my_allocator/my_allocator.h"
#include "my_container/my_container.h"
#include <iostream>
#include <map>

namespace
{
unsigned int factorial(unsigned int n)
{
    unsigned int result{1U};
    for(auto i{1U}; i <= n; ++i)
    {
        result *= i;
    }
        
    return result;
}
}

int main (int, char **)
{
    const int num_elements{10};

    // Create std::map<int, int> and 
    // fill it with 10 elements
    std::map<int, int> stl_map{};
    for(int i{0}; i < num_elements; ++i)
    {
        stl_map.emplace(std::pair<int, int>(i, factorial(i)));
    }

    // Do the same using own allocator
    using element_type = std::pair<const int, int>;
    using my_allocator_type = my_allocator::MyAllocator<element_type, 10U>;

    std::map<const int, int, std::less<int>, my_allocator_type> my_map{};
    for(int i{0}; i < num_elements; ++i)
    {
        my_map.emplace(element_type(i, factorial(i)));
    }

    // Print elements
    std::cout << "Values in map: \n";      
    for(const auto& el : my_map)
    {
        std::cout << el.first << " " << el.second << std::endl;
    }

    // Create own container for type int and fill with values in range (0, 9)
    my_container::MyContainer<int, 10U> my_container{};
    for(int i{0U}; i < num_elements; ++i)
    {
        my_container.push_back(i);
    }

    std::cout << "Values in container: \n";
    for(const auto& el : my_container)
    {
        std::cout << el << " ";
    }
    std::cout << std::endl;

    my_container::MyContainer<int, 10U, std::allocator<int>> my_container_with_stl_allocator{};
    for(int i{0}; i < num_elements; ++i)
    {
        my_container_with_stl_allocator.push_back(i);
    }

    std::cout << "Values in container with stl allocator: \n";
    for(const auto& el : my_container_with_stl_allocator)
    {
        std::cout << el << " ";
    }
    std::cout << std::endl;

    return 0;
}
