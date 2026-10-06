#include "Menuitem.h"

MenuItem::MenuItem(std::string id, std::string name, double price) 
    : id(id), name(name), basePrice(price) {}

std::string MenuItem::getId() const { return id; }
std::string MenuItem::getName() const { return name; }
double MenuItem::getBasePrice() const { return basePrice; }
