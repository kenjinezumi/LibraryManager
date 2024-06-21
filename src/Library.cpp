#include "Library.h"
#include "exceptions.h"
#include <algorithm>

Library::Library() : logger("library.log") {}

void Library::addBook(const Book& book) {
    std::lock_guard<std::mutex> lock(mtx);
    if (books.search(book)) {
        throw LibraryException("Book with the same ID already exists.");
    }
    books.insert(book);
    logger.log("Added book: " + book.title);
}

void Library::addUser(const User& user) {
    std::lock_guard<std::mutex> lock(mtx);
    if (users.find(user.id) != users.end()) {
        throw LibraryException("User with the same ID already exists.");
    }
    users[user.id] = user;
    logger.log("Added user: " + user.name);
}

void Library::loanBook(int bookId, int userId, const std::string& dueDate) {
    std::lock_guard<std::mutex> lock(mtx);
    Book* bookPtr = books.search(Book(bookId, "", "", ""));
    if (!bookPtr) {
        throw LibraryException("Book not found.");
    }
    if (users.find(userId) == users.end()) {
        throw LibraryException("User not found.");
    }
    if (bookPtr->isLoaned) {
        throw LibraryException("Book is already loaned.");
    }
    bookPtr->isLoaned = true;
    bookPtr->dueDate = dueDate;
    loans[bookId] = userId;
    logger.log("Loaned book: " + bookPtr->title + " to user: " + users[userId].name + " due on: " + dueDate);
}

void Library::returnBook(int bookId) {
    std::lock_guard<std::mutex> lock(mtx);
    Book* bookPtr = books.search(Book(bookId, "", "", ""));
    if (!bookPtr) {
        throw LibraryException("Book not found.");
    }
    if (!bookPtr->isLoaned) {
        throw LibraryException("Book is not loaned.");
    }
    bookPtr->isLoaned = false;
    bookPtr->dueDate = "";
    loans.erase(bookId);
    logger.log("Returned book: " + bookPtr->title);
}

std::vector<Book> Library::searchByTitle(const std::string& title) {
    std::lock_guard<std::mutex> lock(mtx);
    std::vector<Book> result;
    auto booksInOrder = books.inorder();
    for (const auto& book : booksInOrder) {
        if (book.title.find(title) != std::string::npos) {
            result.push_back(book);
        }
    }
    return result;
}

std::vector<Book> Library::searchByAuthor(const std::string& author) {
    std::lock_guard<std::mutex> lock(mtx);
    std::vector<Book> result;
    auto booksInOrder = books.inorder();
    for (const auto& book : booksInOrder) {
        if (book.author.find(author) != std::string::npos) {
            result.push_back(book);
        }
    }
    return result;
}

std::vector<Book> Library::searchByGenre(const std::string& genre) {
    std::lock_guard<std::mutex> lock(mtx);
    std::vector<Book> result;
    auto booksInOrder = books.inorder();
    for (const auto& book : booksInOrder) {
        if (book.genre.find(genre) != std::string::npos) {
            result.push_back(book);
        }
    }
    return result;
}
