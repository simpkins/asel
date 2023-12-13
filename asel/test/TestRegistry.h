// Copyright (c) 2023, Adam Simpkins
#pragma once

namespace asel {

class TestCase;

class TestRegistry {
public:
  constexpr TestRegistry() noexcept = default;

  void register_test(TestCase* test);

  TestCase* head = nullptr;
  TestCase* tail = nullptr;
};

extern TestRegistry g_test_registry;

} // namespace asel
