set(CMAKE_CXX_STANDARD 20)

include(CTest)

if(NOT CMAKE_CROSSCOMPILING)
    # Prefer compiling clang if we can find it.
    # Enable ASAN if we found clang.
    find_program(CXX_COMPILER NAMES "clang++" "clang++-15" "g++")
    find_program(C_COMPILER NAMES "clang" "clang-15" "gcc")
    if(CXX_COMPILER)
        set(CMAKE_CXX_COMPILER "${CXX_COMPILER}")
        string(REGEX MATCH ".*/clang.*" IS_CLANG "${CXX_COMPILER}")
        if(IS_CLANG)
          string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address")
        endif()
    endif()
    if(C_COMPILER)
        set(CMAKE_C_COMPILER "${C_COMPILER}")
        string(REGEX MATCH ".*/clang.*" IS_CLANG "${C_COMPILER}")
        if(IS_CLANG)
          string(APPEND CMAKE_C_FLAGS_DEBUG " -fsanitize=address")
        endif()
    endif()
endif()

string(APPEND CMAKE_CXX_FLAGS_DEBUG " -Werror")
string(APPEND CMAKE_C_FLAGS_DEBUG " -Werror")

add_library(asel STATIC ${srcs})
target_include_directories(
    asel PUBLIC
    "${ASEL_ROOT_DIR}"
)

if(NOT CMAKE_SYSTEM_PROCESSOR STREQUAL avr)
    target_compile_definitions(
        asel PUBLIC
        ASEL_HAVE_STDLIB=1
    )
endif()

add_executable(test_runner test/runner/host/main.cpp)
target_link_libraries(test_runner PUBLIC test_cases)

add_test(NAME asel COMMAND test_runner)
