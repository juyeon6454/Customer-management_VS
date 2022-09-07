#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include<vector>
#include <ctime>
#include "order.h"
#include "ordermanager.h"
using namespace std;

int num_2;
int orderid = 0;
string purchasedate, client_name, clientphone_number,client_address, product_name;
int client_id, product_id, productcount;
map<int, Order*> OrderLIst;
//bool flag = true;
extern int getBnumber();

//++++++++++++++++++++++++++++++주문정보입력+++++++++++++++++++++++++++++++++++++++++
void OrderManager::inputOrder(bool& back, bool& flag, ClientManager clientmanager, ProductManager productmanager)   
{
	//clientlist.at(i)->getID().compare(shoppinglist.at(j)->getpkclient()) == 0
    while (1)
    {
        string purchasedate = currentDateTime();
        int p;//구매수량, 가격
        cout << "주문날짜 : " << purchasedate<<endl;
        cout << endl; cout << "고객 ID : "; client_id = getBnumber();
        cout << endl;  cout << "상품 ID : "; product_id = getBnumber(); cout << endl;//이름, 번호, 주소 입출력
        cout << "구매수량 : "; productcount = getBnumber(); cout << endl;
       // cout << "가격 : ";
       /* cout << "주문번호 : "; cin >> orderid;
        cout << endl;*/
        int orderid = makeId();   //id(key) 자동배정 (직접 입력하면 중복 문제)
        //string purchasedate = currentDateTime();
        OrderList.insert(make_pair (orderid, new Order(orderid,purchasedate, client_id, product_id,productcount)));//map의 key,value값
        cout << "주문번호는 [R" << orderid << "] 입니다." << endl;//배정된 id(key) 알림
        cout << "주문이 완료되었습니다." << endl << endl;
        cout << "======================================" << endl<<endl;
        cout << "1) 추가 입력 2) 처음으로 돌아가기 3) 종료" << endl;//한 번 등록후 추가 실행할 메뉴 선택
        cout << "실행할 메뉴를 선택해주세요 : "; p = getBnumber();
       //한 번 등록후 추가 실행할 메뉴 선택 변수
        cout << endl;

        if (p > 3 || p < 0)//a가 1만 추가입력으로 통과하도록 예외적인 상황을 만들어 다시 입력되도록 함
        {
            cout << "다시 입력해주세요." << endl;
            cout << "======================================" << endl;
            cout << "1) 추가 주문 2)메뉴화면으로 돌아가기 3)종료" << endl;
            cout << "실행할 메뉴를 선택해주세요 : ";  p = getBnumber();
            cout << endl;
            //continue;
        }

        else if (p == 2)//a가 3이 입력되었을때 첫 화면으로 돌아가기
        {
            system("cls");//지나간 화면 지우기
            back = false;//첫 화면으로
            break;
        }

        else if (p == 3)//a로 2가 입력되었을 때 프로그램이 아예 꺼지도록
        {
            system("cls");//지나간 화면 지우기
            cout << "=============================================" << endl;
            cout << "          프로그램이 종료되었습니다." << endl;
            cout << "=============================================" << endl;
            flag = false;
            break;
        }

    }
}

