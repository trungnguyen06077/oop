#include "RestaurantManager.h"
#include "User.h"
#include <iostream>

int main() {
    // Da bo het thu vien windows.h va SetConsole de tuong thich 100% tren moi he thong console
    RestaurantManager rm;
    rm.loadMenuFromCSV();

    User managerAccount("Nguyen Van A", "Manager");
    User staffAccount("Tran Thi B", "Staff");
    User currentLoggedInUser = staffAccount; 

    int choice;
    do {
        std::cout << "\n=============================================\n";
        std::cout << "  QUAN LY NHA HANG - " << currentLoggedInUser.getUsername() 
                  << " (" << currentLoggedInUser.getRole() << ")\n";
        std::cout << "=============================================\n";
        std::cout << " 1. Xem so do ban an\n";
        std::cout << " 2. Xem thuc den\n";
        std::cout << " 3. Dat ban truoc (Reservation)\n";
        std::cout << " 4. Xem danh sach lich dat ban\n";
        std::cout << " 5. Mo ban & Goi mon\n";
        std::cout << " 6. Tinh tien & Xuat hoa don (Checkout)\n";
        std::cout << " 7. Xem bao cao doanh thu (Quyen Manager)\n";
        std::cout << " 8. Chuyen doi tai khoan (Staff <-> Manager)\n";
        std::cout << " 0. Thoat chuong trinh\n";
        std::cout << "---------------------------------------------\n";
        std::cout << "Moi chon chuc nang (0-8): ";
        std::cin >> choice;

        switch (choice) {
            case 1: rm.displayTables(); break;
            case 2: rm.displayMenu(); break;
            case 3: rm.createReservation(); break;
            case 4: rm.displayReservations(); break;
            case 5: rm.orderFood(); break;
            case 6: rm.checkoutTable(); break;
            case 7: rm.viewRevenue(currentLoggedInUser); break;
            case 8:
                currentLoggedInUser = (currentLoggedInUser.getRole() == "Staff") ? managerAccount : staffAccount;
                std::cout << ">> Da chuyen doi tai khoan thanh cong!\n";
                break;
            case 0: std::cout << ">> He thong dang tat...\n"; break;
            default: std::cout << ">> Lua chon sai!\n";
        }
    } while (choice != 0);

    return 0;
}
