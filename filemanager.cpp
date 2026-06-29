#include "filemanager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

void FileManager::ensureDataFolder() {
    if (!fs::exists("data")) {
        fs::create_directory("data");
    }
}

void FileManager::saveCatalog(const vector<Product*>& catalog, const string& path) {
    ensureDataFolder();
    ofstream f(path, ios::trunc);
    if (!f.is_open()) {
        cerr << "Не удалось открыть файл для записи: " << path << endl;
        return;
    }
    // format: name;category;price;quantity\n
    for (const auto& p : catalog) {
        f << p->getName() << ";" << p->getCategory() << ";" << p->getPrice() << ";" << p->getQuantity() << "\n";
    }
    f.close();
}

void FileManager::loadCatalog(vector<Product*>& catalog, const string& path) {
    ensureDataFolder();
    ifstream f(path);
    if (!f.is_open()) {
        // create default catalog if not exists
        catalog.clear();
        // default items (quantity = 10)
        catalog.push_back(new Product("Классическая гитара", "Гитары", 12000.0, 10));
        catalog.push_back(new Product("Акустическая гитара", "Гитары", 15000.0, 10));
        catalog.push_back(new Product("Бас-гитара", "Гитары", 18000.0, 10));
        catalog.push_back(new Product("Электрогитара", "Гитары", 20000.0, 10));

        catalog.push_back(new Product("Фортепиано", "Клавишные", 150000.0, 10));
        catalog.push_back(new Product("Синтезатор", "Клавишные", 35000.0, 10));
        catalog.push_back(new Product("Аккордеон", "Клавишные", 45000.0, 10));

        catalog.push_back(new Product("Флейта", "Духовые", 12000.0, 10));
        catalog.push_back(new Product("Кларнет", "Духовые", 18000.0, 10));
        catalog.push_back(new Product("Саксофон", "Духовые", 55000.0, 10));

        catalog.push_back(new Product("Барабанная установка", "Ударные", 60000.0, 10));
        catalog.push_back(new Product("Малый барабан", "Ударные", 10000.0, 10));
        catalog.push_back(new Product("Бонго", "Ударные", 8000.0, 10));

        catalog.push_back(new Product("Струны для гитары", "Аксессуары", 700.0, 10));
        catalog.push_back(new Product("Медиаторы", "Аксессуары", 100.0, 10));
        catalog.push_back(new Product("Чехлы", "Аксессуары", 1800.0, 10));
        catalog.push_back(new Product("Кабели и переходники", "Аксессуары", 500.0, 10));
        catalog.push_back(new Product("Тюнеры", "Аксессуары", 1000.0, 10));

        // save
        saveCatalog(catalog, path);
        return;
    }
    catalog.clear();
    string line;
    while (getline(f, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string name, category, priceStr, qtyStr;
        if (!getline(ss, name, ';')) continue;
        if (!getline(ss, category, ';')) continue;
        if (!getline(ss, priceStr, ';')) continue;
        if (!getline(ss, qtyStr)) continue;
        double price = stod(priceStr);
        int qty = stoi(qtyStr);
        catalog.push_back(new Product(name, category, price, qty));
    }
    f.close();
}

void FileManager::saveMeta(int lastSaleId, int lastSupplyId, const string& path) {
    ensureDataFolder();
    ofstream f(path, ios::trunc);
    if (!f.is_open()) return;
    f << "last_sale_id=" << lastSaleId << "\n";
    f << "last_supply_id=" << lastSupplyId << "\n";
    f.close();
}

void FileManager::loadMeta(int& lastSaleId, int& lastSupplyId, const string& path) {
    ensureDataFolder();
    ifstream f(path);
    if (!f.is_open()) {
        lastSaleId = 0;
        lastSupplyId = 0;
        saveMeta(lastSaleId, lastSupplyId, path);
        return;
    }
    lastSaleId = 0;
    lastSupplyId = 0;
    string line;
    while (getline(f, line)) {
        if (line.find("last_sale_id=") == 0) {
            lastSaleId = stoi(line.substr(13));
        } else if (line.find("last_supply_id=") == 0) {
            lastSupplyId = stoi(line.substr(15));
        }
    }
    f.close();
}

void FileManager::appendSale(const Sale& sale, const string& path) {
    ensureDataFolder();
    ofstream f(path, ios::app);
    if (!f.is_open()) return;
    f << sale.toText();
    f.close();
}

void FileManager::appendSupply(const Supply& supply, const string& path) {
    ensureDataFolder();
    ofstream f(path, ios::app);
    if (!f.is_open()) return;
    f << supply.toText();
    f.close();
}
