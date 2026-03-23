#pragma once
#include <iostream>
#include <string>
#include <utility>

class Customer {
private:
    std::string fullName;
    std::string phoneNumber;
    int loyaltyPoints;

public:
    Customer(std::string name, std::string phone, int points)
        : fullName(std::move(name)), phoneNumber(std::move(phone)), loyaltyPoints(points) {}

    Customer(std::string name) : Customer(std::move(name), "Unknown", 10) {}

    Customer() : Customer("Guest", "None", 0) {}

    ~Customer() = default;


    void addLoyaltyPoints(int points) {
        this->loyaltyPoints += points;
    }

    void displayInfo() const {
        std::cout << "Customer: " << fullName << " | Phone: " << phoneNumber << " | Points: " << loyaltyPoints << std::endl;
    }
};
