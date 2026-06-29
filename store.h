#ifndef STORE_H
#define STORE_H

#include <vector>
#include <string>
#include "product.h"
#include "sale.h"
#include "supply.h"

class Store {
private:
    std::vector<Product*> catalog;        // агрегация
    std::vector<Sale> sales;
    std::vector<Supply> supplies;

    int lastSaleId;
    int lastSupplyId;

    std::string makeSaleId(int id) const;
    std::string makeSupplyId(int id) const;
    Product* findProductByIndex(int index);

public:
    Store();
    ~Store();

    void showCatalog() const;
    void createSale();
    void createSupply();
    void changePrice();
    void generateReports() const;
    void saveAll();
};

#endif
