#include "Book.h"

void to_json(nlohmann::json& j, const Book& b) {
    j = nlohmann::json{{"id", b.id}, {"title", b.title}, {"author", b.author}, {"genre", b.genre}, {"isLoaned", b.isLoaned}, {"dueDate", b.dueDate}};
}

void from_json(const nlohmann::json& j, Book& b) {
    j.at("id").get_to(b.id);
    j.at("title").get_to(b.title);
    j.at("author").get_to(b.author);
    j.at("genre").get_to(b.genre);
    j.at("isLoaned").get_to(b.isLoaned);
    j.at("dueDate").get_to(b.dueDate);
}
