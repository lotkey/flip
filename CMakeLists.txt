cmake_minimum_required(VERSION 3.16)
project(flip
    VERSION 0.0.1
    HOMEPAGE_URL https://www.github.com/lotkey/flip
)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${SRC})

add_executable(flip
    ${SRC}/main.cpp
    ${SRC}/clipboard.cpp
)

install(TARGETS flip DESTINATION bin)
message("Add ${CMAKE_INSTALL_PREFIX}/bin to your PATH variable.")
