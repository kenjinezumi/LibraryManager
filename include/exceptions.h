#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

/**
 * @class LibraryException
 * @brief Custom exception class for library-related errors.
 */
class LibraryException : public std::exception {
private:
    std::string message;

public:
    explicit LibraryException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif // EXCEPTIONS_H
