#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Library.h"
#include "Logger.h"

void loadBooksFromFile(Library& library, const std::string& filename) {
    library.loadLibraryState(filename);
}

void saveBooksToFile(const Library& library, const std::string& filename) {
    library.saveLibraryState(filename);
}

void loadUsersFromFile(Library& library, const std::string& filename) {
    library.loadUsersFromFile(filename);
}

void saveUsersToFile(const Library& library, const std::string& filename) {
    library.saveUsersToFile(filename);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <command> [arguments]" << std::endl;
        return 1;
    }

    Library library;

    // Automatically load state from files
    loadBooksFromFile(library, "../data/books.json");
    loadUsersFromFile(library, "../data/users.json");

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
                std::cout << "ID=" << book.id << ", Title=" << book.title << ", Author=" << book.author << ", Genre=" << book.genre << std::endl;
            }
        } else {
            std::cerr << "Unknown command: " << command << std::endl;
            return 1;
        }
    } catch (const LibraryException& e) {
        std::cerr << "Library error: " << e.what() << std::endl;
        return 1;
    }

    // Automatically save state to files
    saveBooksToFile(library, "../data/books.json");
    saveUsersToFile(library, "../data/users.json");

    return 0;
}
