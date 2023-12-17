// Copyright (c) 2023, Adam Simpkins
#include "asel/TimeoutManager.h"

#include "asel/test/TestCase.h"
#include "asel/test/checks.h"

using namespace asel::chrono_literals;

namespace asel {

namespace {
class TestTimeout : public Timeout {
public:
  explicit TestTimeout(int value) : value_(value) {}

  void on_timeout() override {
    log_message("TestTimeout ", value_, " fired");
  }

private:
  int const value_ = 0;
};
} // namespace

ASEL_TEST(TimeoutManager, test2) {
  TimeoutManager mgr;
  TestTimeout t1(1);
  TestTimeout t2(1);

  const auto now = chrono::steady_clock::now();

  mgr.add_timeout(&t1, now + 10ms);
  mgr.add_timeout(&t2, now + 20ms);
  mgr.add_timeout(&t2, now + 7ms);

  const auto next = mgr.get_next_timeout();
  const auto n = chrono::duration_cast<chrono::milliseconds>(next - now);
  ASEL_EXPECT_EQ(n.count(), (7ms).count());
}

} // namespace asel
