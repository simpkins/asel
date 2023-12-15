// Copyright (c) 2023, Adam Simpkins
#pragma once

#if ASEL_HAVE_STDLIB
#include <cinttypes>
#else
namespace asel {

// GCC and Clang both provide predefined macros that specify the desired
// integer width types.
//
// Just for documentation purposes, on AVR:
// - sizeof(int) = 2
// - sizeof(long) = 4
// - sizeof(long long) = 8
//
using uint8_t = __UINT8_TYPE__;
using int8_t = __INT8_TYPE__;
using uint16_t = __UINT16_TYPE__;
using int16_t = __INT16_TYPE__;
using uint32_t = __UINT32_TYPE__;
using int32_t = __INT32_TYPE__;

// Beware that on AVR size_t is only 16 bits
using size_t = __SIZE_TYPE__;

} // namespace asel
#endif
