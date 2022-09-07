#include "product.h"

#include <iostream>

using namespace std;

Product::Product(int productID,  string productName,string productPrice, string productStock)
	:m_productID(productID), m_productName(productName),m_productPrice(productPrice), m_productStock(productStock)
{

}

int Product::getProductID() const
{
	return m_productID;
}

void Product::setProductID(int& productID)
{
	m_productID = productID;
}


string Product::getProductName() const
{
	return m_productName;
}

void Product::setProductName(string& productName)
{
	m_productName=productName;
}

string Product::getProductPrice() const
{
	return m_productPrice;
}

void Product::setProductPrice(string& productPrice)
{
	m_productPrice = productPrice;
}

string Product::getProductStock() const
{
	return m_productStock;
}

void Product::setProductStock(string& productStock)
{
	m_productStock = productStock;
}








