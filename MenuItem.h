#pragma once
#include <iostream>
#include <string>

class MenuItem {
protected:
    std::string name;
    double price;
    std::string category;

public:
    MenuItem(std::string n, double p, std::string c) 
        : name(n), price(p), category(c) {
        std::cout << "MenuItem created: " << name << "\n";
    }

    MenuItem(std::string n, double p) 
        : MenuItem(n, p, "No category") { 
        std::cout << "MenuItem delegated\n";
    }

    MenuItem() : MenuItem("Unknown dish", 0.0, "General") {
        std::cout << "MenuItem default created\n";
    }

    ~MenuItem() {
        std::cout << "MenuItem destroyed: " << name << "\n";
    }

    void display() const {
        std::cout << "Dish: " << name << " | Price: " << price << " | Category: " << category << "\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const MenuItem& item) {
        os << "Dish: " << item.name << " | Price: " << item.price << " | Category: " << item.category;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, MenuItem& item) {
        is >> item.name >> item.price >> item.category;
        return is;
    }
};

