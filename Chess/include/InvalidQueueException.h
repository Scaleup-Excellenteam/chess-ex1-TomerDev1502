#ifndef INVALID_QUEUE_EXCEPTION_H
#define INVALID_QUEUE_EXCEPTION_H

#include <exception>
#include <string>

/// Thrown when a queue operation is invalid (e.g. polling an empty queue)
class InvalidQueueException : public std::exception {
public:
    explicit InvalidQueueException(std::string msg = "Invalid queue operation")
        : message_(std::move(msg)) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

#endif // INVALID_QUEUE_EXCEPTION_H
