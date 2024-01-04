// Copyright (c) 2023, Adam Simpkins
#pragma once

namespace asel {

class TestFilter;

/**
 * Returns the number of failed tests.
 */
unsigned int run_tests(const TestFilter *filter = nullptr);

int test_main(int argc, const char *const *argv);
int test_main();

} // namespace asel
