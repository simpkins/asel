// Copyright (c) 2023, Adam Simpkins
#include "asel/test/run_tests.h"

#include "asel/log.h"
#include "asel/test/TestCase.h"
#include "asel/test/TestFilter.h"
#include "asel/test/TestRegistry.h"

#if ASEL_HAVE_STDLIB
#include <string>
#include <vector>
#endif

namespace asel {

TestResult *g_test_result;

class TestMainFilter : public TestFilter {
public:
  bool is_enabled(const TestCase *test_case) const override {
#if ASEL_HAVE_STDLIB
    if (filters_.empty()) {
      return true;
    }
    for (const auto &filter : filters_) {
      if (is_glob_match(test_case->suite, test_case->name, filter.c_str())) {
        return true;
      }
    }
    return false;
#else
    if (!filter_) {
      return true;
    }

    return is_glob_match(test_case->suite, test_case->name, filter_);
#endif
  }

  [[nodiscard]] bool add_filter(const char *filter) {
#if ASEL_HAVE_STDLIB
    filters_.emplace_back(filter);
    return true;
#else
    if (filter_) {
      log_message("only a single test filter is supported when compiled "
                  "without std library support");
      return false;
    }
    filter_ = filter;
    return true;
#endif
  }

private:
  static bool
  is_glob_match(const char *suite, const char *name, const char *filter) {
    size_t filter_idx = 0;
    size_t suite_idx = 0;
    while (true) {
      char f = filter[filter_idx];
      char s = suite[suite_idx];
      if (f == '\0') {
        // Allow the filter to match either just the suite name, or the
        // entire "<suite>.<test>" name.
        return s == '\0';
      } else if (f == '?') {
        if (s == '\0') {
          if (name == nullptr) {
            return false;
          }
          // Allow '?' to match the implicit separator between the suite name
          // and test name.
          suite = name;
          suite_idx = 0;
          name = nullptr;
          ++filter_idx;
          continue;
        } else {
          // '?' can match any character
          ++suite_idx;
          ++filter_idx;
          continue;
        }
      } else if (f == '.') {
        // Allow '.' to match a literal '.', or the separator between the suite
        // name and test name.
        if (s == '.') {
          ++suite_idx;
          ++filter_idx;
          continue;
        } else if (s == '\0') {
          if (name == nullptr) {
            return false;
          }
          suite = name;
          suite_idx = 0;
          name = nullptr;
          ++filter_idx;
          continue;
        }
      } else if (f == '*') {
        // Recursively check if the test name matches after skipping this glob
        if (is_glob_match(suite + suite_idx, name, filter + filter_idx + 1)) {
          return true;
        }
        // Check if the test name matches after skipping this character in the
        // name.
        if (s == '\0') {
          if (name == nullptr) {
            // There is more to the glob pattern after this '*', otherwise
            // is_glob_match() would have already returned true.
            return false;
          }
          suite = name;
          suite_idx = 0;
          name = nullptr;
        } else {
          ++suite_idx;
        }
        continue;
      } else {
        // A literal character match
        if (s != f) {
          return false;
        }
        ++suite_idx;
        ++filter_idx;
        continue;
      }
    }
  }

#if ASEL_HAVE_STDLIB
  std::vector<std::string> filters_;
#else
  const char *filter_ = nullptr;
#endif
};

unsigned int run_tests(const TestFilter *filter) {
  auto *test = g_test_registry.head;
  unsigned int num_tests = 0;
  unsigned int failed_tests = 0;
  while (test) {
    if (filter && !filter->is_enabled(test)) {
      test = test->next;
      continue;
    }

    ++num_tests;
    log_message("Running ", test->suite, ".", test->name, "...");
    g_test_result = &test->result;
    g_test_result->reset();

    test->run();
    test = test->next;

    if (g_test_result->num_failures() > 0) {
      log_message("  Failed");
      ++failed_tests;
    } else {
      log_message("  Success");
    }
    g_test_result = nullptr;
  }

  if (failed_tests == 0) {
    log_message("Ran ", num_tests, " tests");
    log_message("100% successful");
  } else {
    log_message(failed_tests, " of ", num_tests, " tests failed");
  }
  return failed_tests;
}

int test_main(int argc, const char *const *argv) {
  TestMainFilter filter;

  bool parsing_args = true;
  for (int n = 1; n < argc; ++n) {
    const char *const arg = argv[n];
    if (parsing_args && arg[0] == '-') {
      if (arg[1] == '-') {
        // Long argument
        if (arg[2] == '\0') {
          parsing_args = false;
        } else {
          log_message("unknown argument: ", arg);
          return 2;
        }
      } else {
        // Short argument
        log_message("unknown argument: ", arg);
        return 2;
      }
    } else {
      // This is a test filter.
      if (!filter.add_filter(arg)) {
        // add_filter() will have logged an error message
        return 2;
      }
    }
  }

  const auto num_failed = run_tests(&filter);
  if (num_failed != 0) {
    return 1;
  }
  return 0;
}

int test_main() {
  return test_main(0, nullptr);
}

} // namespace asel
