#pragma once
#include <iostream>
#include <string>
#include <memory>

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

    std::string getName() const { return name; }
    virtual double getPrice() const { return price; }
    std::string getCategory() const { return category; }

    virtual void prepare() {
        std::cout << "Preparing " << name << "...\n";
    }

    virtual std::string serialize() const {
        return "MENU_ITEM;" + name + ";" + std::to_string(price) + ";" + category;
    }
    
    void display() const {
        std::cout << "Dish: " << name << " | Price: " << getPrice() << " | Category: " << category << "\n";
    }
};
