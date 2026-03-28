#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits>
#include "MenuItem.h"
#include "Customer.h"
#include "Order.h"
#include "DiscountedItem.h"
#include "RestaurantManager.h"

int Order::totalOrdersCreated = 0;

void clearCin() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clearCin();
            return value;
        } else {
            std::cout << "Invalid input. Please enter a number.\n";
            clearCin();
        }
    }
}

double getDoubleInput(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clearCin();
            return value;
        } else {
            std::cout << "Invalid input. Please enter a number.\n";
            clearCin();
        }
    }
}

std::string getStringInput(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

void adminMenu(RestaurantManager& manager) {
    std::string password = getStringInput("Enter admin password: ");
    if (!manager.authenticateAdmin(password)) {
        std::cout << "Incorrect password.\n";
        return;
    }

    while (true) {
        std::cout << "\n--- ADMIN MENU ---\n";
        std::cout << "1. Add Dish\n";
        std::cout << "2. View Order History\n";
        std::cout << "3. Exit to Main Menu\n";
        
        int choice = getIntInput("Select an option: ");
        if (choice == 1) {
            std::string name = getStringInput("Enter dish name: ");
            double price = getDoubleInput("Enter price: ");
            std::string cat = getStringInput("Enter category: ");
            manager.addDish(name, price, cat);
            try {
                manager.saveMenuToFile("menu.txt");
                std::cout << "Dish added and saved.\n";
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        } else if (choice == 2) {
            const auto& history = manager.getOrderHistory();
            if (history.empty()) {
                std::cout << "No orders in history.\n";
            } else {
                for (const auto& o : history) {
                    o.print(std::cout);
                    std::cout << "\n";
                }
            }
        } else if (choice == 3) {
            break;
        } else {
            std::cout << "Invalid option.\n";
        }
    }
}

void userMenu(RestaurantManager& manager) {
    while (true) {
        std::cout << "\n--- USER MENU ---\n";
        std::cout << "1. View Menu\n";
        std::cout << "2. Make Order\n";
        std::cout << "3. Exit to Main Menu\n";

        int choice = getIntInput("Select an option: ");
        if (choice == 1) {
            const auto& menu = manager.getMenu();
            if (menu.empty()) {
                std::cout << "Menu is currently empty.\n";
            } else {
                for (size_t i = 0; i < menu.size(); ++i) {
                    std::cout << "[" << i + 1 << "] ";
                    menu[i]->display();
                }
            }
        } else if (choice == 2) {
            const auto& menu = manager.getMenu();
            if (menu.empty()) {
                std::cout << "Cannot make an order, menu is empty.\n";
                continue;
            }

            std::string name = getStringInput("Enter your name: ");
            std::string phone = getStringInput("Enter your phone: ");
            Customer c(name, phone, 10);

            double total = 0.0;
            while (true) {
                std::cout << "Select dish by number (0 to finish): ";
                int dishIndex = getIntInput("");
                if (dishIndex == 0) break;
                if (dishIndex > 0 && dishIndex <= static_cast<int>(menu.size())) {
                    total += menu[dishIndex - 1]->getPrice();
                    std::cout << "Added " << menu[dishIndex - 1]->getName() << " to order.\n";
                } else {
                    std::cout << "Invalid dish number.\n";
                }
            }

            if (total > 0) {
                static int orderIdCounter = 1000;
                Order newOrder(orderIdCounter++, "Pending", total, c);
                manager.addOrder(newOrder);
                try {
                    manager.saveHistoryToFile("history.txt");
                    std::cout << "Order placed successfully! Total: " << total << " UAH. History saved.\n";
                } catch (const std::exception& e) {
                    std::cout << "Error saving history: " << e.what() << "\n";
                }
            } else {
                std::cout << "Order cancelled (no items selected).\n";
            }
        } else if (choice == 3) {
            break;
        } else {
            std::cout << "Invalid option.\n";
        }
    }
}

int main() {
    RestaurantManager manager;

    try {
        manager.loadMenuFromFile("menu.txt");
        manager.loadHistoryFromFile("history.txt");
        std::cout << "Loaded " << manager.getMenu().size() << " menu items and " << manager.getOrderHistory().size() << " order(s) from files.\n";
    } catch (const std::exception& e) {
        std::cout << "Warning during initialization: " << e.what() << "\n";
    }

    while (true) {
        std::cout << "\n=== RESTAURANT SYSTEM ===\n";
        std::cout << "1. Login as Admin\n";
        std::cout << "2. Enter as User\n";
        std::cout << "3. Exit\n";

        int choice = getIntInput("Select role: ");

        if (choice == 1) {
            adminMenu(manager);
        } else if (choice == 2) {
            userMenu(manager);
        } else if (choice == 3) {
            std::cout << "Exiting program. Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid option.\n";
        }
    }
    return 0;
}
