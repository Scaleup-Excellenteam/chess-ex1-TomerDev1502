#pragma once

#include <list>
#include "InvalidQueueException.h"
#include "QueueOverflowException.h"

/// Default comparator: larger values have higher priority
template<typename T>
struct DefaultComparator {
    bool operator()(T const& a, T const& b) const noexcept {
        return a > b;
    }
};

/// A fixed-size priority queue for elements of type T
/// Uses Comparator to order elements. Throws on overflow or invalid access.
template<
    typename T,
    class Comparator = DefaultComparator<T>
>
class PriorityQueue {
public:
    PriorityQueue() = default;

    /// Insert value in sorted position (O(n)).
    /// Throws QueueOverflowException if size >= MAX_SIZE.
    void push(T const& value) {
        if (data_.size() >= MAX_SIZE)
            throw QueueOverflowException();

        auto it = data_.begin();
        while (it != data_.end() && !comp_(value, *it)) {
            ++it;
        }
        data_.insert(it, value);
    }

    /// Remove and return the highest-priority element (O(1)).
    /// Throws InvalidQueueException if empty.
    T poll() {
        if (data_.empty())
            throw InvalidQueueException("poll on empty PriorityQueue");

        T top = data_.front();
        data_.pop_front();
        return top;
    }

    /// Check if queue is empty
    bool empty() const noexcept {
        return data_.empty();
    }

private:
    static constexpr size_t MAX_SIZE = 5;
    std::list<T> data_;
    Comparator comp_;
};