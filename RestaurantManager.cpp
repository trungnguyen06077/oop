#include "RestaurantManager.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

RestaurantManager::RestaurantManager() : totalRevenue(0.0) {
    for (int i = 1; i <= 5; ++i) { tables.push_back(Table(i)); }
}

void RestaurantManager::loadMenuFromCSV() {
    std::ifstream file("menu.csv");
    if (!file.is_open()) {
        menu.push_back(std::make_shared<Food>("F01", "Pho Bo Dac Biet", 65000, "Mon Chinh"));
        menu.push_back(std::make_shared<Food>("F02", "Com Tam Suon Nuong", 55000, "Mon Chinh"));
        menu.push_back(std::make_shared<Drink>("D01", "Ca Phe Sua Da", 25000, false));
        menu.push_back(std::make_shared<Drink>("D02", "Bia Sai Gon", 20000, true));
        
        std::ofstream outFile("menu.csv");
        for (const auto& item : menu) {
            if (item->getType() == "Food") {
                auto f = std::dynamic_pointer_cast<Food>(item);
                outFile << "Food," << item->getId() << "," << item->getName() << "," << item->getBasePrice() << "," << f->getDishType() << "\n";
            } else {
                auto d = std::dynamic_pointer_cast<Drink>(item);
                outFile << "Drink," << item->getId() << "," << item->getName() << "," << item->getBasePrice() << "," << (d->getAlcoholicStatus() ? "1" : "0") << "\n";
            }
        }
        outFile.close(); return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string type, id, name, priceStr, opt;
        std::getline(ss, type, ','); std::getline(ss, id, ','); std::getline(ss, name, ','); std::getline(ss, priceStr, ','); std::getline(ss, opt, ',');
        if (!id.empty()) {
            if (type == "Food") menu.push_back(std::make_shared<Food>(id, name, std::stod(priceStr), opt));
            else menu.push_back(std::make_shared<Drink>(id, name, std::stod(priceStr), opt == "1"));
        }
    }
    file.close();
}

void RestaurantManager::saveRevenueToCSV(double amount) {
    totalRevenue += amount;
    std::ofstream file("revenue.csv", std::ios::app);
    file << "Thanh toan," << amount << " VND\n";
    file.close();
}

void RestaurantManager::displayTables() const {
    std::cout << "\n--- TRANG THAI BAN AN ---\n";
    for (const auto& t : tables) {
        std::cout << " Ban so " << t.getTableNumber() << " | Trang thai: ";
        if (t.getStatus() == "Trong") std::cout << "[Xanh - Trong]\n";
        else if (t.getStatus() == "Da dat truoc") std::cout << "[Vang - Da dat truoc]\n";
        else std::cout << "[Do - Dang ngoi an]\n";
    }
}

void RestaurantManager::displayMenu() const {
    std::cout << "\n-----------------------------------------------------\n";
    std::cout << std::left << std::setw(8) << "Ma Mon" << std::setw(25) << "Ten Mon/Do Uong" << "Gia Goc\n";
    std::cout << "-----------------------------------------------------\n";
    for (const auto& item : menu) {
        std::cout << std::left << std::setw(8) << item->getId() << std::setw(25) << item->getName() << item->getBasePrice() << " VND\n";
    }
}

void RestaurantManager::createReservation() {
    std::string name, phone, time;
    int tableNum;
    std::cout << "\n--- DAT BAN TRUOC ---\n";
    std::cout << "Nhap ten khach hang: "; std::cin.ignore(); std::getline(std::cin, name);
    std::cout << "Nhap so dien thoai: "; std::cin >> phone;
    displayTables();
    std::cout << "Nhap so ban muon dat: "; std::cin >> tableNum;

    if (tableNum < 1 || tableNum > (int)tables.size() || tables[tableNum - 1].getStatus() != "Trong") {
        std::cout << ">> Ban khong hop le hoac da co khach!\n"; return;
    }
    std::cout << "Nhap gio hen (Vi du: 19:00): "; std::cin >> time;

    reservations.push_back(Reservation(name, phone, tableNum, time));
    tables[tableNum - 1].setStatus("Da dat truoc");
    std::cout << ">> Dat ban thanh cong cho khach " << name << " vao luc " << time << "!\n";
}

