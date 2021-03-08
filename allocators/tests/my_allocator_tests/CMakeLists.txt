file(GLOB SRCS *.cpp)
ADD_EXECUTABLE(my_allocator_tests ${SRCS})
TARGET_LINK_LIBRARIES(
    my_allocator_tests
    my_allocator_lib
    libgtest
    libgmock
)
add_test(NAME my_allocator_tests
         COMMAND my_allocator_tests)