//++++++++++++++++++++++++++++++주문정보조회+++++++++++++++++++++++++++++++++++++++++
void OrderManager::searchOrder(bool& back, bool& flag, ClientManager clientmanager, ProductManager productmanager)
{
    //clientmanager.getClientList()[0]->getClientName();
    while (1)
    {
        int s, s_1, s_2, s_3,num_2;

gofirst:
        cout << "1) 전체 목록 조회 2) 검색 3)종료"<<endl;
        cout << "-> ";  num_2 = getBnumber();  cout << endl;
        switch (num_2)
        {
        case 1:
            for (map<int, Order*>::iterator itr = OrderList.begin(); itr != OrderList.end(); itr++)
            {
                Order* order = itr->second;
                int cid = order->getClientID();
                int pid = order->getProductID();
                Client* client = clientmanager.search(cid);
                Product* product = productmanager.search(pid);

                cout << "=======================================================================================================" << endl;
                cout << "주문번호 : P" << (*itr).second->getOrderID() << " l " << "주문자 :" << client->getClientName()
                <<  " l "  << "핸드폰번호 : " << client->getClientNumber() << " l " << "주소 : " << client->getClientAddress()
                 << " l " <<"상품명 : " << product->getProductName() << " l " <<"구매수량 : " << (*itr).second->getProductCount() << endl;
                cout << "=======================================================================================================" << endl << endl;
            }
            goto gofirst;
            break;

        case 2:
      
            cout << "원하는 방법을 선택하세요." << endl << endl;

            cout << "1) ID로 검색 2) 고객이름으로 검색 3) 핸드폰번호로 검색" << endl;
            cout << "-> : "; s = getBnumber();              //id,이름,번호를 선택하는 변수 (전체if)
  
            if (s == 1)//id로 검색
            {
                cout << "=============================================" << endl << endl;
                cout << "주문 ID를 입력하세요 : R"; //주문 번호를 받아서 조회
                orderid = getBnumber();                                                                             //id를 입력받음
                bool find = false;
                for (map<int, Order*>::iterator itr = OrderList.begin(); itr != OrderList.end(); itr++)//m전체를 돌아서
                {
                    Order* order = itr->second;
                    int cid = order->getClientID();
                    int pid = order->getProductID();
                    Client* client = clientmanager.search(cid);
                    Product* product = productmanager.search(pid);

                    if (orderid == order->getOrderID())//입력값이 있는 곳의 데이터를 출력
                    {
                        cout << endl;
                        cout << "주문번호 : R" << order->getOrderID() << endl;
                        clientmanager.displayInfo(cid);
                        productmanager.displayInfo(pid);
                        cout << "구매수량 : " << order->getProductCount() << endl<<endl;
                        find = true;
                    }
                }

                if (find == false)//for 안에서 입력되지 않은 정보를 알리기 위해 표현해주면 map 안에 들어있는 data만큼 돌기 때문에 문구가 여러번 출력됨
                                   //그렇기 때문에 find가 입력값이 value 안에 없을 때 find=true를 만나지 않고 그대로 find=false로 내려와 해당 문구가 출력되고, value 안에 입력값이 있을 때 
                                   //find true를 만나서 내려오기 때문에 find=false가 성립되지 않아 등록되지 않은 정보라는 문구가 출력되지 않는다
                {
                    cout << "=============================================" << endl;
                    cout << "      등록되지 않은 정보입니다." << endl;
                }

                cout << "======================================" << endl << endl;
                cout << "1) 추가 조회 2) 메뉴화면으로 돌아가기 3) 종료" << endl<<endl;
                cout << "-> "; s_1 = getBnumber();
              //한 번 조회 후 추가로 실행하는 메뉴 선택 변수 (if 안 if)


                if (s_1 > 3 || s_1 < 0)//b가 1만 추가조회로 통과하도록 예외적인 상황을 만들어 다시 입력되도록 함
                {
                    cout << "다시 입력해주세요." << endl;
                    cout << "1) 다시 조회하기 2) 메뉴화면으로 돌아가기 3) 종료" << endl;
                    cout << "-> "; s_1 = getBnumber();
                }

                else if (s_1 == 2)//b가 2 입력되었을때 첫 화면으로 돌아가기
                {
                    system("cls");//지나간 화면 지우기
                    back = false;//첫 화면으로
                    break;
                }

                else if (s_1 == 3)                                                  //s_1가 3이 입력되었을 때 프로그램이 정상 종료됨
                {
                    system("cls");                                                  //지나간 화면 지우기
                    cout << endl;
                    cout << "=============================================" << endl;
                    cout << "          프로그램이 종료되었습니다." << endl;
                    cout << "=============================================" << endl;
                    flag = false;                                                    //탈출하면서 main 앞부분에서 조건문이 성립됨으로써 return 0을 만나게 됨
                    break;
                }
                if (s_1 == 1)
                {
                    goto gofirst;
                }    
               //1이 입력되었을 때 break를 만나지 않고 함수의 맨 앞으로 돌아가기 위해 설정해줌 gofirst: 레이블을 만남
            }

            else if (s == 2)
            {
                cout << "=============================================" << endl;
                cout << "조회할 이름을 입력하세요 : "; cin >> client_name;
                bool find = false;
                for (map<int, Order*>::iterator itr = OrderList.begin(); itr != OrderList.end(); itr++)//m전체를 돌아서
                {
                    Order* order = itr->second;
                    int cid = order->getClientID();
                    int pid = order->getProductID();
                    Client* client = clientmanager.search(cid);
                    Product* product = productmanager.search(pid);

                    if (client_name == client->getClientName())//입력값이 있는 곳의 데이터를 출력
                    {
                        cout << "=============================================" << endl << endl;
                        cout << "주문번호 : R" << order->getOrderID() << endl;
                        clientmanager.displayInfo(cid);
                        productmanager.displayInfo(pid);
                        cout << "구매수량 : " << order->getProductCount() << endl;
                        cout << "=============================================" << endl;            //value에 있는 해당 값들을 출력 map에서 key는 First, value는 second 자리이기 때문
                        find = true;                                                                //false로 들어온 find를 true로 바꿔 if(find==false)를 통과하지 못하게 한다
                        // cout << "상품재고 : " << product->getProductStock() << endl;
                    }
                }

                if (find == false) //for 안에서 입력되지 않은 정보를 알리기 위해 표현해주면 map 안에 들어있는 data만큼 돌기 때문에 문구가 여러번 출력됨
                                 //그렇기 때문에 find가 입력값이 value 안에 없을 때 find=true를 만나지 않고 그대로 find=false로 내려와 해당 문구가 출력되고, value 안에 입력값이 있을 때 
                                 //find true를 만나서 내려오기 때문에 find=false가 성립되지 않아 등록되지 않은 정보라는 문구가 출력되지 않는다
                {
                    cout << "=============================================" << endl;
                    cout << "      등록되지 않은 정보입니다." << endl;
                }

                cout << "1) 추가 조회 2) 메뉴화면으로 돌아가기 3) 종료" << endl;
                cout << "-> "; s_2 = getBnumber();//한 번 조회 후 추가로 실행하는 메뉴 선택 변수 (if 안 if)

                if (s_2 > 3 || s_2 < 0)
                    //s_2가 1만 통과하도록 예외적인 상황을 만들어 다시 입력할 수 있는 부분 1은 if조건들에 충족하지 않아
                    //맨 뒤로 가서 goto gofirst;를 만나게 된다.
                {
                    cout << endl;
                    cout << "=============================================" << endl;
                    cout << "          다시 입력해주세요." << endl;
                    cout << "=============================================" << endl;
                    cout << "1) 다시 조회하기 2) 메뉴화면으로 돌아가기 3) 종료" << endl;
                    cout << "->"; s_2 = getBnumber();                                               //해당하는 메뉴가 없으니까 다시 선택하도록 함
                }

                else if (s_2 == 2)              //s_2가 2 입력되었을때 첫 화면으로 돌아가기
                {
                    system("cls");              //지나간 화면 지우기
                    back = false;               //첫 화면으로 
                    break;                      //탈출하면서 back=true를 만나게 됨
                }

                else if (s_2 == 3)
                    //s_2로 3이 입력되었을 때 프로그램이 정상 종료되도록(정상 종료가 되어야 소멸자가 기능해 파일 입출력이 가능)
                    //exit(1)로 구현했었지만 강제 종료가 됨으로써 소멸자가 기능하지 않아 파일 입출력이 되지 않았음
                {
                    system("cls");  //지나간 화면 지우기
                    cout << endl;
                    cout << "=============================================" << endl;
                    cout << "          프로그램이 종료되었습니다." << endl;
                    cout << "=============================================" << endl;
                    flag = false;   //탈출하면서 main 앞부분에서 조건문이 성립됨으로써 return 0을 만나게 됨
                    break;
                }
                if (s_2 == 1)         //if를 쓰지 않아도 조건에 걸리지 않아 내려와 실행됨                                     
                {
                    goto gofirst;    //등록되지 않은 정보를 입력했을 때 다시 입력할 수 있도록 앞 gofirst_2레이블로 돌아가서 원하는 방법을 선택하게 함      
                }     
                break;//1이 입력되었을 때(if문에 아무것도 걸리지 않고 내려옴)  break를 만나지 않고 함수의 맨 앞으로 돌아가기 위해 설정해줌 gofirst: 레이블을 만남
            }

            else if (s == 3)
            {
                cout << "전화번호를 입력하세요 * (-) 없이 입력 * : "; //-있게 저장되는거 없어지는걸로 통일?
                bool find = false;
                cin >> clientphone_number;
                for (map<int, Order*>::iterator itr = OrderList.begin(); itr != OrderList.end(); itr++)//m전체를 돌아서
                {
                    Order* order = itr->second;
                    int cid = order->getClientID();
                    int pid = order->getProductID();
                    Client* client = clientmanager.search(cid);
                    Product* product = productmanager.search(pid);

                    if (client_name == client->getClientName())//입력값이 있는 곳의 데이터를 출력
                    {
                        cout << "=============================================" << endl << endl;
                        cout << "주문번호 : R" << order->getOrderID() << endl;
                        clientmanager.displayInfo(cid);
                        productmanager.displayInfo(pid);
                        cout << "구매수량 : " << order->getProductCount() << endl<<endl;
                        cout << "=============================================" << endl;
                        find = true;
                    }
                }

                if (find == false)  //for 안에서 입력되지 않은 정보를 알리기 위해 표현해주면 map 안에 들어있는 data만큼 돌기 때문에 문구가 여러번 출력됨
                                  //그렇기 때문에 find가 입력값이 value 안에 없을 때 find=true를 만나지 않고 그대로 find=false로 내려와 해당 문구가 출력되고, value 안에 입력값이 있을 때 
                                  //find true를 만나서 내려오기 때문에 find=false가 성립되지 않아 등록되지 않은 정보라는 문구가 출력되지 않는다
                {
                    cout << "=============================================" << endl;
                    cout << "      등록되지 않은 정보입니다." << endl;

                }

                cout << "1) 추가 조회 2) 첫화면으로 돌아가기 3) 종료" << endl;
                cout<< "-> "; s_3 = getBnumber();          //한 번 조회 후 추가로 실행하는 메뉴 선택 변수 (if 안 if)
                if (s_3 > 3 || s_3 < 0)                                              //s_3이 1만 추가조회로 통과하도록 3보다 크고 0보다 작은 수가 입력될 때 값을 다시 입력하도록 함
                {
                    cout << endl;
                    cout << "==============================================" << endl;
                    cout << "   잘못 입력했습니다. 다시 입력해주세요." << endl;
                    cout << "==============================================" << endl;
                    cout << "1) 다시 조회하기 2) 메뉴화면으로 돌아가기 3) 종료" << endl;
                    s_3 = getBnumber();                                                           //재선택 변수
                }

                else if (s_3 == 2)   //s_3이 2 입력되었을때 첫 화면으로 돌아가기
                {
                    system("cls");
                    back = false;   //첫번째 메뉴화면으로 돌아가기 위해 입력  (back=true;)     
                    break;
                }

                else if (s_3 == 3)  //s_3로 3이 입력되었을 때 프로그램이 정상 종료되도록 함
                {
                    system("cls");  //지나간 화면 보이지 않게
                    cout << endl;
                    cout << "=============================================" << endl;
                    cout << "          프로그램이 종료되었습니다." << endl;
                    cout << "=============================================" << endl;
                    flag = false;
                    break;
                }
                if (s_3 == 1)       //if를 쓰지 않아도 조건에 걸리지 않아 내려와 실행됨                                     
                {
                    goto gofirst;   //등록되지 않은 정보를 입력했을 때 다시 입력할 수 있도록 앞 gofirst_2레이블로 돌아가서 원하는 방법을 선택하게 함      
                }                   //1이 입력되었을 때(if문에 아무것도 걸리지 않고 내려옴)  break를 만나지 않고 함수의 맨 앞으로 돌아가기 위해 설정해줌 gofirst: 레이블을 만남
            }//큰 if끝
            case 3:             //검색하기 전 메뉴에서 프로그램 종료하는 switch 세번째 정상 종료
            {
                system("cls");  //지나간 화면 지우기
                cout << endl;
                cout << "=============================================" << endl;
                cout << "          프로그램이 종료되었습니다." << endl;
                cout << "=============================================" << endl;
                flag = false;    //탈출하면서 main 앞부분에서 조건문이 성립됨으로써 return 0을 만나게 됨
                break;
            }
            if (s_2 == 1)
            {
                goto gofirst;   //등록되지 않은 정보를 입력했을 때 다시 입력할 수 있도록 앞 gofirst_2레이블로 돌아가서 원하는 방법을 선택하게 함      
            }                   //1이 입력되었을 때(if문에 아무것도 걸리지 않고 내려옴)  break를 만나지 않고 함수의 맨 앞으로 돌아가기 위해 설정해줌 gofirst: 레이블을 만남
           
        }
        break;
    }
}
    //++++++++++++++++++++++++++++++주문정보변경+++++++++++++++++++++++++++++++++++++++++



