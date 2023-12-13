set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

add_compile_options(--target=avr -mmcu=at90usb1286 -fno-rtti -fno-exceptions)
add_link_options(--target=avr -mmcu=at90usb1286 -fno-rtti -fno-exceptions)

set(clang_bin "$ENV{HOME}/src/llvm-project/build/bin")
set(CMAKE_C_COMPILER "${clang_bin}/clang")
set(CMAKE_CXX_COMPILER "${clang_bin}/clang++")
set(CMAKE_ASM_COMPILER "${clang_bin}/clang")
