cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)

set(ASEL_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(
    srcs
)

if(ESP_PLATFORM)
    include("${CMAKE_CURRENT_LIST_DIR}/cmake/esp.cmake")
else()
    project(asel HOMEPAGE_URL https://github.com/simpkins/asel)

    include("${CMAKE_CURRENT_LIST_DIR}/cmake/linux.cmake")
    add_subdirectory("test")
endif()
