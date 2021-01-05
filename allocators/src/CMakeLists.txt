add_subdirectory(my_allocator)
add_subdirectory(my_container)
add_executable (my_allocator_cli main.cpp)
target_link_libraries (my_allocator_cli my_allocator_lib my_container_lib)

install(TARGETS my_allocator_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

include(CPack)
