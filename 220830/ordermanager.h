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

    OrderManager();                        //생성자 (파일입출력)
    ~OrderManager();                      //소멸자 (파일입출력)

    void inputOrder(bool&, bool&, ClientManager, ProductManager);
    void searchOrder(bool&, bool& ,ClientManager, ProductManager);
    void alterOrder(bool&, bool&, ClientManager, ProductManager);
    void eraseOrder(bool&, bool& ,ClientManager, ProductManager);             //order 정보를 입력, 조회, 삭제, 변경하는 함수 선언
    void organizeOrderList(ClientManager, ProductManager);                     //주문 후 고객정보가 사라졌을 때
    string currentDateTime();                                                  //현재 날짜를 자동입력하는 함수
    void displayInfo(int);
    Order* search(int); 
    int makeId();                                                             //id 자동부여 함수 선언
    vector<string> parseCSV(istream&, char);


private:
    map<int, Order*> OrderList;               //map을 사용해서 ClientList에 정보를 저장하고 읽어옴
};

#endif			// __ORDER_MANAGER_H__
