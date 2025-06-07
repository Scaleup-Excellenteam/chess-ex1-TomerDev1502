#pragma once

#include <list>
#include "InvalidQueueException.h"
#include "QueueOverflowException.h"

// Comparator: higher int = higher priority
struct MyComparator {
    bool operator()(int a, int b) const {
        return a > b;
    }
};

class PriorityQueue {
public:
    PriorityQueue() = default;

    // O(n) insert into sorted position
    void push(int value);

    // O(1) remove & return highest-priority element
    int poll();

    bool empty() const noexcept { return data_.empty(); }

private:
    static constexpr size_t MAX_SIZE = 5;
    std::list<int> data_;
    MyComparator  comp_;
};
