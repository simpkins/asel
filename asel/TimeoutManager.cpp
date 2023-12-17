// Copyright (c) 2023, Adam Simpkins
#include "asel/TimeoutManager.h"

namespace asel {

chrono::steady_clock::time_point TimeoutManager::get_next_timeout() const {
  if (list_.next == &list_) {
    // No entries in the list.
    return time_point() + duration(std::numeric_limits<duration::rep>::max());
  }
  return timeout_for_node(list_.next)->timeout_;
}

void TimeoutManager::add_timeout(Timeout *t,
                                 chrono::steady_clock::time_point timeout) {
  TimeoutNode *prev = &list_;
  TimeoutNode *node = list_.next;
  while (true) {
    // Stop when we reach a node with a timeout greater than this one,
    // or the end of the list.
    if (node == &list_ || timeout_for_node(node)->timeout_ > timeout) {
      node->prev = &t->node_;
      t->node_.next = node;
      prev->next = &t->node_;
      t->node_.prev = prev;
      t->timeout_ = timeout;
      return;
    }
    prev = node;
    node = node->next;
  }
}

} // namespace asel
