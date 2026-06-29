#include <iostream>
#include "store.h"
#include <limits>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    Store store;

    int choice = -1;
    while (true) {
        cout << "\n=== Музыкальный магазин (админ) ===\n";
        cout << "1. Просмотр каталога\n";
        cout << "2. Создать заказ (продажа)\n";
        cout << "3. Создать поставку\n";
        cout << "4. Изменить цену товара\n";
        cout << "5. Сформировать отчёт (файлы в data/)\n";
        cout << "0. Сохранить и выйти\n";
        cout << "Выбор: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
            case 1: store.showCatalog(); break;
            case 2: store.createSale(); break;
            case 3: store.createSupply(); break;
            case 4: store.changePrice(); break;
            case 5: store.generateReports(); break;
            case 0:
                store.saveAll();
                cout << "Сохранено. Выход.\n";
                return 0;
            default:
                cout << "Неверный вариант.\n";
        }
    }
    return 0;
}
