#ifndef QUEUE_OVERFLOW_EXCEPTION_H
#define QUEUE_OVERFLOW_EXCEPTION_H

#include <exception>
#include <string>

/// Thrown when pushing more than the allowed number of elements (max 5)
class QueueOverflowException : public std::exception {
public:
    explicit QueueOverflowException(std::string msg = "Queue overflow: too many elements")
        : message_(std::move(msg)) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

#endif // QUEUE_OVERFLOW_EXCEPTION_H
