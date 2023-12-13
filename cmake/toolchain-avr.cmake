set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

# toolchain files unfortunately cannot access normal CMake cache variables.
# Therefore we have to pass in the MCU as an environment variable.
set(AVR_MCU "$ENV{CMAKE_AVR_MCU}")
if(NOT AVR_MCU)
    message(
        FATAL_ERROR "CMAKE_AVR_MCU environment variable must be set to "
        "define the target MCU"
    )
endif()

add_compile_options(--target=avr "-mmcu=${AVR_MCU}" -fno-rtti -fno-exceptions)
add_link_options(--target=avr "-mmcu=${AVR_MCU}" -fno-rtti -fno-exceptions)

set(clang_bin "$ENV{HOME}/src/llvm-project/build/bin")
set(CMAKE_C_COMPILER "${clang_bin}/clang")
set(CMAKE_CXX_COMPILER "${clang_bin}/clang++")
set(CMAKE_ASM_COMPILER "${clang_bin}/clang")
