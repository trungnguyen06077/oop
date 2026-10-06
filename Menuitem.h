#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>

class MenuItem {
protected:
    std::string id;
    std::string name;
    double basePrice;

public:
    MenuItem(std::string id, std::string name, double price);
    virtual ~MenuItem() = default;

    std::string getId() const;
    std::string getName() const;
    double getBasePrice() const;

    virtual double calculateServiceTax() const = 0; 
    virtual std::string getType() const = 0;
};

#endif
