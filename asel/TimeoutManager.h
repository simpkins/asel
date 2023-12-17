// Copyright (c) 2023, Adam Simpkins
#pragma once

#include "asel/chrono.h"
#include "asel/type_traits.h"

namespace asel {

struct TimeoutNode {
  constexpr TimeoutNode() noexcept = default;
  constexpr TimeoutNode(TimeoutNode *p, TimeoutNode *n) noexcept
      : prev(p), next(n) {}

  TimeoutNode *prev = nullptr;
  TimeoutNode *next = nullptr;
};

class Timeout {
public:
  virtual void on_timeout() = 0;

  chrono::steady_clock::time_point get_timeout() const {
    return timeout_;
  }

private:
  friend class TimeoutManager;

  // The timeout will not be fired until after the timeout has expired.
  // (We don't provide a guarantee on how quickly it will run after the timeout
  // has expired, just that it won't run before.)
  chrono::steady_clock::time_point timeout_;

  // We currently store timeouts as a pretty dumb linked list, sorted by
  // timeout order.  In the future we could consider storing the data in a
  // heap, however for must embedded projects the number of timeouts is
  // probably quite small--small enough that the linear scan for insertion
  // might not be a big deal.
  TimeoutNode node_;
};

/**
 * TimeoutManager is not thread-safe.  The intention is to use separate
 * TimeoutManager objects for each CPU.  If work from one task needs to
 * schedule a timeout on a different task's TimeoutManager, it should use RPC
 * mechanisms to do so.
 */
class TimeoutManager {
public:
  using clock = chrono::steady_clock;
  using time_point = clock::time_point;
  using duration = clock::duration;

  constexpr TimeoutManager() = default;

  time_point get_next_timeout() const;

  void add_timeout(Timeout *t, time_point timeout);
  void add_timeout(Timeout *t, duration timeout) {
    add_timeout(t, clock::now() + timeout);
  }

private:
  TimeoutManager(TimeoutManager const &) = delete;
  TimeoutManager &operator=(TimeoutManager const &) = delete;

  // Given a TimeoutNode object, return the Timeout that contains it.
  // Must not be called on the TimeoutManager's node representing the head of
  // the list.
  static Timeout *timeout_for_node(TimeoutNode *node) {
    const Timeout *t = nullptr;
    const auto offset = reinterpret_cast<const uint8_t *>(&t->node_) -
                        reinterpret_cast<const uint8_t *>(t);
    return reinterpret_cast<Timeout *>(reinterpret_cast<uint8_t *>(node) -
                                       offset);
  }

  TimeoutNode list_{&list_, &list_};
};

} // namespace asel
