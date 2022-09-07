#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include "product.h"
#include "productmanager.h"


int num_1;
int productid = 0;
string productname, productprice, productstock;
map<int, Product*> ProductList;
extern int getBnumber();
//소멸자 작성해주기

//++++++++++++++++++++++++++++++상품정보입력+++++++++++++++++++++++++++++++++++++++++
void ProductManager::inputProduct(bool& back, bool& flag)       //고객정보입력함수
{
    while (1)
    {
        int p;                                           //한 번 등록후 추가 실행할 메뉴 선택 변수
        cout << "상품명 : "; cin >> productname; 
        cout << endl;
        cout << "상품가격 : "; cin >> productprice; 
        cout << endl;
        cout << "재고수량 : "; cin >> productstock;
        cout << endl;                                   //상품명, 상품가격, 재고수량 입출력

        int productid = makeId();                       //id(key) 자동배정 (직접 입력하면 중복 문제)
        ProductList.insert(make_pair(productid, new Product(productid, productname, productprice, productstock)));  //map의 key,value값
        cout << productname << " 의 ID는 [P" << productid << "] 입니다." << endl<<endl;                             //배정된 id(key) 알림
        cout << "등록이 완료되었습니다." << endl << endl;
        cout << "======================================" << endl;
        cout << "1) 추가 입력 2) 처음으로 돌아가기 3) 종료" << endl;  //한 번 등록후 추가 실행할 메뉴 선택
        cout << "실행할 메뉴를 선택해주세요 : "; p = getBnumber();     //한 번 등록후 추가 실행할 메뉴 선택 변수
        cout << endl;
        cout << endl;

        if (p > 3 || p < 0)                  //p가 1,2,3 이외의 값을 받았을 때 다시 입력
        {
            cout << "다시 입력해주세요." << endl;
            cout << "======================================" << endl << endl;
            cout << "1) 추가 입력 2) 메뉴화면으로 돌아가기 3) 종료" << endl;
            cout << "실행할 메뉴를 선택해주세요 : "; p = getBnumber();
            cout << endl;
        }

        else if (p == 2)    //p가 2 입력되었을때 첫 화면으로 돌아가기
        {
            system("cls");  //지나간 화면 지우기
            back = false;   //첫 화면으로
            break;
        }

        else if (p == 3)    //p로 3이 입력되었을 때 프로그램 정상 종료
        {
            system("cls"); //지나간 화면 지우기
            cout << "=============================================" << endl;
            cout << "          프로그램이 종료되었습니다." << endl;
            cout << "=============================================" << endl;
            flag = false;    //main 앞에 조건문을 추가함으로써 return 0을 만나게 됨
            break;
        }
    }
}
//++++++++++++++++++++++++++++++상품정보조회+++++++++++++++++++++++++++++++++++++++++

