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

    OrderManager();                        //������ (���������)
    ~OrderManager();                      //�Ҹ��� (���������)

    void inputOrder(bool&, bool&, ClientManager, ProductManager);
    void searchOrder(bool&, bool& ,ClientManager, ProductManager);
    void alterOrder(bool&, bool&, ClientManager, ProductManager);
    void eraseOrder(bool&, bool& ,ClientManager, ProductManager);             //order ������ �Է�, ��ȸ, ����, �����ϴ� �Լ� ����
    void organizeOrderList(ClientManager, ProductManager);                     //�ֹ� �� �������� ������� ��
    string currentDateTime();                                                  //���� ��¥�� �ڵ��Է��ϴ� �Լ�
    void displayInfo(int);
    Order* search(int); 
    int makeId();                                                             //id �ڵ��ο� �Լ� ����
    vector<string> parseCSV(istream&, char);


private:
    map<int, Order*> OrderList;               //map�� ����ؼ� ClientList�� ������ �����ϰ� �о��
};

#endif			// __ORDER_MANAGER_H__
