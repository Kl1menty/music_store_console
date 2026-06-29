#include "store.h"
#include "filemanager.h"
#include <iostream>
#include <limits>
#include <sstream>

using namespace std;

Store::Store() {
    FileManager::loadCatalog(catalog);
    FileManager::loadMeta(lastSaleId, lastSupplyId);
}

Store::~Store() {
    for (auto p: catalog) delete p;
    catalog.clear();
}

string Store::makeSaleId(int id) const {
    ostringstream oss;
    oss.fill('0');
    oss.width(6);
    oss << id;
    return oss.str();
}

string Store::makeSupplyId(int id) const {
    ostringstream oss;
    oss.fill('0');
    oss.width(6);
    oss << id;
    return oss.str();
}

Product *Store::findProductByIndex(int index) {
    if (index < 1 || index > (int) catalog.size()) return nullptr;
    return catalog[index - 1];
}

void Store::showCatalog() const {
    cout << "\n=== Каталог ===\n";
    for (size_t i = 0; i < catalog.size(); ++i) {
        cout << (i + 1) << ". ";
        catalog[i]->showInfo();
    }
    cout << "===============\n";
}

void Store::createSale() {
    lastSaleId++;
    string sid = makeSaleId(lastSaleId);
    Sale sale(sid);
    double runningTotal = 0.0;

    while (true) {
        showCatalog();
        cout << "Введите номер товара (0 - завершить): ";
        int idx;
        if (!(cin >> idx)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (idx == 0) break;
        Product *p = findProductByIndex(idx);
        if (!p) {
            cout << "Неверный номер товара.\n";
            continue;
        }
        cout << "В наличии: " << p->getQuantity() << ". Введите количество для добавления в заказ: ";
        int qty;
        cin >> qty;
        if (qty <= 0) {
            cout << "Количество должно быть положительным.\n";
            continue;
        }
        if (qty > p->getQuantity()) {
            cout << "Недостаточно на складе. Текущее наличие: " << p->getQuantity() << "\n";
            continue;
        }
        // reduce stock immediately
        p->reduceStock(qty);
        sale.addItem(p->getName(), qty, p->getPrice());
        runningTotal += p->getPrice() * qty;
        cout << "Добавлено: " << p->getName() << " x" << qty << "\n";
    }

    if (sale.items.empty()) {
        cout << "Заказ пуст, отмена.\n";
        lastSaleId--; // rollback id because no sale created
        return;
    }

    cout << "Итоговая сумма: " << runningTotal << " ₽\n";
    int payChoice = 0;
    string paymentType;
    while (true) {
        cout << "Выберите тип оплаты: 1 - Наличные, 2 - Карта: ";
        cin >> payChoice;
        if (payChoice == 1) {
            paymentType = "Наличные";
            break;
        }
        if (payChoice == 2) {
            string card;
            while (true) {
                cout << "Введите номер карты (16 цифр): ";
                cin >> card;
                bool ok = (card.size() == 16);
                for (char c: card) if (!isdigit((unsigned char) c)) ok = false;
                if (ok) break;
                cout << "Неверный формат карты. Попробуйте ещё.\n";
            }
            paymentType = "Карта";
            break;
        }
        cout << "Неверный выбор.\n";
    }

    sale.total = runningTotal;
    sale.finalize(paymentType);
    sale.showSale();

    sales.push_back(sale);
    FileManager::appendSale(sale);
    FileManager::saveMeta(lastSaleId, lastSupplyId);
    FileManager::saveCatalog(catalog);
    cout << "Оплата прошла успешно! Продажа сохранена.\n";
}

void Store::createSupply() {
    lastSupplyId++;
    string sid = makeSupplyId(lastSupplyId);
    Supply supply(sid);
    while (true) {
        showCatalog();
        cout << "Введите номер товара для поставки (0 - завершить): ";
        int idx;
        if (!(cin >> idx)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (idx == 0) break;
        Product *p = findProductByIndex(idx);
        if (!p) {
            cout << "Неверный номер.\n";
            continue;
        }
        cout << "Введите количество (целое, <=100): ";
        int qty;
        cin >> qty;
        if (qty < 0 || qty > 100) {
            cout << "Недопустимое количество.\n";
            continue;
        }
        p->addStock(qty);
        supply.addItem(p->getName(), qty);
        cout << "Поставлено: " << p->getName() << " x" << qty << "\n";
    }

    if (supply.items.empty()) {
        cout << "Поставка пуста, отмена.\n";
        lastSupplyId--;
        return;
    }

    // После завершения выбора товаров:
    cout << "\n---------------------------------------\n";
    cout << "Поставка зарегистрирована успешно!\n";
    cout << "ID поставки: " << sid << "\n";
    cout << "Содержимое поставки:\n";
    for (const auto &it: supply.items) {
        cout << " - " << it.first << " x" << it.second << endl;
    }

    // Сохраняем в файлы:
    supplies.push_back(supply);
    FileManager::appendSupply(supply);
    FileManager::saveMeta(lastSaleId, lastSupplyId);
    FileManager::saveCatalog(catalog);
}

void Store::changePrice() {
    showCatalog();
    cout << "Введите номер товара для изменения цены: ";
    int idx;
    cin >> idx;
    Product *p = findProductByIndex(idx);
    if (!p) {
        cout << "Неверный номер.\n";
        return;
    }
    cout << "Текущая цена: " << p->getPrice() << " ₽. Введите новую цену: ";
    double np;
    cin >> np;
    if (np < 0) {
        cout << "Цена не может быть отрицательной.\n";
        return;
    }
    p->setPrice(np);
    FileManager::saveCatalog(catalog);
    cout << "Цена изменена.\n";
}

void Store::generateReports() const {
    cout << "\n=== Отчёты ===\n";
    cout << "История продаж: data/sales.txt\n";
    cout << "История поставок: data/supplies.txt\n";
    cout << "Текущий каталог/остатки: data/catalog.txt\n";
    cout << "Открыть эти файлы в папке data.\n";
}

void Store::saveAll() {                                               // зависимость
    FileManager::saveCatalog(catalog);
    FileManager::saveMeta(lastSaleId, lastSupplyId);
}

