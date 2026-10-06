#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

class Reservation {
private:
    std::string customerName;
    std::string phone;
    int tableNumber;
    std::string timeSlot;

public:
    Reservation(std::string name, std::string p, int tableNum, std::string time);
    std::string getCustomerName() const;
    std::string getPhone() const;
    int getTableNumber() const;
    std::string getTimeSlot() const;
};

#endif
