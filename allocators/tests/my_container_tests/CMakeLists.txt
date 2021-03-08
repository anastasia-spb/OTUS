file(GLOB SRCS *.cpp)
ADD_EXECUTABLE(my_container_tests ${SRCS})
TARGET_LINK_LIBRARIES(
    my_container_tests
    my_container_lib
    libgtest
    libgmock
)
add_test(NAME my_container_tests
         COMMAND my_container_tests)
