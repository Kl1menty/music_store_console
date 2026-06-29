#include "product.h"
#include <utility>


// Конструкторы
Product::Product(const std::string &name_, const std::string &category_, double price_, int quantity_)
    : name(name_), category(category_), price(price_), quantity(quantity_) { // Конструктор с параметрами
}

Product::Product(const Product &other) // Конструктор копирования
    : name(other.name), category(other.category), price(other.price), quantity(other.quantity) {
}

Product::Product(Product &&other) noexcept // Конструктор перемещения
    : name(std::move(other.name)), category(std::move(other.category)),
      price(other.price), quantity(other.quantity) {
    other.price = 0.0;
    other.quantity = 0;
}

Product::~Product() = default; // Деструктор

// Геттеры
std::string Product::getName() const { return name; } // Геттер
std::string Product::getCategory() const { return category; } // Геттер
double Product::getPrice() const { return price; } // Геттер
int Product::getQuantity() const { return quantity; } // Геттер

// Сеттеры / модификаторы
void Product::setPrice(double newPrice) { price = newPrice; } // Сеттер
void Product::addStock(int amount) { quantity += amount; } // Сеттер

void Product::reduceStock(int amount) { // Сеттер
    quantity -= amount;
    if (quantity < 0) quantity = 0;
}

// Виртуальный метод showInfo()
void Product::showInfo() const {
    std::cout << name << " [" << category << "] — " << price << " ₽, в наличии: " << quantity << std::endl;
}

// Перегрузка оператора вывода
std::ostream &operator<<(std::ostream &os, const Product &p) {
    os << p.name << " [" << p.category << "] — "
            << p.price << " ₽, в наличии: " << p.quantity;
    return os;
}

// ======= Реализация наследников =======

Guitar::Guitar(const std::string &name, double price, int quantity)
    : Product(name, "Гитары", price, quantity) {
}

void Guitar::showInfo() const {
    std::cout << "[Гитара] " << name << " — " << price
            << " ₽, в наличии: " << quantity << std::endl;
}

Keyboard::Keyboard(const std::string &name, double price, int quantity)
    : Product(name, "Клавишные", price, quantity) {
}

void Keyboard::showInfo() const {
    std::cout << "[Клавишные] " << name << " — " << price
            << " ₽, в наличии: " << quantity << std::endl;
}

Wind::Wind(const std::string &name, double price, int quantity)
    : Product(name, "Духовые", price, quantity) {
}

void Wind::showInfo() const {
    std::cout << "[Духовые] " << name << " — " << price
            << " ₽, в наличии: " << quantity << std::endl;
}

Percussion::Percussion(const std::string &name, double price, int quantity)
    : Product(name, "Ударные", price, quantity) {
}

void Percussion::showInfo() const {
    std::cout << "[Ударные] " << name << " — " << price
            << " ₽, в наличии: " << quantity << std::endl;
}

Accessory::Accessory(const std::string &name, double price, int quantity)
    : Product(name, "Аксессуары", price, quantity) {
}

void Accessory::showInfo() const {
    std::cout << "[Аксессуары] " << name << " — " << price
            << " ₽, в наличии: " << quantity << std::endl;
}
