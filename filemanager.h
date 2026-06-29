#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>
#include "product.h"
#include "sale.h"
#include "supply.h"

class FileManager {
public:
    static void ensureDataFolder();
    static void saveCatalog(const std::vector<Product*>& catalog, const std::string& path = "data/catalog.txt");
    static void loadCatalog(std::vector<Product*>& catalog, const std::string& path = "data/catalog.txt");

    static void saveMeta(int lastSaleId, int lastSupplyId, const std::string& path = "data/meta.txt");
    static void loadMeta(int& lastSaleId, int& lastSupplyId, const std::string& path = "data/meta.txt");

    static void appendSale(const Sale& sale, const std::string& path = "data/sales.txt");
    static void appendSupply(const Supply& supply, const std::string& path = "data/supplies.txt");
};

#endif
