#include "MenuItem.h"
#ifndef RESTAURANTMANAGER_H
#define RESTAURANTMANAGER_H

#include "Menuitem.h"
#include "Food.h"
#include "Drink.h"
#include "Table.h"
#include "Reservation.h"
#include "User.h"
#include <vector>
#include <memory>

class RestaurantManager {
private:
    std::vector<std::shared_ptr<MenuItem>> menu;
    std::vector<Table> tables;
    std::vector<Reservation> reservations;
    double totalRevenue;

public:
    RestaurantManager();
    void loadMenuFromCSV();
    void saveRevenueToCSV(double amount);
    
    void displayTables() const;
    void displayMenu() const;
    void createReservation(); 
    void displayReservations() const;
    void orderFood();
    void checkoutTable();
    void viewRevenue(const User& user) const;
};

#endif
