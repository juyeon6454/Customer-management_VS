#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include "client.h"
#include "clientmanager.h"
#include "product.h"
#include "productmanager.h"

int num;
int clientid = 0;
string clientname,clientaddress,clientphonenumber,clientemail;
map<int, Client*> ClientList;
extern int getBnumber();        //int형은 숫자만 받기 위해서 사용

//++++++++++++++++++++++++++++++고객정보입력+++++++++++++++++++++++++++++++++++++++++
void ClientManager::inputClient(bool& back, bool&flag)          //고객정보입력함수
{
    while (1)
    {
        int p;          //한 번 등록후 추가 실행할 메뉴 선택 변수
        string s;       //'-'가 포함된 전화번호를 '-'없이 저장하기 위한 변수

        cout << "이름 : "; cin >> clientname;
        cout << endl;
        cout << "번호 : "; cin >> s;
        cout << endl;
        stringstream ss(s);     
        string buffer;

        while (getline(ss, buffer, '-') ){
            clientphonenumber += buffer;            //'-'가 있는 buffer에서 끊어서 번호만 저장해줌
        }                                           //'-'가 포함된 번호를 입력받았을때 '-'가 포함되지 않게 저장

        cout << "주소 : "; cin >> clientaddress;
        cout << endl;
        cout << "E-mail : "; cin >> clientemail;
        cout << endl;                              //이름, 번호, 주소, 이메일 입출력

        int clientid = makeId();                   //id(key) 자동배정 (직접 입력하면 중복 문제)                                                                                  //id(key) 자동배정 (직접 입력하면 중복 문제)
        ClientList.insert(make_pair(clientid, new Client(clientid, clientname, clientphonenumber, clientaddress, clientemail)));    //map의 key,value값 저장
        cout << clientname << " 님의 ID는 [C" << clientid << "] 입니다." << endl<<endl;                                             //배정된 id(key)가 몇 번인지 알림
        cout << "등록이 완료되었습니다."<<endl<<endl;
        cout << "======================================" << endl;
        cout << "1) 추가 입력 2) 처음으로 돌아가기 3) 종료"<< endl<<endl;   //한 번 등록후 추가 실행할 메뉴 선택
        cout << "실행할 메뉴를 선택해주세요 : "; p = getBnumber();          //한 번 등록후 추가 실행할 메뉴 선택 변수
        cout << endl;
        
        if (p > 3 || p < 0)                  //p가 1,2,3 이외의 값을 받았을 때 다시 입력
        {
            cout << "다시 입력해주세요." << endl;
            cout << "======================================" << endl<<endl;
            cout << "1) 추가 입력 2) 메뉴화면으로 돌아가기 3) 종료"<< endl;
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
             flag= false;    //main 앞에 조건문을 추가함으로써 return 0을 만나게 됨
             break;
         }
    }
 }

//++++++++++++++++++++++++++++++고객정보조회+++++++++++++++++++++++++++++++++++++++++

