// Copyright (c) 2023, Adam Simpkins
#pragma once

#include "asel/range.h"

namespace asel {

#if ASEL_HAVE_STDLIB
using buf_view = std::basic_string_view<uint8_t>;
#else
using buf_view = range<uint8_t>;
#endif

} // namespace asel
