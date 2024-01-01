// Copyright (c) 2023, Adam Simpkins
#pragma once

#include "asel/array.h"
#include "asel/buf_view.h"
#include "asel/inttypes.h"
#include "asel/optional.h"
#include "asel/range.h"
#include "asel/type_traits.h"
#include "asel/utility.h"

#if ASEL_HAVE_STDLIB
#include <array>
#include <system_error>
#endif // ASEL_HAVE_STDLIB

namespace asel {

// TODO: implement low-level printing for when we do not have stdlib or printf
// My avrpp repository contains code for doing this on AVR, and I should just
// move it here.

void log_puts(const char *str);
void log_putc(char c);
void log_put_range(const char *str, unsigned int length);

inline void log_field() {}

namespace detail {
void custom_log();
}

template <typename T>
void log_field(const T &value) {
  using namespace asel::detail;
  custom_log(value);
}

inline void log_field(const char *str) {
  asel::log_puts(str);
}
void log_field(unsigned long n);
void log_field(long n);
void log_field(bool value);

inline void log_field(unsigned int n) {
  log_field(static_cast<unsigned long>(n));
}
inline void log_field(int n) {
  log_field(static_cast<long>(n));
}

inline void log_field(unsigned char n) {
  log_field(static_cast<unsigned long>(n));
}
inline void log_field(signed char n) {
  log_field(static_cast<long>(n));
}
inline void log_field(unsigned short n) {
  log_field(static_cast<unsigned long>(n));
}
inline void log_field(short n) {
  log_field(static_cast<long>(n));
}

#if ASEL_HAVE_STDLIB
void log_field(std::error_code ec);
#endif // ASEL_HAVE_STDLIB

template <typename T>
void log_field(asel::string_view value) {
  log_put_range(value.data(), value.size());
}

void log_hex(const void *data, unsigned long length);

inline void log_field(asel::buf_view value) {
  log_hex(value.data(), value.size());
}
template <size_t N>
inline void log_field(const array<uint8_t, N> value) {
  log_hex(value.data(), value.size());
}
template <typename T, size_t N>
inline void log_field(const array<T, N> value) {
  log_field("{");
  log_field(value[0]);
  for (size_t n = 0; n < N; ++n) {
    log_field(", ");
    log_field(value[n]);
  }
  log_field("}");
}

template <typename T>
void log_field(const asel::optional<T> &value) {
  if (!value) {
    log_puts("nullopt");
  } else {
    log_field(*value);
  }
}

template <typename T1, typename T2, typename... Args>
void log_field(const T1 &arg1, const T2 &arg2, Args... rest) {
  log_field(arg1);
  log_field(arg2, asel::forward<Args>(rest)...);
}

template <typename... Args>
void log_message(Args... args) {
  log_field(asel::forward<Args>(args)...);
  log_putc('\n');
}

} // namespace asel