void ClientManager::searchClient(bool& back, bool& flag)    //고객정보조회
{
    while (1)
    {
        int s,s_1,s_2,s_3, num;

gofirst:                                                    //break를 만나지 않기 위한 goto문 lable (1 입력받았을 때 사용)
        cout << "1) 전체 목록 조회 2) 검색 3)종료" << endl; //고객정보를 한 번에 보는지, 검색해서 원하는 정보만 볼지 결정
        cout << "-> "; num = getBnumber();   cout << endl;            //1) 전체 목록 조회 2)검색에 대한 입력값
        switch (num)                                        //1)전체 목록 2) 검색을 결정
        {
        case 1:                                                                                         //1)전체 목록 조회
            for (map<int, Client*>::iterator itr = ClientList.begin(); itr != ClientList.end(); itr++)  //map에 저장된 값을 iterator로 출력
            {
                cout << "=======================================================================================================" << endl;
                cout << "ID : C" << (*itr).second->getClientID() << " l " << "이름 : " << (*itr).second->getClientName()
                    << " l " << "핸드폰번호 : " << (*itr).second->getClientNumber() << " l " << "주소 : " << (*itr).second->getClientAddress()
                    << " l " << "E-mail : " << (*itr).second->getClientEmail() << endl;
                cout << "=======================================================================================================" << endl << endl;
            }                                                                                           //value에 있는 값들을 전부 출력
            goto gofirst;                                                                               //전체 출력하고 검색을 위해 함수의 맨 처음 기능으로 다시 실행하게 함
            break;

        case 2:                                                                      //검색

            cout << "원하는 방법을 선택하세요." << endl << endl;

            cout << "1) ID로 검색 2) 이름으로 검색 3) 핸드폰번호로 검색" << endl;    //원하는 방법으로 조회 if로 1,2,3을 받게 됨
            cout << "-> ";  s = getBnumber();                                              
  

            if (s == 1)                                                                                      //id로 검색하는 방법
            {
                cout << "=============================================" << endl << endl;
                cout << "조회할 고객 ID를 입력하세요 : C";                                                    //C는 ID에서 clinet의 번호라는 것을 구분하기 위해 넣어줌 product는 P, order는 R
                clientid = getBnumber();                                                                             //id를 입력받음
                bool find = false;                                                                           //없는 정보를 입력했을 때 등록되지 않은 정보라는 것을 알려주기 위해
                for (map<int, Client*>::iterator itr = ClientList.begin(); itr != ClientList.end(); itr++)
                                                                                                             //map값을 시작부터 end()가 아닐때까지 map에서 end는 마지막에 있는 값 다음을 의미하기 때문에
                                                                                                              //end가 아닐때까지면 값이 없는 끝을 의미한다
                {
                    if (clientid == (*itr).second->getClientID())                               //id를 입력한 값이 있는 value의 데이터를 출력
                    {
                        cout << endl;
                        cout << "ID : C" << (*itr).second->getClientID() << endl;
                        cout << "이름 : " << (*itr).second->getClientName() << endl;
                        cout << "핸드폰번호 : " << (*itr).second->getClientNumber() << endl;
                        cout << "주소 : " << (*itr).second->getClientAddress() << endl;
                        cout << "E-mail : " << (*itr).second->getClientEmail() << endl << endl;
                        find = true;
                    }                                                                           //value에 있는 해당 값들을 출력 map에서 key는 First, value는 second 자리이기 때문
                }

                if (find == false)//for 안에서 입력되지 않은 정보를 알리기 위해 표현해주면 map 안에 들어있는 data만큼 돌기 때문에 문구가 여러번 출력됨
                                   //그렇기 때문에 find가 입력값이 value 안에 없을 때 find=true를 만나지 않고 그대로 find=false로 내려와 해당 문구가 출력되고, value 안에 입력값이 있을 때 
                                   //find true를 만나서 내려오기 때문에 find=false가 성립되지 않아 등록되지 않은 정보라는 문구가 출력되지 않는다
                {
                    cout << "=============================================" << endl;
                    cout << "      등록되지 않은 정보입니다." << endl;
                }
            
                cout << "=============================================" << endl << endl;
                cout << "1) 추가 조회 2) 메뉴화면으로 돌아가기 3) 종료" << endl<<endl;
                cout << "-> "; s_1 = getBnumber();      //한 번 조회 후 추가로 실행하는 메뉴 선택 변수


                if (s_1 > 3 || s_1 < 0)   //s_1이 1,2,3 이외의 값을 받았을 때 다시 입력 
                {
                    cout << "다시 입력해주세요." << endl;
                    cout << "1) 다시 조회하기 2) 메뉴화면으로 돌아가기 3) 종료" << endl;
                    cout << "-> "; s_1 = getBnumber();
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
                }                                                          //1이 입력되었을 때 break를 만나지 않고 함수의 맨 앞으로 돌아가기 위해 설정해줌 gofirst: 레이블을 만남
            }



            else if (s == 2)                                                                                        //이름으로 조회하는 부분
            {
                cout << "=============================================" << endl;
                cout << "조회할 이름을 입력하세요 : ";  cin >> clientname;
                bool find = false;                                                                                  //등록되지 않은 정보를 입력했을 때 사용하기 위함
                for (map<int, Client*>::iterator itr = ClientList.begin(); itr != ClientList.end(); itr++)          //map값을 시작부터 end()가 아닐때까지
                                                                                                                    //map에서 end는 마지막에 있는 값 다음을 의미하기 때문에 end가 아닐때까지면 값이 없는 끝을 의미한다
                {
                    if (clientname == (*itr).second->getClientName())                                                //id를 입력한 값이 있는 value의 데이터를 출력
                    {
                        cout << "=============================================" << endl << endl;
                        cout << "ID : C" << (*itr).second->getClientID() << endl;
                        cout << "이름 : " << (*itr).second->getClientName() << endl;
                        cout << "핸드폰번호 : " << (*itr).second->getClientNumber() << endl;
                        cout << "주소 : " << (*itr).second->getClientAddress() << endl;
                        cout << "E-mail : " << (*itr).second->getClientEmail() << endl << endl;
                        cout << "=============================================" << endl;            //value에 있는 해당 값들을 출력 map에서 key는 First, value는 second 자리이기 때문
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
                    cout <<"============================================="  << endl;
                    cout << "          다시 입력해주세요." << endl;
                    cout << "============================================="  << endl;
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
                }                    //1이 입력되었을 때(if문에 아무것도 걸리지 않고 내려옴)  break를 만나지 않고 함수의 맨 앞으로 돌아가기 위해 설정해줌 gofirst: 레이블을 만남
            }

            else if (s == 3)                                                                                //s로 3을 입력했을때 전화번호로 정보 조회
            {
                cout << "전화번호를 입력하세요 * (-) 없이 입력 * : ";  cin >> clientphonenumber;
                bool find = false;
                for (map<int, Client*>::iterator itr = ClientList.begin(); itr != ClientList.end(); itr++)//map값을 시작부터 end()가 아닐때까지
                                                                                                          //map에서 end는 마지막에 있는 값 다음을 의미하기 때문에 end가 아닐때까지면 값이 없는 끝을 의미
                {
                    if (clientphonenumber == (*itr).second->getClientNumber())                          
                    {
                        cout << "=============================================" << endl << endl;
                        cout << "ID : C" << (*itr).second->getClientID() << endl;                        //입력값과 입력값이 있는 곳의 데이터가 일치할 때 그 value를 출력한다
                        cout << "이름 : " << (*itr).second->getClientName() << endl;
                        cout << "핸드폰번호 : " << (*itr).second->getClientNumber() << endl;
                        cout << "주소 : " << (*itr).second->getClientAddress() << endl;                                                                                                               
                        cout << "E-mail : " << (*itr).second->getClientEmail() << endl << endl;
                        cout << "=============================================" << endl;
                        find = true;
                    }
                  
                    
                }
                if (find==false)  //for 안에서 입력되지 않은 정보를 알리기 위해 표현해주면 map 안에 들어있는 data만큼 돌기 때문에 문구가 여러번 출력됨
                                   //그렇기 때문에 find가 입력값이 value 안에 없을 때 find=true를 만나지 않고 그대로 find=false로 내려와 해당 문구가 출력되고, value 안에 입력값이 있을 때 
                                   //find true를 만나서 내려오기 때문에 find=false가 성립되지 않아 등록되지 않은 정보라는 문구가 출력되지 않는다
                {
                    cout << "=============================================" << endl;
                    cout << "      등록되지 않은 정보입니다." << endl;
                    
                }
          
                cout << "1) 추가 조회 2) 첫화면으로 돌아가기 3) 종료" << endl;
                cout << "-> "; s_3 = getBnumber();                                               //한 번 조회 후 추가로 실행하는 메뉴 선택 변수
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
        }//switch
        break;
    }//while
 }//함수

 //++++++++++++++++++++++++++++++고객정보변경+++++++++++++++++++++++++++++++++++++++++

void ClientManager::alterClient(bool& back, bool& flag)//고객정보변경
{

    int t, t_1, t_2, t_3;

    while (1)
    {
gofirst_2:
        cout << "원하는 방법을 선택하세요." << endl << endl;

        cout << "1) ID로 검색 2) 이름으로 검색 3) 핸드폰번호로 검색" << endl;
        cout << "-> "; t = getBnumber();      //id,이름,번호를 선택해서 고객을 찾고, 그 정보를 변경

        switch (t)      //id,이름,번호를 선택해서 고객을 찾고, 그 정보를 변경
        {

        case 1:
        {
            cout << endl;
            cout << "고객 ID를 입력하세요 : C"; clientid = getBnumber();//cin>>clientid를 사용할 시 int형이기 떄문에 문자 입력시 에러
            cout << endl;
          
            bool find = false;                                                                              //bool형 fine를 false로 선언
            for (map<int, Client*>::iterator itr = ClientList.begin(); itr != ClientList.end(); itr++)
            {
                if (clientid == (*itr).second->getClientID())
                {
                    find = true;                                                                            //false로 들어온 find를 true로 바꿔 if(find==false)를 통과하지 못하게 한다
                    cout << "=============================================" << endl;
                    cout << "ID : C" << (*itr).second->getClientID() << endl;                               //value에 있는 해당 값들을 출력 map에서 key는 First, value는 second 자리이기 때문
                    cout << "이름 : " << (*itr).second->getClientName() << endl;
                    cout << "핸드폰번호 : " << (*itr).second->getClientNumber() << endl;
                    cout << "주소 : " << (*itr).second->getClientAddress() << endl;
                    cout << "E-mail : " << (*itr).second->getClientEmail() <<  endl;
                    cout << "=============================================" << endl<<endl;
                
                    cout << "변경할 정보를 선택하세요." << endl << endl;
                    cout << "1) 이름 2) 핸드폰번호 3) 주소 4) E-mail 5) 전체변경" << endl;                   //변경할 정보를 부분적으로 선택 
                    cout << "-> "; t_1 = getBnumber();

                    if (t_1 == 1)
                    {
                        cout << "=============================================" << endl;                    //이름만 변경
                        cout << "변경할 이름 : ";
                        cin >> clientname;
                        (*itr).second->setClientName(clientname);
                        cout << "=============================================" << endl;                   
                        cout << endl;
                    }
                    else if (t_1 == 2)
                    {
                        cout << "=============================================" << endl;                //핸드폰번호만 변경
                        cout << "변경할 핸드폰번호 : ";
                        cin >> clientphonenumber;
                        (*itr).second->setClientNumber(clientphonenumber);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_1 == 3)
                    {
                        cout << "=============================================" << endl;
                        cout << "변경할 주소 : ";                                                            //주소만 변경
                        cin >> clientaddress;
                        (*itr).second->setClientAddress(clientaddress);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_1 == 4)
                    {
                        cout << "=============================================" << endl;
                        cout << "변경할 E-mail : ";                                                        //이메일만 변경
                        cin >> clientemail;
                        (*itr).second->setClientEmail(clientemail);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_1 == 5)                                                                  //변경할 정보가 많을 경우 전체 변경을 통해 한 번에 바꿔준다
                    {
                        cout << "=============================================" << endl;
                        cout << "변경할 이름 : ";
                        cin >> clientname;
                        (*itr).second->setClientName(clientname);
                        cout << "변경할 핸드폰번호 : ";
                        cin >> clientphonenumber;
                        (*itr).second->setClientNumber(clientphonenumber);
                        cout << "변경할 주소 : ";
                        cin >> clientaddress;
                        (*itr).second->setClientAddress(clientaddress);
                        cout << "변경할 E-mail : ";
                        cin >> clientemail;
                        (*itr).second->setClientEmail(clientemail);
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
        cout << "고객 이름을 입력하세요 : ";  cin >> clientname;
        bool find = false;
        for (map<int, Client*>::iterator itr = ClientList.begin(); itr != ClientList.end(); itr++)
        {
            if (clientname == (*itr).second->getClientName())                               //고객의 이름으로 고객정보를 찾아 출력
            {
                find = true;                                                                 //false로 들어온 find를 true로 바꿔 if(find==false)를 통과하지 못하게 한다
                cout << "=============================================" << endl;
                cout << "ID : C" << (*itr).second->getClientID() << endl;                    //value에 있는 해당 값들을 출력 map에서 key는 First, value는 second 자리이기 때문
                cout << "이름 : " << (*itr).second->getClientName() << endl;
                cout << "핸드폰번호 : " << (*itr).second->getClientNumber() << endl;
                cout << "주소 : " << (*itr).second->getClientAddress() << endl;
                cout << "E-mail : " << (*itr).second->getClientEmail() << endl;
                cout << "=============================================" << endl << endl;

                cout << "변경할 정보를 선택하세요." << endl << endl;
                cout << "1) 이름 2) 핸드폰번호 3) 주소 4) E-mail 5) 전체변경" << endl;        //변경할 정보를 부분적으로 선택 
                cout << "-> "; t_2 = getBnumber();

                if (t_2 == 1)
                {
                    cout << "=============================================" << endl;          //이름만 변경
                    cout << "변경할 이름 : ";    
                    cin >> clientname;
                    (*itr).second->setClientName(clientname);
                    cout << "=============================================" << endl;
                    cout << endl;
                }
                else if (t_2 == 2)
                {
                    cout << "=============================================" << endl;           //핸드폰번호만 변경
                    cout << "변경할 핸드폰번호 : ";
                    cin >> clientphonenumber;
                    (*itr).second->setClientNumber(clientphonenumber);
                    cout << "=============================================" << endl;
                    cout << endl;
                }
                else if (t_2 == 3)
                {
                    cout << "=============================================" << endl;           //주소만 변경
                    cout << "변경할 주소 : ";
                    cin >> clientaddress;
                    (*itr).second->setClientAddress(clientaddress);
                    cout << "=============================================" << endl;
                    cout << endl;
                }
                else if (t_2 == 4)
                {
                    cout << "=============================================" << endl;
                    cout << "변경할 E-mail : ";                                                //이메일만 변경
                    cin >> clientemail;
                    (*itr).second->setClientEmail(clientemail);
                    cout << "=============================================" << endl;
                    cout << endl;
                }
                else if (t_2 == 5)
                {
                    cout << "=============================================" << endl;            //변경할 정보가 많을 경우 전체 변경을 통해 한 번에 바꿔준다
                    cout << "변경할 이름 : ";
                    cin >> clientname;
                    (*itr).second->setClientName(clientname);
                    cout << "변경할 핸드폰번호 : ";
                    cin >> clientphonenumber;
                    (*itr).second->setClientNumber(clientphonenumber);
                    cout << "변경할 주소 : ";
                    cin >> clientaddress;
                    (*itr).second->setClientAddress(clientaddress);
                    cout << "변경할 E-mail : ";
                    cin >> clientemail;
                    (*itr).second->setClientEmail(clientemail);
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
        case 3:
        {
            cout << "=============================================" << endl;                                
            cout << "고객 전화번호를 입력하세요 : ";  cin >> clientphonenumber;                              //고객의 전화번호로 고객정보를 찾아 출력
            bool find = false;
            for (map<int, Client*>::iterator itr = ClientList.begin(); itr != ClientList.end(); itr++)
            {
                if (clientphonenumber == (*itr).second->getClientNumber())
                {
                    find = true;                                                                            //false로 들어온 find를 true로 바꿔 if(find==false)를 통과하지 못하게 한다
                    cout << "=============================================" << endl;
                    cout << "ID : C" << (*itr).second->getClientID() << endl;                               //value에 있는 해당 값들을 출력 map에서 key는 First, value는 second 자리이기 때문
                    cout << "이름 : " << (*itr).second->getClientName() << endl;
                    cout << "핸드폰번호 : " << (*itr).second->getClientNumber() << endl;
                    cout << "주소 : " << (*itr).second->getClientAddress() << endl;
                    cout << "E-mail : " << (*itr).second->getClientEmail() << endl;
                    cout << "=============================================" << endl << endl;

                    cout << "변경할 정보를 선택하세요." << endl << endl;
                    cout << "1) 이름 2) 핸드폰번호 3) 주소 4) E-mail 5) 전체변경" << endl;                    //변경할 정보를 부분적으로 선택 
                    cout << "-> "; t_3 = getBnumber();

                    if (t_3 == 1)
                    {
                        cout << "=============================================" << endl;                      //이름만 변경
                        cout << "변경할 이름 : "; cin >> clientname;
                        (*itr).second->setClientName(clientname);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_3 == 2)
                    {
                        cout << "=============================================" << endl;
                        cout << "변경할 핸드폰번호 : "; cin >> clientphonenumber;                              //핸드폰번호만 변경
                        (*itr).second->setClientNumber(clientphonenumber);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_3 == 3)
                    {
                        cout << "=============================================" << endl;        
                        cout << "변경할 주소 : "; cin >> clientaddress;                                        //주소만 변경
                        (*itr).second->setClientAddress(clientaddress);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_3 == 4)
                    {
                        cout << "=============================================" << endl;
                        cout << "변경할 E-mail : "; cin >> clientemail;                                        //이메일만 변경
                        (*itr).second->setClientEmail(clientemail);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_3 == 5)
                    {
                        cout << "=============================================" << endl;                       //변경할 정보가 많을 경우 전체 변경을 통해 한 번에 바꿔준다
                        cout << "변경할 이름 : "; cin >> clientname;
                        (*itr).second->setClientName(clientname);
                        cout << "변경할 핸드폰번호 : ";  cin >> clientphonenumber;
                        (*itr).second->setClientNumber(clientphonenumber);
                        cout << "변경할 주소 : "; cin >> clientaddress;
                        (*itr).second->setClientAddress(clientaddress);
                        cout << "변경할 E-mail : "; cin >> clientemail;
                        (*itr).second->setClientEmail(clientemail);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                }
            }
            if (find == false)                                       //for 안에서 입력되지 않은 정보를 알리기 위해 표현해주면 map 안에 들어있는 data만큼 돌기 때문에 문구가 여러번 출력됨
                                                                    //그렇기 때문에 find가 입력값이 value 안에 없을 때 find=true를 만나지 않고 그대로 find=false로 내려와 해당 문구가 출력되고, value 안에 입력값이 있을 때 
                                                                    //find true를 만나서 내려오기 때문에 find=false가 성립되지 않아 등록되지 않은 정보라는 문구가 출력되지 않는다      
            {
                cout << endl;
                cout << "=============================================" << endl;
                cout << "         등록되지 않은 정보입니다." << endl;
                cout << "=============================================" << endl << endl;
                goto gofirst_2;                                      //등록되지 않은 정보를 입력했을 때 다시 입력할 수 있도록 앞 gofirst_2레이블로 돌아가서 원하는 방법을 선택하게 함                       
            }   
        }
        break;
        }

        cout << "=============================================" << endl;
        cout << "           변경이 완료되었습니다." << endl;
        cout << "=============================================" << endl << endl;
        cout << "1) 추가 입력 2) 메뉴화면으로 돌아가기 3) 종료" << endl;    
        cout << "->"; t=getBnumber();

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

//++++++++++++++++++++++++++++++고객정보삭제+++++++++++++++++++++++++++++++++++++++++
    
void ClientManager::eraseClient(bool& back, bool& flag)
{
    gofirst_3:
    int e,e_1;
    bool repeat(true);
    while (repeat)
    {   
        if (ClientList.size() == 0)                                                     //ClientList (map)에 데이터가 존재하지 않을 때 즉 map의 사이즈가 0일때 
        {                                                                               //정보가 존재하지 않음을 알리고 메뉴화면으로 돌아가거나 정상 종료하도록 알림
            cout << endl;                                                                                   
            cout << "=============================================" << endl;
            cout << "      List에 정보가 존재하지 않습니다" << endl;
            cout << "=============================================" << endl<<endl;
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
                cout << "=============================================" << endl<<endl;
                flag = false;                                                    //main의 flag = false 조건을 만나 reuturn 0; 으로 반환되어 정상 종료
                break;
            }
            break;
        }
        
      
        else if (ClientList.size() != 0)                                                                //ClientSize가 0이 아닐 때 즉 데이터가 있을 때를 의미 eise if 꼭 표현 안 해도 실행됨
        {
            cout << "삭제할 고객 ID를 입력하세요 : C"; clientid = getBnumber();                         //고객 id를 입력받아 삭제
            bool find = false;
            for (map<int, Client*>::iterator itr = ClientList.begin(); itr != ClientList.end(); itr++)
            {
                if (clientid == (*itr).second->getClientID())
                {
                    find = true;                                                                              //false로 들어온 find를 true로 바꿔 if(find==false)를 통과하지 못하게 한다
                    // ClientList.erase(clientid = ClientList[i]->getClientID());
                    ClientList.erase(clientid);                                                              //ClientList즉 map의 key인 ClientID를 입력받아 해당 value를 삭제
                    cout << "=============================================" << endl;
                    cout << "                삭제되었습니다." << endl;
                    cout << "=============================================" << endl<<endl;
                    cout << "1) 추가 삭제하기 2) 메뉴화면으로 돌아가기 3) 종료" << endl; e_1= getBnumber();   //추가 삭제를 할지 다른 기능을 사용할지 프로그램을 종료할지 선택
                    
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
                        cout <<"=============================================" << endl;
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


int ClientManager::makeId()             //id(key)를 자동부여하는 inputClient에 사용한 함수
{
    auto key = ClientList.end();        //end()는 map의 끝 다음자리를 가리킨다
    if (ClientList.size() == 0) {       //map의 end까지 size가 0이면 return 0;
        return 0;
    }
    else {                              //size가 0이 아니라면 end가 마지막 데이터 다음 자리이기 때문에 --key 자리부터
        int id = (--key)->first;
        return ++id;                    //id하나씩 +1 해가면서 부여
    }
}

map<int, Client*> ClientManager ::getClientList()       //Ordermanger에서 사용하기 위해 선언
{
    return ClientList;
}

map<int, Client*> ClientManager::setClientList()        //Ordermanger에서 사용하기 위해 선언
{
    return ClientList;
}

//========================파일입출력===========================

ClientManager::ClientManager()                                                       //기본 생성자 : 파일 읽기

{
    ifstream file;
    file.open("clientlist.txt");                                                    //.txt로 생성된 파일 open
    if (!file.fail()) {                                                             //파일이 있으면 작업
        while (!file.eof()) {                                                       //파일이 끝까지 갈때까지
            vector<string> row = parseCSV(file, ',');                               //한줄만 읽어
            if (row.size()) {
                int clientid = atoi(row[0].c_str());                                //int형으로 바꿔줌 stoi(row[0]) 표현 가능 string to int / auto to int
                Client* c = new Client(clientid, row[1], row[2], row[3],row[4]);
                ClientList.insert({ clientid, c });                                 //파일에서 읽어온 하나를 map에 저장
            }
        }
    }
    file.close();                                                                   

}

ClientManager::~ClientManager()                                              //기본 소멸자 : 파일 저장
{
    ofstream file;
    file.open("clientlist.txt");
    if (!file.fail()) {                                                      //파일을 열 수 없으면? 리드 온리 같은 거
        for (const auto& v : ClientList) {
            Client* c = v.second;                                            //값
            file << c->getClientID() << ", " << c->getClientName() << ", ";
            file << c->getClientNumber() << ", ";
            file << c->getClientAddress() << ", ";
            file << c->getClientEmail()<<endl;                              //한줄에 콤마로 구분하면서 들어감

        }
    }
    file.close();                                                           //파일 open했으면 닫아줘야함
}
              
                                                                 //한줄을 읽어와
vector<string> ClientManager::parseCSV(istream& file, char delimiter)
                                                                //,로 분리된 값들, 콤마로 분리
{
    stringstream ss;
    vector<string> row;
    string t = " \n\r\t";

    while (!file.eof()) {                                      //마지막 줄이 아니면 들어옴
        char c = file.get();                                  //한글자를 읽어와서
        if (c == delimiter || c == '\r' || c == '\n') {       //컴마, 줄바꿈
            if (file.peek() == '\n') file.get();             //피크는 다음 글자를 보는 것
            string s = ss.str();                             //str을 이용해서 stringstream에서 string으로 변환
            s.erase(0, s.find_first_not_of(t));              //맨 앞부터 t가 아닌 글자가 나올때까지 제거
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


Client* ClientManager::search(int id)
{
    auto it = ClientList.find(id);                                 //client가 입력한 id를 찾음 find()               
    return (it != ClientList.end()) ? ClientList[id] : nullptr;    //map값이 있으면 ClientList[id] 없으면 nullptr
}


void ClientManager::displayInfo(int id)                                 //책임중심
{
    auto it = ClientList.find(id);                                      //client가 입력한 id를 찾음 find()
    if (it != ClientList.end()) {                                       //clinetlist의 end()가 아니면 -> null이 아니면 -> 데이터가 있으면
        Client* client = it->second;                                    //value값 출력
        cout << "고객이름 : " << client->getClientName() << endl;      
        cout << "고객번호 : " << client->getClientNumber() << endl;
        cout << "고객주소 : " << client->getClientAddress() << endl;
    }
}


