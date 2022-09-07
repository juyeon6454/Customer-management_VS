#pragma once
#ifndef __ORDERMANAGER_H__
#define __ORDERMANAGER_H__

#include <map>
#include "order.h"
#include "clientmanager.h"
#include "productmanager.h"
using namespace std;

class OrderManager {
public:

    OrderManager();
    ~OrderManager();

    void inputOrder(bool&, bool&, ClientManager, ProductManager);
    void searchOrder(bool&, bool& ,ClientManager, ProductManager);
    void alterOrder(bool&, bool&, ClientManager, ProductManager);
    void eraseOrder(bool&, bool& ,ClientManager, ProductManager);
    void organizeOrderList(ClientManager, ProductManager);
    string currentDateTime();
    void displayInfo(int);
    Order* search(int);
    int makeId();
    vector<string> parseCSV(istream&, char);


private:
    map<int, Order*> OrderList;
};

#endif			// __ORDER_MANAGER_H__
