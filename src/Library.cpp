#include "Library.h"
#include <fstream>
#include <nlohmann/json.hpp>

void Library::addBook(const Book& book) {
    if (books.search(book)) {
        throw LibraryException("Book with the same ID already exists.");
    }
    books.insert(book);
}

void Library::addUser(const User& user) {
    if (users.find(user.id) != users.end()) {
        throw LibraryException("User with the same ID already exists.");
    }
    users[user.id] = user;
}

void Library::loanBook(int bookId, int userId, const std::string& dueDate) {
    auto nodePtr = books.search(Book(bookId, "", "", ""));
    if (!nodePtr) {
        throw LibraryException("Book not found.");
    }
    Book& book = nodePtr->data;

    if (users.find(userId) == users.end()) {
        throw LibraryException("User not found.");
    }

    if (book.isLoaned) {
        throw LibraryException("Book is already loaned.");
    }

    book.isLoaned = true;
    book.dueDate = dueDate;
    loans[bookId] = userId;

    std::cout << "Loaned book: ID=" << book.id << ", Title=" << book.title << " to user: ID=" << userId << " due on: " << dueDate << std::endl;
}

void Library::returnBook(int bookId) {
    auto nodePtr = books.search(Book(bookId, "", "", ""));
    if (!nodePtr) {
        throw LibraryException("Book not found.");
    }
    Book& book = nodePtr->data;

    if (!book.isLoaned) {
        throw LibraryException("Book is not loaned.");
    }

    book.isLoaned = false;
    book.dueDate = "";
    loans.erase(bookId);

    std::cout << "Returned book: ID=" << book.id << ", Title=" << book.title << std::endl;
}

std::vector<Book> Library::listAllBooks() const {
    return books.inorder();
}

void Library::loadLibraryState(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw LibraryException("Could not open file for loading library state.");
    }

    nlohmann::json j;
    file >> j;

    for (const auto& item : j["books"]) {
        Book book = item.get<Book>();
        books.insert(book);
    }

    for (const auto& item : j["users"]) {
        User user = item.get<User>();
        users[user.id] = user;
    }

    for (const auto& item : j["loans"].items()) {
        int bookId = std::stoi(item.key());
        int userId = item.value();
        loans[bookId] = userId;
    }
}

void Library::saveLibraryState(const std::string& filename) const {
    nlohmann::json j;

    for (const auto& book : books.inorder()) {
        j["books"].push_back(book);
    }

    for (const auto& [id, user] : users) {
        j["users"].push_back(user);
    }

    for (const auto& [bookId, userId] : loans) {
        j["loans"][std::to_string(bookId)] = userId;
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        throw LibraryException("Could not open file for saving library state.");
    }
    file << j.dump(4);
}

void Library::loadUsersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw LibraryException("Could not open file for loading users.");
    }

    nlohmann::json j;
    file >> j;

    for (const auto& item : j) {
        User user = item.get<User>();
        users[user.id] = user;
    }
}

void Library::saveUsersToFile(const std::string& filename) const {
    nlohmann::json j;

    for (const auto& [id, user] : users) {
        j.push_back(user);
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        throw LibraryException("Could not open file for saving users.");
    }
    file << j.dump(4);
}
