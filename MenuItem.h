#pragma once
#include <iostream>
#include <string>

class MenuItem {
private:
    std::string name;
    double price;
    std::string category;

public:
    MenuItem(std::string n, double p, std::string c) 
        : name(n), price(p), category(c) {
        std::cout << "[MenuItem] Main constructor called\n";
    }

    MenuItem(std::string n, double p) 
        : MenuItem(n, p, "No category") { 
        std::cout << "[MenuItem] Delegated constructor called\n";
    }

    MenuItem() : MenuItem("Unknown dish", 0.0, "General") {
        std::cout << "[MenuItem] Default constructor called\n";
    }

    ~MenuItem() {
        std::cout << "[MenuItem] Destructor called for " << name << "\n";
    }

    void display() const {
        std::cout << "Dish: " << name << " | Price: " << price << " | Category: " << category << "\n";
    }
};
