project(3D)

file(GLOB SRC_FILES "*.cpp")

add_subdirectory(geometry)

set(SOURCE_LIB ${SOURCE_LIB} ${SRC_FILES})
add_library(3D STATIC ${SOURCE_LIB})

target_link_libraries(3D ${CONAN_LIBS})
target_include_directories(3D PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
