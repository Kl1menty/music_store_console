#ifndef SALE_H
#define SALE_H

#include <vector>
#include <string>
#include "product.h"

class Sale {
public:
    std::string id;
    std::vector<std::pair<std::string, int>> items;                                 // Ассоциация
    double total;
    std::string paymentType;

    Sale(const std::string& id = "");
    Sale(const Sale& other); // Конструкторы копирования
    Sale(Sale&& other) noexcept; // Конструкторы перемещения

    void addItem(const std::string& productName, int qty, double unitPrice);
    void calculateTotal();
    void finalize(const std::string& payment);
    void showSale() const;

    std::string toText() const;
};

#endif
