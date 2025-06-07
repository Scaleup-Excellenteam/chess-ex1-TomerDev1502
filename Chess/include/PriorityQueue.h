#pragma once

#include <list>
#include <cstddef>

/// Default comparator: larger values have higher priority
template<typename T>
struct DefaultComparator {
    bool operator()(T const& a, T const& b) const noexcept {
        return a > b;
    }
};

/// A bounded priority queue: keeps at most `capacity` items of type T,
/// ordered by Comparator (default = DefaultComparator<T>).
template<
    typename T,
    class Comparator = DefaultComparator<T>
>
class PriorityQueue {
public:
    /// Create a PriorityQueue that holds at most `capacity` elements.
    explicit PriorityQueue(std::size_t capacity = 5)
        : capacity_(capacity) {}

    /// Insert `value` in sorted order (O(n)). If size > capacity_,
    /// pop the worst (last) element.
    void push(T const& value) {
        // find insert position
        auto it = data_.begin();
        while (it != data_.end() && !comp_(value, *it)) {
            ++it;
        }
        data_.insert(it, value);

        // drop the last if we exceeded capacity
        if (data_.size() > capacity_) {
            data_.pop_back();
        }
    }

    /// Remove & return the highest-priority element (O(1)).
    /// Call only if !empty().
    T poll() {
        T top = data_.front();
        data_.pop_front();
        return top;
    }

    bool empty() const noexcept { return data_.empty(); }
    std::size_t size()  const noexcept { return data_.size(); }

private:
    std::size_t   capacity_;
    std::list<T>  data_;
    Comparator    comp_;
};
