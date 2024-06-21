#include <iostream>
#include "Library.h"
#include "exceptions.h"
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
    assert(library.searchByTitle("Test Book 1")[0].isLoaned == true);
    library.returnBook(1);
    assert(library.searchByTitle("Test Book 1")[0].isLoaned == false);

    // Search books
    assert(!library.searchByTitle("Test Book 1").empty());
    assert(!library.searchByAuthor("Author 1").empty());
    assert(!library.searchByGenre("Genre 1").empty());

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    runTests();
    return 0;
}
