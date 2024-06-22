#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Book.h"
#include "User.h"
#include "BST.h"
#include <nlohmann/json.hpp>

class LibraryException : public std::exception {
    std::string message;
public:
    explicit LibraryException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class Library {
public:
    void addBook(const Book& book);
    void addUser(const User& user);
    void loanBook(int bookId, int userId, const std::string& dueDate);
    void returnBook(int bookId);
    std::vector<Book> listAllBooks() const;
    Book getBookInfo(int bookId) const;
    void loadLibraryState(const std::string& booksFilename, const std::string& usersFilename);
    void saveLibraryState(const std::string& booksFilename, const std::string& usersFilename) const;
    void loadUsersFromFile(const std::string& filename);
    void saveUsersToFile(const std::string& filename) const;

private:
    BST<Book> books;
    std::unordered_map<int, User> users;
    std::unordered_map<int, int> loans;
};

#endif // LIBRARY_H
