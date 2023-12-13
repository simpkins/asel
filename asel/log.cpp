// Copyright (c) 2023, Adam Simpkins
#include "asel/log.h"

#if ASEL_HAVE_STDLIB
#include <cstdio>
#include <system_error>
#endif // ASEL_HAVE_STDLIB

namespace asel {

#if ASEL_HAVE_STDLIB

void log_puts(const char *str) { std::fputs(str, stderr); }
void log_putc(char c) { std::putc(c, stderr); }

void log_field(unsigned int n) { fprintf(stderr, "%u", n); }
void log_field(int n) { fprintf(stderr, "%d", n); }

void log_field(std::error_code ec) {
  log_puts("error_code(");
  log_field(ec.category().name());
  log_puts(", ");
  log_field(ec.value());
  log_puts(")");
}

#else // !ASEL_HAVE_STDLIB

void log_puts(const char *str) {
  const char *p = str;
  while (*p) {
    log_putc(*p);
    ++p;
  }
}

void log_putc(char c) {
  // TODO: allow a user-defined putc function
}

void log_field(unsigned int n) {
  // TODO
}

void log_field(int n) {
  if (n < 0) {
    log_putc('-');
    log_field(static_cast<unsigned int>(-n));
  } else {
    log_field(static_cast<unsigned int>(n));
  }
}

#endif // !ASEL_HAVE_STDLIB

} // namespace asel

#if !ASEL_HAVE_STDLIB
extern "C" void __cxa_pure_virtual() {
  asel::log_puts("pure virtual function called!\n");
  while (true) {
  }
}
#endif
