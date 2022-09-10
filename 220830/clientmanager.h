#ifndef __CLIENTMANAGER_H__
#define __CLIENTMANAGER_H__

#include <map>
#include <vector>
#include "client.h"

using namespace std;

class ClientManager {
public:

    ClientManager();                        //생성자 (파일입출력)
    ~ClientManager();                      //소멸자 (파일입출력)
    
    void inputClient(bool&, bool&);
    void searchClient(bool&, bool&);
    void alterClient(bool&, bool&);
    void eraseClient(bool&, bool&);             //client 정보를 입력, 조회, 삭제, 변경하는 함수 선언
    int makeId();                               //id 자동부여 함수 선언
    vector<string> parseCSV(istream&, char);    //파일 입출력시 vector사용
    Client* search(int);                        //책임 중심으로 client의 정보 가져오기
    void displayInfo(int);

    map<int, Client*> getClientList();          //client list에 있는 정보를 map을 사용해 가져오기
    map<int, Client*> setClientList();

    
private:
    map<int, Client*> ClientList;               //map을 사용해서 ClientList에 정보를 저장하고 읽어옴
  
};

#endif			// __CLIENT_MANAGER_H__
