#include "Drink.h"

Drink::Drink(std::string id, std::string name, double price, bool alcohol) 
    : MenuItem(id, name, price), isAlcoholic(alcohol) {}

double Drink::calculateServiceTax() const { 
    return isAlcoholic ? (basePrice * 0.10) : (basePrice * 0.05); // Thue 10% neu co con
}

std::string Drink::getType() const { return "Drink"; }
bool Drink::getAlcoholicStatus() const { return isAlcoholic; }
