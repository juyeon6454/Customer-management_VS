#pragma once
#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include <iostream>

using namespace std;

class Product {
public:
	//Product(string = "", string = "", string = "");//디폴트 매개변수
	Product(int productID, string productName,string productPrice, string productStock);

	
	int getProductID() const;
	void setProductID(int&);
	string getProductName() const;
	void setProductName(string&);
	string getProductPrice() const;
	void setProductPrice(string&);
	string getProductStock() const;
	void setProductStock(string&);


private:
	int m_productID;
	string m_productName;
	string m_productPrice;
	string m_productStock;

};

#endif