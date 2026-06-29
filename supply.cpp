#include "supply.h"
#include <sstream>
#include <iostream>
using namespace std;

Supply::Supply(const string& id_) : id(id_) {}
Supply::Supply(const Supply& other) : id(other.id), items(other.items) {}
Supply::Supply(Supply&& other) noexcept : id(std::move(other.id)), items(std::move(other.items)) {}

void Supply::addItem(const string& productName, int qty) { items.push_back({productName, qty}); }

void Supply::showSupply() const {
    cout << "ID поставки: " << id << endl;
    for (const auto& it : items) cout << " - " << it.first << " x" << it.second << endl;
}

string Supply::toText() const {
    ostringstream oss;
    oss << "ID:" << id << "\nITEMS:";
    for (size_t i = 0; i < items.size(); ++i) {
        if (i) oss << ",";
        oss << items[i].first << ";" << items[i].second;
    }
    oss << "\n----\n";
    return oss.str();
}
