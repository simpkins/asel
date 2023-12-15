// Copyright (c) 2023, Adam Simpkins
#pragma once

#if ASEL_HAVE_STDLIB
#include <array>
namespace asel {
template <typename T, std::size_t N>
using array = std::array<T, N>;
}
#else // !ASEL_HAVE_STDLIB

#include "asel/inttypes.h"

namespace asel {

template <typename T, size_t N>
class array {
public:
  // TODO

private:
  T data_[N];
};

} // namespace asel
  //
#endif // !ASEL_HAVE_STDLIB
