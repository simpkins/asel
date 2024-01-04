// Copyright (c) 2023, Adam Simpkins
#pragma once

namespace asel {

class TestCase;

class TestFilter {
public:
  constexpr TestFilter() = default;
  virtual ~TestFilter() = default;

  virtual bool is_enabled(const TestCase *test_case) const = 0;
};

} // namespace asel
