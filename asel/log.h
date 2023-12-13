// Copyright (c) 2023, Adam Simpkins
#pragma once

#include <cstdio>
#include <system_error>

namespace asel {

// TODO: implement low-level printing for when we do not have stdlib or printf
// My avrpp repository contains code for doing this on AVR, and I should just
// move it here.

inline void log_puts(const char *str) { std::fputs(str, stderr); }
inline void log_putc(char c) { std::putc(c, stderr); }

void log_field() {}
inline void log_field(const char *str) { asel::log_puts(str); }
void log_field(unsigned int n) { fprintf(stderr, "%u", n); }
void log_field(int n) { fprintf(stderr, "%d", n); }
void log_field(std::error_code ec) {
  log_puts("error_code(");
  log_field(ec.category().name());
  log_puts(", ");
  log_field(ec.value());
  log_puts(")");
}

template <typename T1, typename T2, typename... Args>
void log_field(const T1 &arg1, const T2& arg2, Args... rest) {
  log_field(arg1);
  log_field(arg2, std::forward<Args>(rest)...);
}

template <typename... Args>
void log_message(Args... args) {
  log_field(std::forward<Args>(args)...);
  log_putc('\n');
}

} // namespace asel
