add_library(my_container_lib STATIC
    my_container.h)

set_target_properties(my_container_lib PROPERTIES LINKER_LANGUAGE CXX)    

target_link_libraries (my_container_lib my_allocator_lib)

target_include_directories(my_container_lib 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE "${CMAKE_BINARY_DIR}"
)