void OrderManager::alterOrder(bool& back, bool& flag, ClientManager clientmanager, ProductManager productmanager)
{

    int t, t_1, t_2, t_3,num_2;
   
    while(1)
    {
gofirst_2:
        cout << "원하는 방법을 선택하세요." << endl << endl;
        cout << "1) 주문번호로 검색 2) 고객 이름으로 검색 3) 핸드폰번호로 검색" << endl;
        cout << "-> ";  t = getBnumber();
      
        
        switch (t)
        {

        case 1:
        {
            cout << endl;
            cout << "주문번호를 입력하세요 : R";  orderid = getBnumber();
            cout << endl;

            bool find = false;
            for (map<int, Order*>::iterator itr = OrderList.begin(); itr != OrderList.end(); itr++)
            {
                Order* order = itr->second;
                int cid = (*itr).second->getClientID();
                Client* client = clientmanager.getClientList()[cid];
                int pid = (*itr).second->getProductID();
                Product* product = productmanager.getProductList()[pid];
                // Product* product = productmanager.search(pid);
                if (orderid == (*itr).second->getOrderID())
                {
                    find = true;                                                                            //false로 들어온 find를 true로 바꿔 if(find==false)를 통과하지 못하게 한다
                    cout << "=============================================" << endl;
                    cout << "ID : R" << (*itr).second->getOrderID() << endl;
                    cout << "이름 : " << client->getClientName() << endl;
                    cout << "핸드폰번호 : " << client->getClientNumber() << endl;
                    cout << "주소 : " << client->getClientAddress() << endl;
                    cout << "상품명 : " << product->getProductName() << endl;
                    cout << "구매수량 : " << (*itr).second->getProductCount() << endl;
                    cout << "======================================" << endl << endl;

                    cout << "변경할 정보를 선택하세요" << endl << endl;
                    cout << "1) 이름 2) 핸드폰번호 3) 주소 4) 상품명 5) 상품수량 6) 전체변경" << endl;
                    cout << "-> "; t_1 = getBnumber();

                    if (t_1 == 1)
                    {
                        cout << "=============================================" << endl;                    //이름만 변경
                        cout << "변경할 이름 : ";
                        cin >> client_name;
                        client->setClientName(client_name);
                        cout << "=============================================" << endl;
                        cout << endl;
                        cout << "********변경된 정보*******" << endl;

                        cout << "ID : R" << (*itr).second->getOrderID() << endl;
                        cout << "이름 : " << client->getClientName() << endl;
                        cout << "핸드폰번호 : " << client->getClientNumber() << endl;
                        cout << "주소 : " << client->getClientAddress() << endl;
                        cout << "상품명 : " << product->getProductName() << endl;
                        cout << "구매수량 : " << (*itr).second->getProductCount() << endl;
                        cout <<  "=============================================" << endl << endl;


                    }
                    else if (t_1 == 2)
                    {
                        cout << "=============================================" << endl;                //핸드폰번호만 변경
                        cout << "변경할 핸드폰번호 : ";
                        cin >> clientphone_number;
                        client->setClientNumber(clientphone_number);
                        cout << "=============================================" << endl;
                        cout << endl;

                    }
                    else if (t_1 == 3)
                    {
                        cout << "=============================================" << endl;
                        cout << "변경할 주소 : ";
                        cin >> client_address;
                        client->setClientAddress(client_address);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_1 == 4)
                    {
                        cout << "=============================================" << endl;
                        cout << "변경할 상품명 : ";
                        cin >> product_name;
                        product->setProductName(product_name);
                        cout << "=============================================" << endl;
                    }

                    else if (t_1 == 5)
                    {
                        cout << "=============================================" << endl;
                        cout << "변경할 구매수량 : ";
                        cin >> productcount;
                        order->setProductCount(productcount);
                        cout << "=============================================" << endl;
                    }

                    else if (t_1 == 6)
                    {
                        cout << "=============================================" << endl;
                        cout << "변경할 이름 : ";
                        cin >> client_name;
                        client->setClientName(client_name);
                        cout << "변경할 핸드폰번호 : ";
                        cin >> clientphone_number;
                        client->setClientNumber(clientphone_number);
                        cout << "변경할 주소 : ";
                        cin >> client_address;
                        client->setClientAddress(client_address);
                        cout << "변경할 상품명 : ";
                        cin >> product_name;
                        product->setProductName(product_name);
                        cout << "변경할 구매수량 : ";
                        cin >> productcount;
                        order->setProductCount(productcount);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }

                }

            }
            if (find == false)                                              //for 안에서 입력되지 않은 정보를 알리기 위해 표현해주면 map 안에 들어있는 data만큼 돌기 때문에 문구가 여러번 출력됨
                                                                           //그렇기 때문에 find가 입력값이 value 안에 없을 때 find=true를 만나지 않고 그대로 find=false로 내려와 해당 문구가 출력되고, value 안에 입력값이 있을 때 
                                                                           //find true를 만나서 내려오기 때문에 find=false가 성립되지 않아 등록되지 않은 정보라는 문구가 출력되지 않는다                                                            
            {
                cout << endl;
                cout << "=============================================" << endl;
                cout << "         등록되지 않은 정보입니다." << endl;
                cout << "=============================================" << endl << endl;
                goto gofirst_2;                                             //등록되지 않은 정보를 입력했을 때 다시 입력할 수 있도록 앞 gofirst_2레이블로 돌아가서 원하는 방법을 선택하게 함
            }
        }
        break;

        case 2:
        {
        cout << "고객 이름을 입력하세요 : ";  cin >> client_name;
        bool find = false;
        for (map<int, Order*>::iterator itr = OrderList.begin(); itr != OrderList.end(); itr++)
        {
            Order* order = itr->second;
            int cid = (*itr).second->getClientID();
            Client* client = clientmanager.getClientList()[cid];
            int pid = (*itr).second->getProductID();
            Product* product = productmanager.getProductList()[pid];

            if (client_name == client->getClientName())
            {
                find = true;                                                                            //false로 들어온 find를 true로 바꿔 if(find==false)를 통과하지 못하게 한다
                cout << "=============================================" << endl;
                cout << "ID : R" << (*itr).second->getOrderID() << endl;
                cout << "이름 : " << client->getClientName() << endl;
                cout << "핸드폰번호 : " << client->getClientNumber() << endl;
                cout << "주소 : " << client->getClientAddress() << endl;
                cout << "상품명 : " << product->getProductName() << endl;
                cout << "구매수량 : " << (*itr).second->getProductCount() << endl;
                cout << "======================================" << endl << endl;

                cout << "변경할 정보를 선택하세요" << endl << endl;
                cout << "1) 이름 2) 핸드폰번호 3) 주소 4) 상품명 5) 상품수량 6) 전체변경" << endl;
                cout << "-> "; t_2 = getBnumber();

                if (t_2 == 1)
                {
                    cout << "=============================================" << endl;                    //이름만 변경
                    cout << "변경할 이름 : ";
                    cin >> client_name;
                    client->setClientName(client_name);
                    cout << "=============================================" << endl;
                    cout << endl;
                    cout << "********변경된 정보*******" << endl;

                    cout << "ID : R" << (*itr).second->getOrderID() << endl;
                    cout << "이름 : " << client->getClientName() << endl;
                    cout << "핸드폰번호 : " << client->getClientNumber() << endl;
                    cout << "주소 : " << client->getClientAddress() << endl;
                    cout << "상품명 : " << product->getProductName() << endl;
                    cout << "구매수량 : " << (*itr).second->getProductCount() << endl;
                    cout << "=============================================" << endl << endl;


                }
                else if (t_2 == 2)
                {
                    cout << "=============================================" << endl;                //핸드폰번호만 변경
                    cout << "변경할 핸드폰번호 : ";
                    cin >> clientphone_number;
                    client->setClientNumber(clientphone_number);
                    cout << "=============================================" << endl;
                    cout << endl;

                }
                else if (t_2 == 3)
                {
                    cout << "=============================================" << endl;
                    cout << "변경할 주소 : ";
                    cin >> client_address;
                    client->setClientAddress(client_address);
                    cout << "=============================================" << endl;
                    cout << endl;
                }
                else if (t_2 == 4)
                {
                    cout << "=============================================" << endl;
                    cout << "변경할 상품명 : ";
                    cin >> product_name;
                    product->setProductName(product_name);
                    cout << "=============================================" << endl;
                }

                else if (t_2 == 5)
                {
                    cout << "=============================================" << endl;
                    cout << "변경할 구매수량 : ";
                    cin >> productcount;
                    order->setProductCount(productcount);
                    cout << "=============================================" << endl;
                }

                else if (t_2 == 6)
                {
                    cout << "=============================================" << endl;
                    cout << "변경할 이름 : ";
                    cin >> client_name;
                    client->setClientName(client_name);
                    cout << "변경할 핸드폰번호 : ";
                    cin >> clientphone_number;
                    client->setClientNumber(clientphone_number);
                    cout << "변경할 주소 : ";
                    cin >> client_address;
                    client->setClientAddress(client_address);
                    cout << "변경할 상품명 : ";
                    cin >> product_name;
                    product->setProductName(product_name);
                    cout << "변경할 구매수량 : ";
                    cin >> productcount;
                    order->setProductCount(productcount);
                    cout << "=============================================" << endl;
                    cout << endl;
                }

            }

        }
        if (find == false)                                              //for 안에서 입력되지 않은 정보를 알리기 위해 표현해주면 map 안에 들어있는 data만큼 돌기 때문에 문구가 여러번 출력됨
                                                                        //그렇기 때문에 find가 입력값이 value 안에 없을 때 find=true를 만나지 않고 그대로 find=false로 내려와 해당 문구가 출력되고, value 안에 입력값이 있을 때 
                                                                        //find true를 만나서 내려오기 때문에 find=false가 성립되지 않아 등록되지 않은 정보라는 문구가 출력되지 않는다                                                            
        {
            cout << endl;
            cout << "=============================================" << endl;
            cout << "         등록되지 않은 정보입니다." << endl;
            cout << "=============================================" << endl << endl;
            goto gofirst_2;                                             //등록되지 않은 정보를 입력했을 때 다시 입력할 수 있도록 앞 gofirst_2레이블로 돌아가서 원하는 방법을 선택하게 함
        }
        }
        break;

        case 3:
        {
            cout << "=============================================" << endl;
            cout << "고객 전화번호를 입력하세요 : ";  cin >> clientphone_number;
            bool find = false;
            for (map<int, Order*>::iterator itr = OrderList.begin(); itr != OrderList.end(); itr++)
            {
                Order* order = itr->second;
                int cid = (*itr).second->getClientID();
                Client* client = clientmanager.getClientList()[cid];
                int pid = (*itr).second->getProductID();
                Product* product = productmanager.getProductList()[pid];

                if (clientphone_number == client->getClientNumber())
                   
                {
                    find = true;                                                                            //false로 들어온 find를 true로 바꿔 if(find==false)를 통과하지 못하게 한다
                    cout << "=============================================" << endl;
                    cout << "ID : R" << (*itr).second->getOrderID() << endl;
                    cout << "이름 : " << client->getClientName() << endl;
                    cout << "핸드폰번호 : " << client->getClientNumber() << endl;
                    cout << "주소 : " << client->getClientAddress() << endl;
                    cout << "상품명 : " << product->getProductName() << endl;
                    cout << "구매수량 : " << (*itr).second->getProductCount() << endl;
                    cout << "======================================" << endl << endl;

                    cout << "변경할 정보를 선택하세요" << endl << endl;
                    cout << "1) 이름 2) 핸드폰번호 3) 주소 4) 상품명 5) 상품수량 6) 전체변경" << endl;
                    cout << "-> "; t_3 = getBnumber();

                    if (t_3 == 1)
                    {
                        cout << "=============================================" << endl;                    //이름만 변경
                        cout << "변경할 이름 : ";
                        cin >> client_name;
                        client->setClientName(client_name);
                        cout << "=============================================" << endl;
                        cout << endl;
                        cout << "********변경된 정보*******" << endl;

                        cout << "ID : R" << (*itr).second->getOrderID() << endl;
                        cout << "이름 : " << client->getClientName() << endl;
                        cout << "핸드폰번호 : " << client->getClientNumber() << endl;
                        cout << "주소 : " << client->getClientAddress() << endl;
                        cout << "상품명 : " << product->getProductName() << endl;
                        cout << "구매수량 : " << (*itr).second->getProductCount() << endl;
                        cout << "=============================================" << endl << endl;


                    }
                    else if (t_3 == 2)
                    {
                        cout << "=============================================" << endl;                //핸드폰번호만 변경
                        cout << "변경할 핸드폰번호 : ";
                        cin >> clientphone_number;
                        client->setClientNumber(clientphone_number);
                        cout << "=============================================" << endl;
                        cout << endl;

                    }
                    else if (t_3 == 3)
                    {
                        cout << "=============================================" << endl;
                        cout << "변경할 주소 : ";
                        cin >> client_address;
                        client->setClientAddress(client_address);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_3 == 4)
                    {
                        cout << "=============================================" << endl;
                        cout << "변경할 상품명 : ";
                        cin >> product_name;
                        product->setProductName(product_name);
                        cout << "=============================================" << endl;
                    }

                    else if (t_3 == 5)
                    {
                        cout << "=============================================" << endl;
                        cout << "변경할 구매수량 : ";
                        cin >> productcount;
                        order->setProductCount(productcount);
                        cout << "=============================================" << endl;
                    }

                    else if (t_3 == 6)
                    {
                        cout << "=============================================" << endl;
                        cout << "변경할 이름 : ";
                        cin >> client_name;
                        client->setClientName(client_name);
                        cout << "변경할 핸드폰번호 : ";
                        cin >> clientphone_number;
                        client->setClientNumber(clientphone_number);
                        cout << "변경할 주소 : ";
                        cin >> client_address;
                        client->setClientAddress(client_address);
                        cout << "변경할 상품명 : ";
                        cin >> product_name;
                        product->setProductName(product_name);
                        cout << "변경할 구매수량 : ";
                        cin >> productcount;
                        order->setProductCount(productcount);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }

                }

            }
            if (find == false)                                              //for 안에서 입력되지 않은 정보를 알리기 위해 표현해주면 map 안에 들어있는 data만큼 돌기 때문에 문구가 여러번 출력됨
                                                                            //그렇기 때문에 find가 입력값이 value 안에 없을 때 find=true를 만나지 않고 그대로 find=false로 내려와 해당 문구가 출력되고, value 안에 입력값이 있을 때 
                                                                            //find true를 만나서 내려오기 때문에 find=false가 성립되지 않아 등록되지 않은 정보라는 문구가 출력되지 않는다                                                            
            {
                cout << endl;
                cout << "=============================================" << endl;
                cout << "         등록되지 않은 정보입니다." << endl;
                cout << "=============================================" << endl << endl;
                goto gofirst_2;                                             //등록되지 않은 정보를 입력했을 때 다시 입력할 수 있도록 앞 gofirst_2레이블로 돌아가서 원하는 방법을 선택하게 함
            }
        }//case 3 끝
        break;
        }//switch끝
     

        cout << "=============================================" << endl;
        cout << "           변경이 완료되었습니다." << endl;
        cout << "=============================================" << endl << endl;
        cout << "1) 추가 입력 2) 메뉴화면으로 돌아가기 3) 종료" << endl;
        cout << "->"; t = getBnumber();

        if (t > 3 || t < 0)                                                         //t가 1만 조건문을 통과하도록 선택 외의 예외 상황을 지정
        {
            cout << "=============================================" << endl;
            cout << "            다시 입력해주세요." << endl;
            cout << "=============================================" << endl << endl;
            cout << "1) 추가 입력 2) 메뉴화면으로 돌아가기 3) 종료" << endl;
            t = getBnumber();;
        }

        else if (t == 2)                                                            //t가 2 입력되었을때 첫 메뉴 화면으로 돌아가기 위한 기능
        {
            system("cls");                                                          //지나간 화면 사라지게
            back = false;                                                           //main의 처음 back = true를 만나 첫 메뉴 화면 출력
            break;
        }

        else if (t == 3)                                                            //t가 3 입력되었을 때 프로그램 정상 종료
        {
            system("cls");                                                          //지나간 화면 지우기                              
            cout << endl;
            cout << "=============================================" << endl;
            cout << "          프로그램이 종료되었습니다." << endl;
            cout << "=============================================" << endl;
            flag = false;                                                           //main의 flag = false 조건을 만나 reuturn 0; 으로 반환되어 정상 종료
            break;
        }
        if (t == 1)                           //if를 쓰지 않아도 조건에 걸리지 않아 내려와 실행됨                                     
        {
            goto gofirst_2;                  //등록되지 않은 정보를 입력했을 때 다시 입력할 수 있도록 앞 gofirst_2레이블로 돌아가서 원하는 방법을 선택하게 함      
        }
        break;
    }//while끝
}


