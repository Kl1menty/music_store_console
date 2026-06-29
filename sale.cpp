#include "sale.h"
#include <iostream>
#include <sstream>
using namespace std;

Sale::Sale(const string& id_) : id(id_), total(0.0), paymentType("") {}
Sale::Sale(const Sale& other)
    : id(other.id), items(other.items), total(other.total), paymentType(other.paymentType) {}
Sale::Sale(Sale&& other) noexcept
    : id(std::move(other.id)), items(std::move(other.items)),
      total(other.total), paymentType(std::move(other.paymentType)) {
    other.total = 0.0;
}

void Sale::addItem(const string& productName, int qty, double /*unitPrice*/) {
    items.push_back({productName, qty});
}

void Sale::calculateTotal() {}

void Sale::finalize(const string& payment) { paymentType = payment; }

void Sale::showSale() const {
    cout << "ID продажи: " << id << endl;
    for (const auto& it : items) cout << " - " << it.first << " x" << it.second << endl;
    cout << "Итого: " << total << " ₽\n";
    cout << "Оплата: " << paymentType << endl;
}

string Sale::toText() const {
    ostringstream oss;
    oss << "ID:" << id << "\nITEMS:";
    for (size_t i = 0; i < items.size(); ++i) {
        if (i) oss << ",";
        oss << items[i].first << ";" << items[i].second;
    }
    oss << "\nTOTAL:" << total << "\nPAYMENT:" << paymentType << "\n----\n";
    return oss.str();
}
