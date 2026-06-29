#ifndef SUPPLY_H
#define SUPPLY_H

#include <vector>
#include <string>

class Supply {
public:
    std::string id;
    std::vector<std::pair<std::string, int>> items;                       // Ассоциация

    Supply(const std::string& id = "");
    Supply(const Supply& other);            // Конструкторы копирования
    Supply(Supply&& other) noexcept;        // Конструкторы перемещения

    void addItem(const std::string& productName, int qty);
    void showSupply() const;
    std::string toText() const;
};

#endif // SUPPLY_H