//++++++++++++++++++++++++++++++주문정보삭제+++++++++++++++++++++++++++++++++++++++++

void OrderManager::eraseOrder(bool& back, bool& flag, ClientManager clientmanager, ProductManager productmanager)
{
 gofirst_3:
    int e, e_1;
    bool repeat(true);
    while (repeat)
    {
        if (OrderList.size() == 0)
        {
            cout << endl;
            cout << "=============================================" << endl;
            cout << "      List에 정보가 존재하지 않습니다" << endl;
            cout << "=============================================" << endl << endl;
            cout << "1) 메뉴화면으로 돌아가기 2) 종료" << endl; e = getBnumber();

            if (e == 1)
            {
                system("cls");
                back = false;//첫 화면으로
                break;
            }

            if (e == 2)
            {
                system("cls");                                                  //지나간 화면 사라지게
                cout << "=============================================" << endl;
                cout << "         프로그램이 종료되었습니다." << endl;
                cout << "=============================================" << endl << endl;
                flag = false;                                                    //main의 flag = false 조건을 만나 reuturn 0; 으로 반환되어 정상 종료
                break;
            }
            break;
        }


        else if (OrderList.size() != 0)
        {
            cout << "삭제할 주문번호를 입력하세요 : R";  cin >> orderid;
            bool find = false;
            for (map<int, Order*>::iterator itr = OrderList.begin(); itr != OrderList.end(); itr++)
            {
                if (orderid == (*itr).second->getOrderID())
                {
                    // ClientList.erase(clientid = ClientList[i]->getClientID());
                    OrderList.erase(orderid);
                    cout << "=============================================" << endl;
                    cout << "                삭제되었습니다." << endl;
                    cout << "=============================================" << endl << endl;
                    cout << "1) 추가 주문 취소하기 2) 메뉴화면으로 돌아가기 3) 종료" << endl;
                    e_1 = getBnumber();

                    if (e_1 == 2)
                    {
                        system("cls");
                        back = false;//첫 화면으로
                        repeat = false;
                        break;
                    }

                    else if (e_1 > 3 || e_1 < 0)//b가 1만 추가조회로 통과하도록 예외적인 상황을 만들어 다시 입력되도록 함
                    {
                        cout << endl;
                        cout << "=============================================" << endl;
                        cout << "            다시 입력해주세요." << endl;
                        cout << "=============================================" << endl;
                        cout << "1) 추가 주문 취소하기 2) 메뉴화면으로 돌아가기 3) 종료" << endl;
                        cout << "->"; e_1 = getBnumber();
                    }

                    else if (e_1 == 3)
                    {
                        system("cls");//지나간 화면 지우기
                        cout << endl;
                        cout << "==========================" << endl;
                        cout << "프로그램이 종료되었습니다." << endl;
                        cout << "==========================" << endl;
                        flag = false;
                        break;
                    }
                    break;

                }//if

            }//for 끝
            if (find == false)                                          //find가 위 조건문을 통과하지 않음으로써 true가 되지 않았기 때문에 false로 성립되어 출력
            {
                cout << endl;
                cout << "=============================================" << endl;
                cout << "         등록되지 않은 정보입니다." << endl;
                cout << "=============================================" << endl << endl;
                goto gofirst_3;                                          //등록되지 않은 정보를 입력했을 때 다시 입력할 수 있도록 앞 gofirst_3 레이블로 돌아가서 원하는 방법을 선택하게 함
            }

        }
        break;
    }//while끝

}


