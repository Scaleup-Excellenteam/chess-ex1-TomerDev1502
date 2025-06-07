#include "PriorityQueue.h"

void PriorityQueue::push(int value) {
    if (data_.size() >= MAX_SIZE)
        throw QueueOverflowException();

    // find insert position
    auto it = data_.begin();
    while (it != data_.end() && !comp_(value, *it)) {
        ++it;
    }
    data_.insert(it, value);
}

int PriorityQueue::poll() {
    if (data_.empty())
        throw InvalidQueueException("poll on empty PriorityQueue");

    int top = data_.front();
    data_.pop_front();
    return top;
}
