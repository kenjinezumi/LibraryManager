#ifndef USER_H
#define USER_H

#include <string>
#include <nlohmann/json.hpp>

class User {
public:
    int id;
    std::string name;

    User() : id(0), name("") {}
    User(int userId, const std::string& userName) : id(userId), name(userName) {}

    bool operator==(const User& other) const {
        return id == other.id;
    }

    bool operator<(const User& other) const {
        return id < other.id;
    }

    bool operator>(const User& other) const {
        return id > other.id;
    }
};

void to_json(nlohmann::json& j, const User& u);
void from_json(const nlohmann::json& j, User& u);

#endif // USER_H
