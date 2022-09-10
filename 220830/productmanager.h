#ifndef __PRODUCTMANAGER_H__
#define __PRODUCTMANAGER_H__

#include <map>
#include <vector>
#include "product.h"

using namespace std;

class ProductManager {
public:
    ProductManager();                        //������ (���������)
    ~ProductManager();                      //�Ҹ��� (���������)

    void inputProduct(bool&, bool&);
    void searchProduct(bool&, bool&);
    void alterProduct(bool&, bool&);
    void eraseProduct(bool&, bool&);             //product ������ �Է�, ��ȸ, ����, �����ϴ� �Լ� ����
    Product* search(int id);                     //å�� �߽����� client�� ���� ��������
    void displayInfo(int id);
    int makeId();                               //id �ڵ��ο� �Լ� ����

    vector<string> parseCSV(istream&, char);    //���� ����½� vector���

    map<int, Product*> getProductList();
    map<int, Product*> setProductList();

private:
    map<int, Product*> ProductList;               //map�� ����ؼ� ProductList�� ������ �����ϰ� �о��
};

#endif			// __PRODUCT_MANAGER_H__

