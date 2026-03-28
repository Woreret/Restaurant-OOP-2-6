#pragma once
#include "MenuItem.h"
#include <iostream>
#include <string>

class DiscountedItem : public MenuItem {
private:
    double discountPercentage;

public:
    DiscountedItem(std::string n, double p, std::string c, double discountPct)
        : MenuItem(std::move(n), p, std::move(c)), discountPercentage(discountPct) {}

    virtual double getPrice() const override {
        double originalPrice = MenuItem::getPrice();
        return originalPrice - (originalPrice * (discountPercentage / 100.0));
    }

    virtual void prepare() override {
        std::cout << "Preparing discounted item " << getName() << " (Discount: " << discountPercentage << "%)...\n";
    }

    double getDiscountPercentage() const {
        return discountPercentage;
    }

    virtual std::string serialize() const override {
        return "DISCOUNTED_ITEM;" + getName() + ";" + std::to_string(MenuItem::getPrice()) + ";" + getCategory() + ";" + std::to_string(discountPercentage);
    }
};
