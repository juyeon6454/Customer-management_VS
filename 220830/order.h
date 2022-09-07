#ifndef __ORDER_H__
#define __ORDER_H__

#include <iostream>

using namespace std;

class Order {
public:
    Order(int orderID,string purchaseDate, int clientID, int productID, int productCount);
    // ��������, �� id(�� ��ȭ��ȣ, �� �ּ�)��ǰid(��ǰ�̸�, ��ǰ����, ��ǰ���),
    int getOrderID() const;
    void setOrderID(int&);
    string getPurchaseDate() const;
    void setPurchaseDate(string&);
    int getClientID() const;
    void setClientID(int&);
    int getProductID() const;
    void setProductID(int&);
    int getProductCount() const;
    void setProductCount(int&);


private:
    int m_orderID;
    string m_purchaseDate;
    int m_clientID;
    int m_productID;
    int m_productCount;
};
#endif          // __ORDER_H