int OrderManager::makeId()
{
    auto key = OrderList.end();
    if (OrderList.size() == 0) {
        return 0;
    }
    else {
        int id = (--key)->first;
        return ++id;
    }

    return 0;
}


//========================파일입출력===========================
//
OrderManager::OrderManager()
{ 
    ifstream file; 
    file.open("orderlist.txt"); 
    if (!file.fail()) { 
        while (!file.eof()) { 
            vector<string> row = parseCSV(file, ',');
            if (row.size()) {
                int orderid = stoi(row[0]);
                int ordercid = stoi(row[2]);
                int orderpid = stoi(row[3]);
                int orderpcid = stoi(row[4]);

                Order* o = new Order(orderid, row[1], ordercid, orderpid, orderpcid);
                OrderList.insert({ orderid, o });
            } 
        } 
    }
    file.close();

}

OrderManager::~OrderManager()
{
    ofstream file;
    file.open("orderlist.txt");
    if (!file.fail()) {
        for (const auto& v : OrderList) {
            Order* o = v.second;
            file << o->getOrderID() << ", " << o->getPurchaseDate() << ", ";
            file << o->getClientID() << ", ";
            file << o->getProductID() << ", ";
            file << o->getProductCount() << endl;

        }
    }
    file.close();
}

vector<string> OrderManager::parseCSV(istream& file, char delimiter)
{
    stringstream ss;
    vector<string> row;
    string t = " \n\r\t";

    while (!file.eof()) {
        char c = file.get();
        if (c == delimiter || c == '\r' || c == '\n') {
            if (file.peek() == '\n') file.get();
            string s = ss.str();
            s.erase(0, s.find_first_not_of(t));
            s.erase(s.find_last_not_of(t) + 1);
            row.push_back(s);
            ss.str("");
            if (c != delimiter) break;
        }
        else {
            ss << c;
        }
    }
    return row;
}


