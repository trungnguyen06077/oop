#include "Table.h"

Table::Table(int num) : tableNumber(num), status("Trong") {}

int Table::getTableNumber() const { return tableNumber; }
std::string Table::getStatus() const { return status; }
void Table::setStatus(std::string stat) { status = stat; }

void Table::addItem(std::shared_ptr<MenuItem> item, int qty) {
    for (size_t i = 0; i < orderedItems.size(); ++i) {
        if (orderedItems[i]->getId() == item->getId()) { 
            quantities[i] += qty; 
            return; 
        }
    }
    orderedItems.push_back(item); 
    quantities.push_back(qty);
}

const std::vector<std::shared_ptr<MenuItem>>& Table::getOrderedItems() const { return orderedItems; }
const std::vector<int>& Table::getQuantities() const { return quantities; }
void Table::clearOrder() { orderedItems.clear(); quantities.clear(); }
