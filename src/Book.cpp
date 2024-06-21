#include "Book.h"

Book::Book(int bookId, const std::string& bookTitle, const std::string& bookAuthor, const std::string& bookGenre)
    : id(bookId), title(bookTitle), author(bookAuthor), genre(bookGenre), isLoaned(false), dueDate("") {}
