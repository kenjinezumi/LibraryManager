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

void Library::loadLibraryState(const std::string& booksFilename, const std::string& usersFilename) {
    // Load books
    std::ifstream booksFile(booksFilename);
    if (!booksFile.is_open()) {
        throw LibraryException("Could not open file for loading books.");
    }

    nlohmann::json booksJson;
    booksFile >> booksJson;
    booksFile.close();

    for (const auto& item : booksJson["books"]) {
        Book book;
        book.id = item.at("id").get<int>();
        book.title = item.at("title").get<std::string>();
        book.author = item.at("author").get<std::string>();
        book.genre = item.at("genre").get<std::string>();
        book.isLoaned = item.at("isLoaned").get<bool>();
        book.dueDate = item.at("dueDate").get<std::string>();
        books.insert(book);
    }

    // Load users
    std::ifstream usersFile(usersFilename);
    if (!usersFile.is_open()) {
        throw LibraryException("Could not open file for loading users.");
    }

    nlohmann::json usersJson;
    usersFile >> usersJson;
    usersFile.close();

    for (const auto& item : usersJson["users"]) {
        User user;
        user.id = item.at("id").get<int>();
        user.name = item.at("name").get<std::string>();
        users[user.id] = user;
    }
}

void Library::saveLibraryState(const std::string& booksFilename, const std::string& usersFilename) const {
    nlohmann::json booksJson;

    for (const auto& book : books.inorder()) {
        nlohmann::json bookJson;
        bookJson["id"] = book.id;
        bookJson["title"] = book.title;
        bookJson["author"] = book.author;
        bookJson["genre"] = book.genre;
        bookJson["isLoaned"] = book.isLoaned;
        bookJson["dueDate"] = book.dueDate;
        booksJson["books"].push_back(bookJson);
    }

    std::ofstream booksFile(booksFilename);
    if (!booksFile.is_open()) {
        throw LibraryException("Could not open file for saving books.");
    }
    booksFile << booksJson.dump(4);
    booksFile.close();

    nlohmann::json usersJson;

    for (const auto& [id, user] : users) {
        nlohmann::json userJson;
        userJson["id"] = user.id;
        userJson["name"] = user.name;
        usersJson["users"].push_back(userJson);
    }

    std::ofstream usersFile(usersFilename);
    if (!usersFile.is_open()) {
        throw LibraryException("Could not open file for saving users.");
    }
    usersFile << usersJson.dump(4);
    usersFile.close();
}

void Library::loadUsersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw LibraryException("Could not open file for loading users.");
    }

    nlohmann::json j;
    file >> j;
    file.close();

    for (const auto& item : j["users"]) {
        User user;
        user.id = item.at("id").get<int>();
        user.name = item.at("name").get<std::string>();
        users[user.id] = user;
    }
}

void Library::saveUsersToFile(const std::string& filename) const {
    nlohmann::json j;

    for (const auto& [id, user] : users) {
        nlohmann::json userJson;
        userJson["id"] = user.id;
        userJson["name"] = user.name;
        j["users"].push_back(userJson);
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        throw LibraryException("Could not open file for saving users.");
    }
    file << j.dump(4);
    file.close();
}