void RestaurantManager::displayReservations() const {
    std::cout << "\n--- DANH SACH LICH DAT BAN ---\n";
    if (reservations.empty()) { std::cout << "Khong co lich dat ban nao.\n"; return; }
    for (const auto& r : reservations) {
        std::cout << " Khach: " << std::setw(15) << r.getCustomerName() << " | SDT: " << std::setw(12) << r.getPhone()
                  << " | Ban: " << r.getTableNumber() << " | Gio hen: " << r.getTimeSlot() << "\n";
    }
}

void RestaurantManager::orderFood() {
    int tableNum;
    displayTables();
    std::cout << "\nNhap so ban: "; std::cin >> tableNum;
    if (tableNum < 1 || tableNum > (int)tables.size()) return;

    Table& table = tables[tableNum - 1];
    table.setStatus("Dang co khach");

    displayMenu();
    std::string itemId; int qty;
    while (true) {
        std::cout << "Nhap Ma Mon (go '0' de dung): "; std::cin >> itemId;
        if (itemId == "0") break;

        std::shared_ptr<MenuItem> found = nullptr;
        for (const auto& item : menu) { if (item->getId() == itemId) { found = item; break; } }

        if (found) {
            std::cout << "Nhap so luong: "; std::cin >> qty;
            table.addItem(found, qty);
            std::cout << ">> Da them mon!\n";
        } else std::cout << ">> Ma khong ton tai!\n";
    }
}

void RestaurantManager::checkoutTable() {
    int tableNum;
    std::cout << "\nNhap so ban thanh toan: "; std::cin >> tableNum;
    if (tableNum < 1 || tableNum > (int)tables.size()) return;

    Table& table = tables[tableNum - 1];
    if (table.getStatus() == "Trong") { std::cout << ">> Ban trong!\n"; return; }

    double subTotal = 0, taxTotal = 0;
    std::cout << "\n--- CHI TIET HOA DON BAN SO " << tableNum << " ---\n";
    auto items = table.getOrderedItems(); auto qtys = table.getQuantities();

    for (size_t i = 0; i < items.size(); ++i) {
        double cost = items[i]->getBasePrice() * qtys[i];
        double tax = items[i]->calculateServiceTax() * qtys[i]; 
        subTotal += cost; taxTotal += tax;
        std::cout << " + " << items[i]->getName() << " x" << qtys[i] << " = " << cost << " VND (Thue: " << tax << ")\n";
    }

    double finalTotal = subTotal + taxTotal;
    std::cout << "--------------------------------------\n";
    std::cout << " Tong tien mon goc: " << subTotal << " VND\n";
    std::cout << " Tong thue dich vu: " << taxTotal << " VND\n";
    std::cout << " TONG THANH TOAN:   " << finalTotal << " VND\n";
    
    saveRevenueToCSV(finalTotal);
    table.clearOrder(); table.setStatus("Trong");
    
    for (auto it = reservations.begin(); it != reservations.end(); ) {
        if (it->getTableNumber() == tableNum) { it = reservations.erase(it); }
        else { ++it; }
    }
    std::cout << ">> Thanh toan xong! Ban duoc don trong.\n";
}

void RestaurantManager::viewRevenue(const User& user) const {
    if (user.getRole() != "Manager") {
        std::cout << ">> Tu choi! Quyen truy cap chi thuoc ve Manager.\n"; return;
    }
    std::cout << "\n=======================================\n";
    std::cout << " DOANH THU NHA HANG TICH LUY: " << totalRevenue << " VND\n";
    std::cout << "=======================================\n";
}
