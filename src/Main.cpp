#include <iostream>
#include <fstream>
#include "Library.h"
#include "nlohmann/json.hpp"
#include "exceptions.h"

using json = nlohmann::json;

/**
 * @brief Loads books from a JSON file and adds them to the library.
 * @param library The library to add books to.
 * @param filename The JSON file containing the book data.
 */
void loadBooksFromFile(Library& library, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    json j;
    file >> j;

    for (const auto& item : j) {
        Book book(item["id"], item["title"], item["author"], item["genre"]);
        library.addBook(book);
    }
}

void showUsage() {
    std::cout << "Usage: LibraryManagerPro <command> [<args>]\n";
    std::cout << "Commands:\n";
    std::cout << "  loadbooks <file>           Load books from a JSON file\n";
    std::cout << "  adduser <id> <name>        Add a user\n";
    std::cout << "  loanbook <bookId> <userId> <dueDate>  Loan a book to a user\n";
    std::cout << "  returnbook <bookId>        Return a loaned book\n";
    std::cout << "  search <field> <value>     Search books by title, author, or genre\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        showUsage();
        return 1;
    }

    Library library;

    std::string command = argv[1];

    try {
        if (command == "loadbooks") {
            if (argc != 3) {
                showUsage();
                return 1;
            }
            loadBooksFromFile(library, argv[2]);
        } else if (command == "adduser") {
            if (argc != 4) {
                showUsage();
                return 1;
            }
            int userId = std::stoi(argv[2]);
            std::string userName = argv[3];
            library.addUser(User(userId, userName));
        } else if (command == "loanbook") {
            if (argc != 5) {
                showUsage();
                return 1;
            }
            int bookId = std::stoi(argv[2]);
            int userId = std::stoi(argv[3]);
            std::string dueDate = argv[4];
            library.loanBook(bookId, userId, dueDate);
        } else if (command == "returnbook") {
            if (argc != 3) {
                showUsage();
                return 1;
            }
            int bookId = std::stoi(argv[2]);
            library.returnBook(bookId);
        } else if (command == "search") {
            if (argc != 4) {
                showUsage();
                return 1;
            }
            std::string field = argv[2];
            std::string value = argv[3];
            std::vector<Book> results;

            if (field == "title") {
                results = library.searchByTitle(value);
            } else if (field == "author") {
                results = library.searchByAuthor(value);
            } else if (field == "genre") {
                results = library.searchByGenre(value);
            } else {
                std::cerr << "Unknown search field: " << field << std::endl;
                return 1;
            }

            for (const auto& book : results) {
                std::cout << "Found book: " << book.title << " by " << book.author << " (Genre: " << book.genre << ")\n";
            }
        } else {
            showUsage();
            return 1;
        }
    } catch (const LibraryException& e) {
        std::cerr << "Library error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
