#include "order.h"

#include <iostream>

using namespace std;

Order::Order(int orderID, string purchaseDate, int clientID, int productID, int productCount)
    : m_orderID(orderID), m_purchaseDate(purchaseDate), m_clientID(clientID),m_productID(productID), m_productCount(productCount)
{
}

int Order::getOrderID() const
{
    return m_orderID;
}

void Order::setOrderID(int& orderID)
{
    m_orderID = orderID;
}


string Order::getPurchaseDate() const
{
    return m_purchaseDate;
}

void Order::setPurchaseDate(string& purchaseDate)
{
    m_purchaseDate = purchaseDate;
}


int Order::getClientID() const
{
    return m_clientID;
}

void Order::setClientID(int& clientID)
{
    m_clientID = clientID;
}


int Order::getProductID() const
{
    return m_productID;
}

void Order::setProductID(int& productID)
{
    m_productID = productID;
}

int Order::getProductCount() const
{
    return m_productCount;
}

void Order::setProductCount(int& productCount)
{
    m_productCount = productCount;
}


