#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <stdexcept>
#include "MenuItem.h"
#include "Order.h"
#include "MenuItem.h"
#include "DiscountedItem.h"

class RestaurantManager {
private:
    std::vector<std::unique_ptr<MenuItem>> menu;
    std::vector<Order> orderHistory;
    const std::string adminPassword = "admin";

public:
    void addDish(std::string name, double price, std::string category) {
        menu.push_back(std::make_unique<MenuItem>(std::move(name), price, std::move(category)));
    }

    void addOrder(const Order& order) {
        orderHistory.push_back(order);
    }

    bool authenticateAdmin(const std::string& password) {
        return password == adminPassword;
    }

    void saveMenuToFile(const std::string& filename) {
        std::ofstream outFile(filename);
        if (!outFile) {
            throw std::runtime_error("Could not open menu file for writing.");
        }
        for (const auto& item : menu) {
            outFile << item->serialize() << "\n";
        }
    }

    std::unique_ptr<MenuItem> parseMenuItem(const std::string& line) {
        size_t pos_type = line.find(';');
        if (pos_type == std::string::npos) return nullptr;
        
        std::string type = line.substr(0, pos_type);
        std::string rest = line.substr(pos_type + 1);
        
        size_t pos1 = rest.find(';');
        if (pos1 == std::string::npos) return nullptr;
        size_t pos2 = rest.find(';', pos1 + 1);
        if (pos2 == std::string::npos) return nullptr;

        std::string name = rest.substr(0, pos1);
        double price = std::stod(rest.substr(pos1 + 1, pos2 - pos1 - 1));
        
        if (type == "MENU_ITEM") {
            std::string cat = rest.substr(pos2 + 1);
            return std::make_unique<MenuItem>(name, price, cat);
        } else if (type == "DISCOUNTED_ITEM") {
            size_t pos3 = rest.find(';', pos2 + 1);
            if (pos3 == std::string::npos) return nullptr;
            std::string cat = rest.substr(pos2 + 1, pos3 - pos2 - 1);
            double disc = std::stod(rest.substr(pos3 + 1));
            return std::make_unique<DiscountedItem>(name, price, cat, disc);
        }
        return nullptr;
    }

    void loadMenuFromFile(const std::string& filename) {
        menu.clear();
        std::ifstream inFile(filename);
        if (!inFile) return; 
        
        std::string line;
        while (std::getline(inFile, line)) {
            if (line.empty()) continue;
            auto item = parseMenuItem(line);
            if (item) {
                menu.push_back(std::move(item));
            }
        }
    }

    void saveHistoryToFile(const std::string& filename) {
        std::ofstream outFile(filename);
        if (!outFile) {
            throw std::runtime_error("Could not open history file for writing.");
        }
        for (const auto& order : orderHistory) {
            outFile << order.serialize() << "\n";
        }
    }

    void loadHistoryFromFile(const std::string& filename) {
        orderHistory.clear();
        std::ifstream inFile(filename);
        if (!inFile) return; 

        std::string line;
        while (std::getline(inFile, line)) {
            if (line.empty()) continue;
            orderHistory.push_back(Order::deserialize(line));
        }
    }

    const std::vector<std::unique_ptr<MenuItem>>& getMenu() const { return menu; }
    const std::vector<Order>& getOrderHistory() const { return orderHistory; }
};
