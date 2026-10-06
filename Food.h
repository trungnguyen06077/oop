#ifndef FOOD_H
#define FOOD_H

#include "Menuitem.h"

class Food : public MenuItem {
private:
    std::string dishType;

public:
    Food(std::string id, std::string name, double price, std::string type);
    double calculateServiceTax() const override; 
    std::string getType() const override;
    std::string getDishType() const;
};

#endif	
