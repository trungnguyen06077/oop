#include "Food.h"

Food::Food(std::string id, std::string name, double price, std::string type) 
    : MenuItem(id, name, price), dishType(type) {}

double Food::calculateServiceTax() const { 
    return basePrice * 0.05; // Thue 5% cho mon an
}

std::string Food::getType() const { return "Food"; }
std::string Food::getDishType() const { return dishType; }
