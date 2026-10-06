#ifndef TABLE_H
#define TABLE_H

#include "MenuItem.h"
#include <vector>
#include <memory>
#include <string> 

class Table {
private:
    int tableNumber;
    std::string status;
    std::vector<int> quantities;
    std::vector<std::shared_ptr<MenuItem>> orderedItems; 

public:
    Table(int num);
    int getTableNumber() const;
    std::string getStatus() const;
    void setStatus(std::string stat);
    
    void addItem(std::shared_ptr<MenuItem> item, int qty);
    const std::vector<std::shared_ptr<MenuItem>>& getOrderedItems() const;
    const std::vector<int>& getQuantities() const; 
    void clearOrder();
};

#endif