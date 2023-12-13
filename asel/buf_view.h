// Copyright (c) 2023, Adam Simpkins
#pragma once

#include "asel/range.h"

#include <string_view>

namespace asel {

using buf_view = std::basic_string_view<uint8_t>;
// using buf_view = range<const uint8_t*>;

} // namespace asel
