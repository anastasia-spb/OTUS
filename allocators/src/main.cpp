#include "version_lib/get_version.h"
#include "my_allocator/my_allocator.h"
#include <iostream>


int main (int, char **)
{
    std::cout << "Version: " << version() << std::endl;

    return 0;
}
