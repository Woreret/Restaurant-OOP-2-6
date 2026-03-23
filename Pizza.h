#pragma once
#include "MenuItem.h"
#include <iostream>
#include <string>

class Pizza : public MenuItem {
public:
    Pizza(std::string name, double price) 
        : MenuItem(std::move(name), price, "Pizza") {}

    virtual void prepare() override {
        std::cout << "Preparing Pizza...\n";
    }
};
