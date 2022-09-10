#ifndef __PRODUCTMANAGER_H__
#define __PRODUCTMANAGER_H__

#include <map>
#include <vector>
#include "product.h"

using namespace std;

class ProductManager {
public:
    ProductManager();                        //생성자 (파일입출력)
    ~ProductManager();                      //소멸자 (파일입출력)

    void inputProduct(bool&, bool&);
    void searchProduct(bool&, bool&);
    void alterProduct(bool&, bool&);
    void eraseProduct(bool&, bool&);             //product 정보를 입력, 조회, 삭제, 변경하는 함수 선언
    Product* search(int id);                     //책임 중심으로 client의 정보 가져오기
    void displayInfo(int id);
    int makeId();                               //id 자동부여 함수 선언

    vector<string> parseCSV(istream&, char);    //파일 입출력시 vector사용

    map<int, Product*> getProductList();
    map<int, Product*> setProductList();

private:
    map<int, Product*> ProductList;               //map을 사용해서 ProductList에 정보를 저장하고 읽어옴
};

#endif			// __PRODUCT_MANAGER_H__

