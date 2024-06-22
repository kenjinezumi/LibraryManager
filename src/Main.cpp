#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Library.h"
#include "Logger.h"

void loadBooksFromFile(Library& library, const std::string& filename) {
    try {
        library.loadLibraryState(filename, "../data/books.json");
    } catch (const LibraryException& e) {
        std::cerr << "Error loading books from file '" << filename << "': " << e.what() << std::endl;
        throw;
    }
}

void saveBooksToFile(const Library& library, const std::string& filename) {
    try {
        library.saveLibraryState(filename, "../data/books.json");
    } catch (const LibraryException& e) {
        std::cerr << "Error saving books to file '" << filename << "': " << e.what() << std::endl;
        throw;
    }
}

void loadUsersFromFile(Library& library, const std::string& filename) {
    try {
        library.loadUsersFromFile(filename);
    } catch (const LibraryException& e) {
        std::cerr << "Error loading users from file '" << filename << "': " << e.what() << std::endl;
        throw;
    }
}

void saveUsersToFile(const Library& library, const std::string& filename) {
    try {
        library.saveUsersToFile(filename);
    } catch (const LibraryException& e) {
        std::cerr << "Error saving users to file '" << filename << "': " << e.what() << std::endl;
        throw;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <command> [arguments]" << std::endl;
        return 1;
    }

    Library library;

    // Automatically load state from files
    try {
        loadBooksFromFile(library, "../data/books.json");
        loadUsersFromFile(library, "../data/users.json");
    } catch (const LibraryException&) {
        // Already logged in loadBooksFromFile and loadUsersFromFile
        return 1;
    }

    std::string command = argv[1];

    try {
        if (command == "loadbooks") {
            if (argc != 3) {
                std::cerr << "Usage: " << argv[0] << " loadbooks <filename>" << std::endl;
                return 1;
            }
            std::string filename = argv[2];
            loadBooksFromFile(library, filename);
        } else if (command == "savebooks") {
            if (argc != 3) {
                std::cerr << "Usage: " << argv[0] << " savebooks <filename>" << std::endl;
                return 1;
            }
            std::string filename = argv[2];
            saveBooksToFile(library, filename);
        } else if (command == "loadusers") {
            if (argc != 3) {
                std::cerr << "Usage: " << argv[0] << " loadusers <filename>" << std::endl;
                return 1;
            }
            std::string filename = argv[2];
            loadUsersFromFile(library, filename);
        } else if (command == "saveusers") {
            if (argc != 3) {
                std::cerr << "Usage: " << argv[0] << " saveusers <filename>" << std::endl;
                return 1;
            }
            std::string filename = argv[2];
            saveUsersToFile(library, filename);
        } else if (command == "listallbooks") {
            auto books = library.listAllBooks();
            for (const auto& book : books) {
                std::cout << "ID=" << book.id << ", Title=" << book.title << ", Author=" << book.author
                          << ", Genre=" << book.genre << ", Loaned=" << (book.isLoaned ? "Yes" : "No")
                          << ", Due Date=" << book.dueDate << std::endl;
            }
        } else if (command == "adduser") {
            if (argc != 4) {
                std::cerr << "Usage: " << argv[0] << " adduser <id> <name>" << std::endl;
                return 1;
            }
            int id = std::stoi(argv[2]);
            std::string name = argv[3];
            library.addUser(User(id, name));
        } else if (command == "loanbook") {
            if (argc != 5) {
                std::cerr << "Usage: " << argv[0] << " loanbook <bookId> <userId> <dueDate>" << std::endl;
                return 1;
            }
            int bookId = std::stoi(argv[2]);
            int userId = std::stoi(argv[3]);
            std::string dueDate = argv[4];
            library.loanBook(bookId, userId, dueDate);
        } else if (command == "getbookinfo") {
            if (argc != 3) {
                std::cerr << "Usage: " << argv[0] << " getbookinfo <bookId>" << std::endl;
                return 1;
            }
            int bookId = std::stoi(argv[2]);
            Book book = library.getBookInfo(bookId);
            std::cout << "ID=" << book.id << ", Title=" << book.title << ", Author=" << book.author
                      << ", Genre=" << book.genre << ", isLoaned=" << (book.isLoaned ? "Yes" : "No")
                      << ", dueDate=" << book.dueDate << std::endl;
        } else {
            std::cerr << "Unknown command: " << command << std::endl;
            return 1;
        }
    } catch (const LibraryException& e) {
        std::cerr << "Library error: " << e.what() << std::endl;
        return 1;
    }

    // Automatically save state to files
    try {
        saveBooksToFile(library, "../data/books.json");
        saveUsersToFile(library, "../data/users.json");
    } catch (const LibraryException&) {
        // Already logged in saveBooksToFile and saveUsersToFile
        return 1;
    }

    return 0;
}
