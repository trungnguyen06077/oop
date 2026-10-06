#include "Reservation.h"

Reservation::Reservation(std::string name, std::string p, int tableNum, std::string time)
    : customerName(name), phone(p), tableNumber(tableNum), timeSlot(time) {}

std::string Reservation::getCustomerName() const { return customerName; }
std::string Reservation::getPhone() const { return phone; }
int Reservation::getTableNumber() const { return tableNumber; }
std::string Reservation::getTimeSlot() const { return timeSlot; }
