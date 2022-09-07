#ifndef __PRODUCTMANAGER_H__
#define __PRODUCTMANAGER_H__

#include <map>
#include <vector>
#include "product.h"

using namespace std;

class ProductManager {
public:
    ProductManager();
    ~ProductManager();

    void inputProduct(bool&, bool&);
    void searchProduct(bool&, bool&);
    void alterProduct(bool&, bool&);
    void eraseProduct(bool&, bool&);
    Product* search(int id);
    void displayInfo(int id);
    int makeId();

    vector<string> parseCSV(istream&, char);

    map<int, Product*> getProductList();
    map<int, Product*> setProductList();

private:
    map<int, Product*> ProductList;
};

#endif			// __PRODUCT_MANAGER_H__

