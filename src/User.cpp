#include "User.h"

void to_json(nlohmann::json& j, const User& u) {
    j = nlohmann::json{{"id", u.id}, {"name", u.name}};
}

void from_json(const nlohmann::json& j, User& u) {
    j.at("id").get_to(u.id);
    j.at("name").get_to(u.name);
}
