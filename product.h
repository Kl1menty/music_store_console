#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>

class Product {
protected:
    std::string name;
    std::string category;
    double price;
    int quantity;

public:
    // Конструкторы
    Product(const std::string &name = "", const std::string &category = "", double price = 0.0, int quantity = 0);

    Product(const Product &other); // копирующий конструктор
    Product(Product &&other) noexcept; // конструктор перемещения

    virtual ~Product(); // виртуальный деструктор

    // Геттеры
    std::string getName() const;

    std::string getCategory() const;

    double getPrice() const;

    int getQuantity() const;

    // Сеттеры / модификаторы
    void setPrice(double newPrice);

    void addStock(int amount);

    void reduceStock(int amount);

    // Виртуальная функция для вывода информации
    virtual void showInfo() const;

    // Перегрузка оператора вывода
    friend std::ostream &operator<<(std::ostream &os, const Product &product);
};

// ======= Наследники =======

class Guitar : public Product { // Одиночное наследование
public:
    Guitar(const std::string &name = "", double price = 0.0, int quantity = 0);

    void showInfo() const override;
};

class Keyboard : public Product { // Одиночное наследование
public:
    Keyboard(const std::string &name = "", double price = 0.0, int quantity = 0);

    void showInfo() const override;
};

class Wind : public Product { // Одиночное наследование
public:
    Wind(const std::string &name = "", double price = 0.0, int quantity = 0);

    void showInfo() const override;
};

class Percussion : public Product { // Одиночное наследование
public:
    Percussion(const std::string &name = "", double price = 0.0, int quantity = 0);

    void showInfo() const override;
};

class Accessory : public Product { // Одиночное наследование
public:
    Accessory(const std::string &name = "", double price = 0.0, int quantity = 0);

    void showInfo() const override;
};

#endif // PRODUCT_H
