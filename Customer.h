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

    std::string getFullName() const { return fullName; }
    std::string getPhoneNumber() const { return phoneNumber; }
    int getLoyaltyPoints() const { return loyaltyPoints; }

    std::string serialize() const {
        return fullName + ";" + phoneNumber + ";" + std::to_string(loyaltyPoints);
    }

    static Customer deserialize(const std::string& line) {
        size_t pos1 = line.find(';');
        if (pos1 == std::string::npos) return Customer();
        size_t pos2 = line.find(';', pos1 + 1);
        if (pos2 == std::string::npos) return Customer();

        std::string n = line.substr(0, pos1);
        std::string p = line.substr(pos1 + 1, pos2 - pos1 - 1);
        int points = std::stoi(line.substr(pos2 + 1));
        return Customer(n, p, points);
    }
};
