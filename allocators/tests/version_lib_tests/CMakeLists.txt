file(GLOB SRCS *.cpp)
ADD_EXECUTABLE(version_lib_tests ${SRCS})
TARGET_LINK_LIBRARIES(
    version_lib_tests
    version_lib
    libgtest
    libgmock
)
add_test(NAME version_lib_tests
         COMMAND version_lib_tests)
