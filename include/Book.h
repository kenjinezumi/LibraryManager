#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <nlohmann/json.hpp>

class Book {
public:
    int id;
    std::string title;
    std::string author;
    std::string genre;
    bool isLoaned;
    std::string dueDate;

    Book() : id(0), title(""), author(""), genre(""), isLoaned(false), dueDate("") {}
    Book(int bookId, const std::string& bookTitle, const std::string& bookAuthor, const std::string& bookGenre)
        : id(bookId), title(bookTitle), author(bookAuthor), genre(bookGenre), isLoaned(false), dueDate("") {}

    bool operator==(const Book& other) const {
        return id == other.id;
    }

    bool operator<(const Book& other) const {
        return id < other.id;
    }

    bool operator>(const Book& other) const {
        return id > other.id;
    }
};

void to_json(nlohmann::json& j, const Book& b);
void from_json(const nlohmann::json& j, Book& b);

#endif // BOOK_H
