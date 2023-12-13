cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 20)

set(ASEL_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(
    srcs
    asel/log.cpp
    asel/test/run_tests.cpp
    asel/test/TestCase.cpp
    asel/test/TestRegistry.cpp
)

if(ESP_PLATFORM)
    include("${CMAKE_CURRENT_LIST_DIR}/cmake/esp.cmake")
else()
    project(asel HOMEPAGE_URL https://github.com/simpkins/asel)

    # Check to see if we are the top-level project, or if we are
    # being used via add_subdirectory() in some other project.
    if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(ASEL_IS_PRIMARY_PROJECT ON)
        message(STATUS "CMake version: ${CMAKE_VERSION}")
    endif()

    # If we are the top-level project, globally apply some of our own compiler
    # flags.  When part of another project we let the top-level project choose
    # these flags.
    if(ASEL_IS_PRIMARY_PROJECT)
        include("${CMAKE_CURRENT_LIST_DIR}/cmake/compiler-settings.cmake")
    endif()

    add_library(asel STATIC ${srcs})
    target_include_directories(
        asel PUBLIC
        "${ASEL_ROOT_DIR}"
    )
    if(NOT CMAKE_SYSTEM_PROCESSOR STREQUAL avr)
        # When building for AVR we don't have the stdlib,
        # but use it on other platforms.
        target_compile_definitions(
            asel PUBLIC
            ASEL_HAVE_STDLIB=1
        )
    endif()

    if (ASEL_IS_PRIMARY_PROJECT OR ASEL_ENABLE_TESTS)
        add_subdirectory("test")
        add_executable(asel_tests test/runner/host/main.cpp)
        target_link_libraries(asel_tests PUBLIC asel_test_cases)

        if(NOT CMAKE_CROSSCOMPILING)
            include(CTest)
            add_test(NAME asel COMMAND asel_tests)
        endif()
    endif()
endif()
