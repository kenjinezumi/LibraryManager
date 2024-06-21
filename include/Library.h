#ifndef LIBRARY_H
#define LIBRARY_H

#include <unordered_map>
#include <vector>
#include <mutex>
#include "Book.h"
#include "User.h"
#include "Logger.h"
#include "AVLTree.h"

/**
 * @class Library
 * @brief Manages the collection of books and user loans in the library.
 */
class Library {
private:
    AVLTree<Book> books;
    std::unordered_map<int, User> users;
    std::unordered_map<int, int> loans; // map of book ID to user ID
    std::mutex mtx;
    Logger logger;

public:
    /**
     * @brief Constructs a new Library object.
     */
    Library();

    /**
     * @brief Adds a new book to the library.
     * @param book The book to add.
     */
    void addBook(const Book& book);

    /**
     * @brief Adds a new user to the library.
     * @param user The user to add.
     */
    void addUser(const User& user);

    /**
     * @brief Loans a book to a user.
     * @param bookId The ID of the book to loan.
     * @param userId The ID of the user borrowing the book.
     * @param dueDate The due date for returning the book.
     */
    void loanBook(int bookId, int userId, const std::string& dueDate);

    /**
     * @brief Returns a loaned book to the library.
     * @param bookId The ID of the book to return.
     */
    void returnBook(int bookId);

    /**
     * @brief Searches for books by title.
     * @param title The title to search for.
     * @return A vector of books that match the title.
     */
    std::vector<Book> searchByTitle(const std::string& title);

    /**
     * @brief Searches for books by author.
     * @param author The author to search for.
     * @return A vector of books that match the author.
     */
    std::vector<Book> searchByAuthor(const std::string& author);

    /**
     * @brief Searches for books by genre.
     * @param genre The genre to search for.
     * @return A vector of books that match the genre.
     */
    std::vector<Book> searchByGenre(const std::string& genre);
};

#endif // LIBRARY_H