void ProductManager::searchProduct(bool& back, bool& flag)  //고객정보조회
{
    while (1)
    {
        int s, s_1, s_2, s_3, num_1;

 gofirst:                                                    //break를 만나지 않기 위한 goto문 lable (1 입력받았을 때 사용)
        cout << "1) 전체 목록 조회 2) 검색 3)종료" << endl; //상품정보를 한 번에 보는지, 검색해서 원하는 정보만 볼지 결정
        cout << "-> "; num_1 = getBnumber();   cout << endl;            //1) 전체 목록 조회 2)검색에 대한 입력값
        switch (num_1)                                        //1)전체 목록 2) 검색을 결정
        {
        case 1:                                                                                             //1)전체 목록 조회
            for (map<int, Product*>::iterator itr = ProductList.begin(); itr != ProductList.end(); itr++)  //map에 저장된 값을 iterator로 출력
            {
                cout << "=======================================================================================================" << endl;
                cout << "ID : P" << (*itr).second->getProductID() << " l " << "상품명 : " << (*itr).second->getProductName()
                    << " l " << "상품가격 : " << (*itr).second->getProductPrice() << " l " << "상품재고 : " << (*itr).second->getProductStock()<<endl;
                cout << "=======================================================================================================" << endl << endl;
            }                                                                                           //value에 있는 값들을 전부 출력
            goto gofirst;                                                                               //전체 출력하고 검색을 위해 함수의 맨 처음 기능으로 다시 실행하게 함
            break;
                    
        case 2:                                                 //검색

         cout << "원하는 방법을 선택하세요." << endl << endl;

         cout << "1) ID로 검색 2) 상품명으로 검색" << endl;    //원하는 방법으로 조회 if로 1,2를 받게 됨
         cout << "-> ";  s = getBnumber();          


        if (s == 1)                                                                       //id로 검색하는 방법
        {
            cout << "=============================================" << endl << endl;
            cout << "상품명 ID를 입력하세요 : P";                                                            //P는 ID에서 product의 번호라는 것을 구분하기 위해 넣어줌 client는 C, order는 R
            productid= getBnumber();                                                                          //id를 입력받음
            bool find = false;                                                                                //없는 정보를 입력했을 때 등록되지 않은 정보라는 것을 알려주기 위해
            for (map<int, Product*>::iterator itr = ProductList.begin(); itr != ProductList.end(); itr++)     //map값을 시작부터 end()가 아닐때까지 map에서 end는 마지막에 있는 값 다음을 의미하기 때문에
                                                                                                              //end가 아닐때까지면 값이 없는 끝을 의미한다
            {
                if (productid == (*itr).second->getProductID())                                  //id를 입력한 값이 있는 value의 데이터를 출력
                {
                    cout << "ID : P" << (*itr).second->getProductID() << "]" << endl; 
                    cout << "이름 : " << (*itr).second->getProductName() << endl;
                    cout << "핸드폰번호 : " << (*itr).second->getProductPrice() << endl;
                    cout << "재고수량 : " << (*itr).second->getProductStock() << endl << endl;
                    find = true;                                                                   //value에 있는 해당 값들을 출력 map에서 key는 First, value는 second 자리이기 때문
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
            cout << "1) 추가 조회 2) 첫화면으로 돌아가기 3) 종료" << endl<<endl;
            cout << "-> ";  s_1 = getBnumber();          //한 번 조회 후 추가로 실행하는 메뉴 선택 변수 (if 안 if)


            if (s_1 > 3 || s_1 < 0)     //s_1이 1,2,3 이외의 값을 받았을 때 다시 입력 
            {
                cout << "다시 입력해주세요." << endl;
                cout << "1) 다시 조회하기 2) 메뉴화면으로 돌아가기 3) 종료" << endl;
                cout << "-> ";  s_1 = getBnumber();
            }

            else if (s_1 == 2)      //s_1가 2 입력되었을때 첫 화면으로 돌아가기
            {
                system("cls");      //지나간 화면 지우기
                back = false;       //첫 화면으로 
                break;              //탈출하면서 back=true를 만나게 됨
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
            }                       //1이 입력되었을 때 break를 만나지 않고 함수의 맨 앞으로 돌아가기 위해 설정해줌 gofirst: 레이블을 만남
        }

        else if (s == 2)                                                                                        //상품명으로 조회하는 부분
        {
            cout << "=============================================" << endl;
            cout << "조회할 상품명을 입력하세요 : ";  cin >> productname;
            bool find = false;                                                                                  //등록되지 않은 정보를 입력했을 때 사용하기 위함
            for (map<int, Product*>::iterator itr = ProductList.begin(); itr != ProductList.end(); itr++)          //map값을 시작부터 end()가 아닐때까지      
                                                                                                                   //map에서 end는 마지막에 있는 값 다음을 의미하기 때문에 end가 아닐때까지면 값이 없는 끝을 의미한다
            {
                if (productname == (*itr).second->getProductName())                                                //id를 입력한 값이 있는 value의 데이터를 출력
                {
                    cout << "=============================================" << endl << endl;
                    cout << "ID : P" << (*itr).second->getProductID() << "]" << endl;
                    cout << "상품명 : " << (*itr).second->getProductName() << endl;
                    cout << "상품가격 : " << (*itr).second->getProductPrice() << endl;
                    cout << "재고수량 : " << (*itr).second->getProductStock() << endl << endl;
                    cout << "=============================================" << endl;
                                                                                                //value에 있는 해당 값들을 출력 map에서 key는 First, value는 second 자리이기 때문
                    find = true;                                                                //false로 들어온 find를 true로 바꿔 if(find==false)를 통과하지 못하게 한다
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
            cout << "-> "; s_2 = getBnumber();      //한 번 조회 후 추가로 실행하는 메뉴 선택 변수 (if 안 if)



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
            if (s_2 == 1)                       
            {
                goto gofirst;   //등록되지 않은 정보를 입력했을 때 다시 입력할 수 있도록 앞 gofirst_2레이블로 돌아가서 원하는 방법을 선택하게 함      
            }                   //1이 입력되었을 때(if문에 아무것도 걸리지 않고 내려옴)  break를 만나지 않고 함수의 맨 앞으로 돌아가기 위해 설정해줌 gofirst: 레이블을 만남
        }//switch끝
        }//if끝
        break;
    }//while끝
}//함수

//++++++++++++++++++++++++++++++상품정보변경+++++++++++++++++++++++++++++++++++++++++

void ProductManager::alterProduct(bool& back, bool& flag)//상품정보변경
{
    int t, t_1, t_2, t_3;

    while (1)
    {
gofirst_2:
        cout << "원하는 방법을 선택하세요." << endl << endl;

        cout << "1) ID로 검색 2) 상품명으로 검색" << endl;
        cout << "-> "; t = getBnumber();      //id,이름,번호를 선택해서 고객을 찾고, 그 정보를 변경


        switch (t)// ID, 이름, 핸드폰번호 선택 관련 switch
        {

        case 1:
        {
            cout << endl;
            cout << "상품 ID를 입력하세요 : P"; productid = getBnumber();//cin>>clientid를 사용할 시 int형이기 떄문에 문자 입력시 에러
            cout << endl;

            bool find = false;                                                                              //bool형 fine를 false로 선언
            for (map<int, Product*>::iterator itr = ProductList.begin(); itr != ProductList.end(); itr++)
            {
                if (productid == (*itr).second->getProductID())
                {
                    find = true;                                                                            //false로 들어온 find를 true로 바꿔 if(find==false)를 통과하지 못하게 한다
                    cout << "=============================================" << endl;
                    cout << "ID : P" << (*itr).second->getProductID() << endl;                               //value에 있는 해당 값들을 출력 map에서 key는 First, value는 second 자리이기 때문
                    cout << "상품명  : " << (*itr).second->getProductName() << endl;
                    cout << "상품가격  : " << (*itr).second->getProductPrice() << endl;
                    cout << "재고수량  : " << (*itr).second->getProductStock() << endl;
                    cout << "=============================================" << endl << endl;

                    cout << "변경할 정보를 선택하세요." << endl << endl;
                    cout <<  "1) 상품명 2) 상품가격 3) 재고수량 4) 전체변경" << endl;                      //변경할 정보를 부분적으로 선택 
                    cout << "-> "; t_1 = getBnumber();

                    if (t_1 == 1)
                    {
                        cout << "=============================================" << endl;                    //상품명만 변경
                        cout << "변경할 상품명  : ";
                        cin >> productname;
                        (*itr).second->setProductName(productname);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_1 == 2)
                    {
                        cout << "=============================================" << endl;                    //상품가격만 변경
                        cout << "변경할 상품가격  : ";
                        cin >> productprice;
                        (*itr).second->setProductPrice(productprice);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_1 == 3)
                    {
                        cout << "=============================================" << endl;
                        cout << "변경할 재고수량  : ";                                                       //재고수량만 변경
                        cin >> productstock;
                        (*itr).second->setProductStock(productstock);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_1 == 4)                                                                  //변경할 정보가 많을 경우 전체 변경을 통해 한 번에 바꿔준다
                    {
                        cout << "=============================================" << endl;
                        cout << "변경할 상품명 : ";
                        cin >> productname;
                        (*itr).second->setProductName(productname);
                        cout << "변경할 상품가격 : ";
                        cin >> productprice;
                        (*itr).second->setProductPrice(productprice);
                        cout << "변경할 재고수량 : ";
                        cin >> productstock;
                        (*itr).second->setProductStock(productstock);
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
            cout << "상품명을 입력하세요 : ";  cin >> productname;
            bool find = false;
            for (map<int, Product*>::iterator itr = ProductList.begin(); itr != ProductList.end(); itr++)
            {
                if (productname == (*itr).second->getProductName())                               //고객의 이름으로 고객정보를 찾아 출력
                {
                    find = true;                                                                 //false로 들어온 find를 true로 바꿔 if(find==false)를 통과하지 못하게 한다
                    cout << "=============================================" << endl;
                    cout << "ID : P" << (*itr).second->getProductID() << endl;                   //value에 있는 해당 값들을 출력 map에서 key는 First, value는 second 자리이기 때문
                    cout << "상품명  : " << (*itr).second->getProductName() << endl;
                    cout << "상품가격  : " << (*itr).second->getProductPrice() << endl;
                    cout << "재고수량  : " << (*itr).second->getProductStock() << endl;
                    cout << "=============================================" << endl << endl;

                    cout << "변경할 정보를 선택하세요." << endl << endl;
                    cout << "1) 상품명 2) 상품가격 3) 재고수량 4) 전체변경" << endl;                 //변경할 정보를 부분적으로 선택 
                    cout << "-> "; t_2 = getBnumber();

                    if (t_2 == 1)
                    {
                        cout << "=============================================" << endl;                //이름만 변경
                        cout << "변경할 상품명  : ";
                        cin >> productname;
                        (*itr).second->setProductName(productname);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_2 == 2)
                    {
                        cout << "=============================================" << endl;                 //상품가격만 변경
                        cout << "변경할 상품가격  : ";
                        cin >> productprice;
                        (*itr).second->setProductPrice(productprice);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_2 == 3)
                    {
                        cout << "=============================================" << endl;
                        cout << "변경할 재고수량  : ";                                                   //주소만 변경
                        cin >> productstock;
                        (*itr).second->setProductStock(productstock);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_2 == 4)                                                                  //변경할 정보가 많을 경우 전체 변경을 통해 한 번에 바꿔준다
                    {
                        cout << "=============================================" << endl;
                        cout << "변경할 상품명 : ";
                        cin >> productname;
                        (*itr).second->setProductName(productname);
                        cout << "변경할 상품가격 : ";
                        cin >> productprice;
                        (*itr).second->setProductPrice(productprice);
                        cout << "변경할 재고수량 : ";
                        cin >> productstock;
                        (*itr).second->setProductStock(productstock);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }

                }
            }

            if (find == false)                                           //for 안에서 입력되지 않은 정보를 알리기 위해 표현해주면 map 안에 들어있는 data만큼 돌기 때문에 문구가 여러번 출력됨
                                                                        //그렇기 때문에 find가 입력값이 value 안에 없을 때 find=true를 만나지 않고 그대로 find=false로 내려와 해당 문구가 출력되고, value 안에 입력값이 있을 때 
                                                                        //find true를 만나서 내려오기 때문에 find=false가 성립되지 않아 등록되지 않은 정보라는 문구가 출력되지 않는다       
            {
                cout << endl;
                cout << "=============================================" << endl;
                cout << "         등록되지 않은 정보입니다." << endl;
                cout << "=============================================" << endl << endl;
                goto gofirst_2;                                          //등록되지 않은 정보를 입력했을 때 다시 입력할 수 있도록 앞 gofirst_2레이블로 돌아가서 원하는 방법을 선택하게 함
            }
        }
        break;

        }

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

void ProductManager::eraseProduct(bool& back, bool& flag)
{
gofirst_3:
    int e, e_1;
    bool repeat(true);
    while (repeat)
    {
        if (ProductList.size() == 0)                                                     //ClientList (map)에 데이터가 존재하지 않을 때 즉 map의 사이즈가 0일때 
        {                                                                               //정보가 존재하지 않음을 알리고 메뉴화면으로 돌아가거나 정상 종료하도록 알림
            cout << endl;
            cout << "=============================================" << endl;
            cout << "      List에 정보가 존재하지 않습니다" << endl;
            cout << "=============================================" << endl << endl;
            cout << "1) 메뉴화면으로 돌아가기 2) 종료" << endl; e = getBnumber();

            if (e == 1)
            {                                       //e가 1일 때 메뉴화면으로 돌아감
                system("cls");                      //지나간 화면 사라지게
                back = false;                       //main의 처음 back = true를 만나 첫 메뉴 화면 출력
                break;
            }

            else if (e == 2)
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


        else if (ProductList.size() != 0)                                                                //ClientSize가 0이 아닐 때 즉 데이터가 있을 때를 의미 eise if 꼭 표현 안 해도 실행됨
        {
            cout << "삭제할 고객 ID를 입력하세요 : P"; productid = getBnumber();                         //상품 id를 입력받아 삭제
            bool find = false;
            for (map<int, Product*>::iterator itr = ProductList.begin(); itr != ProductList.end(); itr++)
            {
                if (productid == (*itr).second->getProductID())
                {
                    find = true;                                                                              //false로 들어온 find를 true로 바꿔 if(find==false)를 통과하지 못하게 한다
                    // ClientList.erase(clientid = ClientList[i]->getClientID());
                    ProductList.erase(productid);                                                              //ProductList즉 map의 key인 ProductID를 입력받아 해당 value를 삭제
                    cout << "=============================================" << endl;
                    cout << "                삭제되었습니다." << endl;
                    cout << "=============================================" << endl << endl;
                    cout << "1) 추가 삭제하기 2) 메뉴화면으로 돌아가기 3) 종료" << endl; e_1 = getBnumber();   //추가 삭제를 할지 다른 기능을 사용할지 프로그램을 종료할지 선택

                    if (e_1 == 2)
                    {
                        system("cls");
                        back = false;//첫 화면으로
                        repeat = false;             //break가 if만 빠져나가기 때문에 back만 가지고 메뉴첫화면으로 돌아갈 수 없음 
                        break;                      // while도 빠져나가도록 repeat가 true일때 실행되는 while을 false로 해서 빠져나가게함               
                    }

                    else if (e_1 > 3 || e_1 < 0)//e_1이 1만 조건문을 통과하도록 예외적인 상황을 만들어 추가적인 상황을 표현
                    {
                        cout << endl;
                        cout << "=============================================" << endl;
                        cout << "            다시 입력해주세요." << endl;
                        cout << "=============================================" << endl;
                        cout << "1) 추가 삭제하기 2) 메뉴화면으로 돌아가기 3) 종료" << endl;
                        cout << "->"; e_1 = getBnumber();
                    }

                    else if (e_1 == 3)
                    {
                        system("cls");//지나간 화면 지우기
                        cout << endl;
                        cout << "=============================================" << endl;
                        cout << "       프로그램이 종료되었습니다." << endl;
                        cout << "=============================================" << endl;
                        flag = false;                                      //main의 flag = false 조건을 만나 reuturn 0; 으로 반환되어 정상 종료
                        break;
                    }

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


int ProductManager::makeId()        //id(key)를 자동부여하는 inputClient에 사용한 함수
{
    auto key = ProductList.end();   //end()는 map의 끝 다음자리를 가리킨다
    if (ProductList.size() == 0) {  //map의 end까지 size가 0이면 return 0;
        return 0;
    }
    else {                           //size가 0이 아니라면 end가 마지막 데이터 다음 자리이기 때문에 --key 자리부터
        int id = (--key)->first;
        return ++id;                  //id하나씩 +1 해가면서 부여
    }
}

map<int, Product*> ProductManager::getProductList()         //Ordermanger에서 사용하기 위해 선언

{
    return ProductList;
}

map<int, Product*> ProductManager::setProductList()         //Ordermanger에서 사용하기 위해 선언
{
    return ProductList;
}

//========================파일입출력===========================

ProductManager::ProductManager()                                                     //기본 생성자 : 파일 읽기
{ 
    ifstream file;
    file.open("productlist.txt");                                                     //.txt로 생성된 파일 open
    if (!file.fail()) {                                                               //파일이 있으면 작업
        while (!file.eof()) {                                                         //파일이 끝까지 갈때까지
            vector<string> row = parseCSV(file, ',');                                 //한줄만 읽어
            if (row.size()) {
                int productid = atoi(row[0].c_str());                                 //int형으로 바꿔줌 stoi(row[0]) 표현 가능 string to int / auto to int
                Product* p = new Product(productid, row[1], row[2], row[3]);
                ProductList.insert({ productid, p });                                 //파일에서 읽어온 하나를 map에 저장
            }
        }
    }
    file.close();

}

ProductManager::~ProductManager()                                            //기본 소멸자 : 파일 저장
{
    ofstream file;
    file.open("productlist.txt");
    if (!file.fail()) {                                                      //파일을 열 수 없으면? 리드 온리 같은 거
        for (const auto& v : ProductList) {
            Product* p = v.second;                                           //값
            file << p->getProductID() << ", " << p->getProductName() << ", ";
            file << p->getProductPrice() << ", ";
            file << p->getProductStock()<<endl;                              //한줄에 콤마로 구분하면서 들어감

        }
    }
    file.close();                                                           //파일 open했으면 닫아줘야함
}

vector<string> ProductManager::parseCSV(istream& file, char delimiter)
{
    stringstream ss;
    vector<string> row;
    string t = " \n\r\t";

    while (!file.eof()) {                                     //마지막 줄이 아니면 들어옴
        char c = file.get();                                  //한글자를 읽어와서
        if (c == delimiter || c == '\r' || c == '\n') {       //컴마, 줄바꿈
            if (file.peek() == '\n') file.get();;             //피크는 다음 글자를 보는 것
            string s = ss.str();                              //str을 이용해서 stringstream에서 string으로 변환
            s.erase(0, s.find_first_not_of(t));               //맨 앞부터 t가 아닌 글자가 나올때까지 제거
            s.erase(s.find_last_not_of(t) + 1);
            row.push_back(s);
            ss.str("");
            if (c != delimiter) break;
        }
        else {
            ss << c;                                        //콤마가 나올때까지 계속 추가
        }
    }
    return row;
}

Product* ProductManager::search(int id)
{
    auto it = ProductList.find(id);                                  //client가 입력한 id를 찾음 find()        
    return (it != ProductList.end()) ? ProductList[id] : nullptr;    //map값이 있으면 ClientList[id] 없으면 nullptr
}


void ProductManager::displayInfo(int id)                                //책임중심
{
    auto it = ProductList.find(id);                                      //product가 입력한 id를 찾음 find()
    if(it != ProductList.end()) {                                        //productlist의 end()가 아니면 -> null이 아니면 -> 데이터가 있으면
        Product* product = it->second;                                   //value값 출력
        cout << "상품명 : " << product->getProductName() << endl;
        cout << "상품가격 : " << product->getProductPrice() << endl;
        cout << "상품재고 : " << product->getProductStock() << endl;
       
    }
}