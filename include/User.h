#ifndef USER_H
#define USER_H

#include <string>

/**
 * @class User
 * @brief Represents a user of the library.
 */
class User {
public:
    int id;
    std::string name;

    /**
     * @brief Constructs a new User object.
     * @param userId The unique identifier for the user.
     * @param userName The name of the user.
     */
    User(int userId, const std::string& userName);

    User() = default;  // Default constructor
};

#endif // USER_H
