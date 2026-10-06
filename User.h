#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string role;

public:
    User(std::string name, std::string r);
    std::string getUsername() const;
    std::string getRole() const;
};

#endif
