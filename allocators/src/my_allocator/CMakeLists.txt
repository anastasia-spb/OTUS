add_library(my_allocator_lib STATIC
    my_allocator.h)

set_target_properties(my_allocator_lib PROPERTIES LINKER_LANGUAGE CXX)    

target_include_directories(my_allocator_lib 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE "${CMAKE_BINARY_DIR}"
)