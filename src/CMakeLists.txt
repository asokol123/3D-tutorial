cmake_minimum_required(VERSION 3.5)
project(3D CXX)

SET(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_CLANG_TIDY clang-tidy)

# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -fno-sanitize-recover=all")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(3D-renderer)
add_subdirectory(tests)

target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
  target_compile_options(3D PRIVATE /W4 /WX)
  target_compile_options(test PRIVATE /W4 /WX)
else()
  target_compile_options(3D PRIVATE -Wall -Wextra -Wpedantic -Werror)
  target_compile_options(test PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