string OrderManager::currentDateTime()      //날짜 자동입력
{
    time_t now = time(0); //현재 시간을 time_t 타입으로 저장
    struct tm tstruct;
    char buf[40];
    localtime_s(&tstruct, &now);
    strftime(buf, sizeof(buf), "%Y%m%d", &tstruct); //YYMMDD 형태의 스트링
    string str = buf;

    return str.substr(2, str.size() - 1);
}

void OrderManager::displayInfo(int id)
{
    auto it = OrderList.find(id);
    if (it != OrderList.end()) {
        Order* order = it->second;
        cout << "주문수량 : " << order->getProductCount() << endl;

    }
}

Order* OrderManager::search(int id)
{
    auto it = OrderList.find(id);
    return (it != OrderList.end()) ? OrderList[id] : nullptr;
}


void OrderManager::organizeOrderList(ClientManager clientManager, ProductManager productManager)
{
    vector<int> veDeleteIDList;
    for (auto mapTmp : OrderList)
    {
        int iOrderId = mapTmp.second->getOrderID();
        int iClientId = mapTmp.second->getClientID();
        int iProductId = mapTmp.second->getProductID();
        if (clientManager.search(iClientId) == NULL || productManager.search(iProductId) == NULL) // 고객ID 또는 제품ID와 일치하는게 없다면...
            veDeleteIDList.push_back(iOrderId);
    }
    for (auto veTmp : veDeleteIDList)
    {
        OrderList.erase(veTmp);
    }
}
