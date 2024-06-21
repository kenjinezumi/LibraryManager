#ifndef BOOK_H
#define BOOK_H

#include <string>

/**
 * @class Book
 * @brief Represents a book in the library.
 */
class Book {
public:
    int id;
    std::string title;
    std::string author;
    std::string genre;
    bool isLoaned;
    std::string dueDate;

    /**
     * @brief Constructs a new Book object.
     * @param bookId The unique identifier for the book.
     * @param bookTitle The title of the book.
     * @param bookAuthor The author of the book.
     * @param bookGenre The genre of the book.
     */
    Book(int bookId, const std::string& bookTitle, const std::string& bookAuthor, const std::string& bookGenre);

    bool operator<(const Book& other) const {
        return id < other.id;
    }

    bool operator>(const Book& other) const {
        return id > other.id;
    }

    bool operator==(const Book& other) const {
        return id == other.id;
    }
};

#endif // BOOK_H
