// Copyright (c) 2023, Adam Simpkins
#pragma once

#if ASEL_HAVE_STDLIB

#include <optional>

namespace asel {
template <typename T> using optional = std::optional<T>;
}

#else // !ASEL_HAVE_STDLIB

namespace asel {

struct nullopt_t {
  enum class Construct { Tag };
  explicit constexpr nullopt_t(Construct) = default;
};

inline constexpr nullopt_t nullopt{nullopt_t::Construct::Tag};

template<typename T>
class optional {
public:

private:
  struct Empty {};

  union {
      Empty empty;
      T data;
  } value_;
  bool has_value_ = false;
};

} // namespace asel

#endif // !ASEL_HAVE_STDLIB
