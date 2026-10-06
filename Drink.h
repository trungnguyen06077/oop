#ifndef DRINK_H
#define DRINK_H

#include "MenuItem.h"

class Drink : public MenuItem {
private:
    bool isAlcoholic;

public:
    Drink(std::string id, std::string name, double price, bool alcohol);
    double calculateServiceTax() const override; 
    std::string getType() const override;
    bool getAlcoholicStatus() const;
};

#endif
