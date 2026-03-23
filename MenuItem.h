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
        : name(std::move(n)), price(p), category(std::move(c)) {}

    MenuItem(std::string n, double p) 
        : MenuItem(std::move(n), p, "No category") {}

    MenuItem() : MenuItem("Unknown dish", 0.0, "General") {}

    virtual ~MenuItem() = default;

    virtual void prepare() = 0;

    void display() const {
        std::cout << "Dish: " << name << " | Price: " << price << " | Category: " << category << "\n";
    }


};

