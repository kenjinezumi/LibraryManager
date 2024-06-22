#include <iostream>
#include "Library.h"
#include <cassert>

/**
 * @brief Unit tests for the library system.
 */
void runTests() {
    Library library;

    // Add books
    library.addBook(Book(1, "Test Book 1", "Author 1", "Genre 1"));
    library.addBook(Book(2, "Test Book 2", "Author 2", "Genre 2"));

    // Add users
    library.addUser(User(1, "Test User 1"));
    library.addUser(User(2, "Test User 2"));

    // Loan and return a book
    library.loanBook(1, 1, "2024-06-30");
    auto searchResults = library.listAllBooks();
    for(const auto& book : searchResults) {
        if(book.title == "Test Book 1") {
            assert(book.isLoaned == true);
        }
    }
    library.returnBook(1);
    searchResults = library.listAllBooks();
    for(const auto& book : searchResults) {
        if(book.title == "Test Book 1") {
            assert(book.isLoaned == false);
        }
    }

    // Save and load library state
    library.saveLibraryState("books.json", "users.json");
    Library newLibrary;
    newLibrary.loadLibraryState("books.json", "users.json");

    // Verify loaded data
    auto loadedBooks = newLibrary.listAllBooks();
    assert(loadedBooks.size() == 2);
    assert(loadedBooks[0].title == "Test Book 1" || loadedBooks[1].title == "Test Book 1");

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    runTests();
    return 0;
}
