#include "User.h"

User::User(std::string name, std::string r) : username(name), role(r) {}
std::string User::getUsername() const { return username; }
std::string User::getRole() const { return role; }
