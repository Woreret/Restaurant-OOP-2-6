#pragma once

class Discount {
private:
    double percentage;

public:
    Discount(double percent = 0.0) : percentage(percent) {}
    
    double getPercentage() const {
        return percentage;
    }

    double applyDiscount(double amount) const {
        return amount - (amount * (percentage / 100.0));
    }
};
