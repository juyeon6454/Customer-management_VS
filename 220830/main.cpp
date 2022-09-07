#include "client.h"         //""만든 헤더파일 참조
#include "product.h"
#include "order.h"
#include "ordermanager.h"
#include "clientmanager.h"
#include "productmanager.h"
#include <algorithm>
#include <map>
#include <string>
#include <conio.h>

using namespace std;
extern int getBnumber();    //int 변수가 문자열을 받을때 나는 오류를 위해

int main()
{
    int num;            //첫 메뉴 선택 변수 선언
    int a, b, c;        //메뉴 선택 변수 선언
    int id = 0;         //id를 0으로 초기화
    bool back = true;   //첫 화면으로 이동을 위해 사용
    bool flag = true;   //프로그램 정상 종료를 위해 사용

    ClientManager clientmanager;        //Clientmanger 함수를 사용
    ProductManager productmanager;      //Productmanger 함수를 사용
    OrderManager ordermanager;          //Ordermanger 함수를 사용

    back = true;        //첫 메뉴 화면으로 돌아오기 위해 사용한 bool

input:
    if (flag == false)  //프로그램 정상 종료를 위해 flag가 false일때 return //back일 경우에는 while이 다시 돌아야 하기 때문에 if로 선언
        return 0;

        cout << endl;
        cout << "******* 상품관리 프로그램 *******" << endl << endl;
        cout << "       1. 고객 정보 관리" << endl;
        cout << "       2. 상품 정보 관리" << endl;
        cout << "       3. 쇼핑 정보 관리" << endl;
        cout << "       4. 프로그램 종료" << endl << endl;
        cout << "*********************************" << endl << endl;
        cout << "원하시는 서비스를 선택해주세요 :  ";  num = getBnumber();
        system("cls");

        switch (num)    //상품관리 프로그램 첫 화면 메뉴 선택 case 1,2,3 num
        {
           
        case 1:
aa:
            cout << endl;
            cout << "******** 고객 정보 관리 ********" << endl << endl;
            cout << "      1) 고객 정보 입력" << endl;
            cout << "      2) 고객 정보 조회" << endl;
            cout << "      3) 고객 정보 변경" << endl;
            cout << "      4) 고객 정보 삭제" << endl << endl;
            cout << "********************************" << endl << endl;
            cout << "원하시는 번호를 선택해주세요 : ";  a = getBnumber();;
            system("cls");


            switch (a)
            {
            case 1:
                cout << endl;
                cout << "============고객 정보 입력============" << endl<<endl;
                clientmanager.inputClient(back, flag);                          //Clientmanager에 선언된 inputClient 함수 사용
                break;
            case 2:
                cout << endl;
                cout << "============고객 정보 조회============" << endl<<endl;
                clientmanager.searchClient(back, flag);                          //Clientmanager에 선언된 searchClient 함수 사용
                break;
            case 3:
                cout << endl;
                cout << "============고객 정보 변경============" << endl<<endl;
                clientmanager.alterClient(back, flag);                          //Clientmanager에 선언된 alterClient 함수 사용
                break;
            case 4:
                cout << endl;
                cout << "============고객 정보 삭제============" << endl<< endl;
                clientmanager.eraseClient(back, flag);                          //Clientmanager에 선언된 eraseClient 함수 사용
                break;
            default:
                if (cin.fail())                                                      //숫자 외의 입력값이 들어갔을 때 입력값이 무시되고 다시 입력하도록 함
                {
                    cout << endl;
                    cout << "※ 번호를 다시 선택해주세요 ※" << endl << endl;
                    cin.clear();
                    cin.ignore(1024, '\n');
                    goto aa;                                                    
                }
                if (num > 4)
                {
                    cout << endl;                                                       //4보다 큰 숫자들이 들어갈 때 상품정리 선택 화면 오도록 goto 사용 aa: 레이블로 이동
                    cout << "※ 번호를 다시 선택해주세요 ※" << endl << endl;
                    goto aa;
                }

                break;
            }
            //break;
            goto input;
            //+++++++++++++++++고객 switch문 끝 / product 시작 ++++++++++++++++++++++++++++++++++++++++++++++++++++
        case 2:
bb:
            cout << endl;
            cout << "******* 상품 정보 관리 ******" << endl << endl;
            cout << "      1)상품 정보 입력" << endl;
            cout << "      2)상품 정보 조회" << endl;
            cout << "      3)상품 정보 변경" << endl;
            cout << "      4)상품 정보 삭제" << endl << endl;
            cout << "********************************" << endl << endl;
            cout << "원하시는 번호를 선택해주세요 : ";  b = getBnumber();;
            system("cls");
            switch (b)
            {
            case 1:
                cout << endl;
                cout << "============상품 정보 입력============" << endl;
                productmanager.inputProduct(back, flag);                          //Productmanager에 선언된 inputProduct 함수 사용
                break;
            case 2:
                cout << endl;
                cout << "============상품 정보 조회============" << endl;
                productmanager.searchProduct(back, flag);                          //Productmanager에 선언된 searchProduct 함수 사용
                break;
            case 3:
                cout << endl;
                cout << "============상품 정보 변경============" << endl;
                productmanager.alterProduct(back, flag);                          //Productmanager에 선언된 alterProduct 함수 사용
                break;
            case 4:
                cout << endl;
                cout << "============상품 정보 삭제============" << endl;
                productmanager.eraseProduct(back, flag);                          //Productmanager에 선언된 eraseProduct 함수 사용
                break;
            default:
                if (cin.fail())                                                 //숫자 외의 입력값이 들어갔을 때 입력값이 무시되고 다시 입력하도록 함
                {
                    cout << endl;
                    cout << "※ 번호를 다시 선택해주세요 ※" << endl << endl;
                    cin.clear();
                    cin.ignore(1024, '\n');
                    goto bb;
                }
                if (num > 4)                                                    //4보다 큰 숫자들이 들어갈 때 상품정리 선택 화면 오도록 goto 사용 bb: 레이블로 이동
                {
                    cout << endl;
                    cout << "※ 번호를 다시 선택해주세요 ※" << endl << endl;
                    goto bb;                                                    //bb레이블로 이동
                }

                break;                                                          //switch를 빠져나감
            }
            goto input;                                                         //input레이블로 이동 첫 메뉴 화면으로 이동

            //+++++++++++++++++상품 switch 끝 / order 시작 +++++++++++++++++++++++++++++++++++++++++++++
        case 3:
 cc:
            cout << endl;
            ordermanager.organizeOrderList(clientmanager, productmanager);
            cout << "******* 쇼핑 정보 관리 *******" << endl << endl;
            cout << "      1)상품 주문" << endl;
            //구매일자, 고객 정보(전화번호), 상품정보(ID)
            cout << "      2)주문 조회" << endl;
            cout << "      3)주문 변경" << endl;
            cout << "      4)주문 취소" << endl << endl;
            cout << "********************************" << endl << endl;
            cout << "원하시는 번호를 선택해주세요 : ";  c = getBnumber();;
            system("cls");
            switch (c)
            {
            case 1:
                cout << endl;
                cout << "============상품 주문============" << endl;
                ordermanager.inputOrder(back,flag, clientmanager, productmanager);                          //Ordermanager에 선언된 inputOrder 함수 사용
                break;
            case 2:
                cout << endl;
                cout << "============주문 조회============" << endl;
                ordermanager.searchOrder(back, flag, clientmanager, productmanager);                         //Ordermanager에 선언된 searchOrder 함수 사용
                break;
            case 3:
                cout << endl;
                cout << "============주문 변경============" << endl;
                ordermanager.alterOrder(back, flag, clientmanager, productmanager);                          //Ordermanager에 선언된 alterOrder 함수 사용
                break;
            case 4:
                cout << endl;
                cout << "============주문 취소============" << endl;
                ordermanager.eraseOrder(back, flag, clientmanager, productmanager);                          //Ordermanager에 선언된 eraseOrder 함수 사용
                break;
            default:
                if (cin.fail())                                            
                {
                    cout << endl;
                    cout << "※ 번호를 다시 선택해주세요 ※" << endl << endl;
                    cin.clear();                                                //숫자 외의 입력값이 들어갔을 때 입력값이 무시되고 다시 입력하도록 함
                    cin.ignore(1024, '\n');
                    goto cc;
                }
                if (num > 4)
                {
                    cout << endl;
                    cout << "※ 번호를 다시 선택해주세요 ※" << endl << endl;   //4보다 큰 숫자들이 들어갈 때 상품관리 선택 화면 오도록 goto 사용 cc: 레이블로 이동
                    goto cc;
                }

                break;
            }

           // break;
            goto input;

        case 4://프로그램 종료
            cout << endl;
            cout << "==========================" << endl;
            cout << "프로그램이 종료되었습니다." << endl;
            cout << "==========================" << endl;
            return 0;

        default://5이상의 숫자 받으면 처음으로 돌아감
            if (cin.fail())//숫자 외의 입력값이 들어갔을 때 다시 입력하라고 알림
            {
                cout << endl;
                cout << "※ 번호를 다시 선택해주세요 ※" << endl << endl;     //숫자 외의 입력값이 들어갔을 때 입력값이 무시되고 다시 입력하도록 함
                cin.clear();
                cin.ignore(1024, '\n');
                goto input;
            }
            if (num > 4)                                                     //4보다 큰 숫자들이 들어갈 때 상품관리 선택 화면 오도록 goto 사용 cc: 레이블로 이동
            {
                cout << endl;
                cout << "※ 번호를 다시 선택해주세요 ※" << endl << endl;
                goto input;
            }
        
            break;
        }
 

    return 0;
}


int getBnumber()                                //int 변수가 문자열을 받을때 나는 오류를 위해 숫자만 받을 수 있도록함
{
    int n, i = 0;
    char ch, str[128];                          //문자열 배열 자리
    while (1) {
        do {                                    
            ch = _getch();                      //한글자씩 입력 받는 함수
            if (ch == '\r')                     //줄바꿈 마지막 문자가
            {
                cout << endl;
                goto END;
            }
            else if (ch == '\b' && i > 0)        //문자가 들어오면 하나씩 지움
            {
                cout << "\b \b";
                i--;
            }
            //else if (ch < '0' || ch > '9')     //한자리 숫자 외의 수가 눌리면 잘못된 입력이라고 출력됨
            //{
            //    cout << "잘못된 입력입니다. 다시 입력하세요." << endl;
            //    i = 0;
            //}
        } while (ch < '0' || ch > '9');
        cout << ch;
        str[i++] = ch;
    }
END:
    str[i++] = '\0';
    n = atoi(str);
    return n;

   
}
    