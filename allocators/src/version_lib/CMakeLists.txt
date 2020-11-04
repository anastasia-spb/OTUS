configure_file(version.h.in version.h)

add_library(version_lib STATIC
    get_version.h
    get_version.cpp
)

target_include_directories(version_lib 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE "${CMAKE_BINARY_DIR}"
)