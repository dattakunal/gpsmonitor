cmake_minimum_required(VERSION 3.14)

project(gpsread)
include(CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support.\n
                    Please use a different C++ compiler.")
endif()

# Global compile options:
add_compile_options(
    -ggdb
    -O0
)

include_directories(${CMAKE_SOURCE_DIR}/include/)

# Application:
add_executable(gpsread
    "${CMAKE_CURRENT_SOURCE_DIR}/source/gps_read.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/ipaddress.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp"
)
target_link_libraries(gpsread
    -lm
    -lgps
)
