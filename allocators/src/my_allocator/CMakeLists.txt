add_library(my_allocator_lib STATIC
    my_allocator.h
    my_allocator.cpp
)

target_include_directories(my_allocator_lib 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE "${CMAKE_BINARY_DIR}"
)