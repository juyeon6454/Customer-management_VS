#ifndef __CLIENTMANAGER_H__
#define __CLIENTMANAGER_H__

#include <map>
#include <vector>
#include "client.h"

using namespace std;

class ClientManager {
public:

    ClientManager();                        //������ (���������)
    ~ClientManager();                      //�Ҹ��� (���������)
    
    void inputClient(bool&, bool&);
    void searchClient(bool&, bool&);
    void alterClient(bool&, bool&);
    void eraseClient(bool&, bool&);             //client ������ �Է�, ��ȸ, ����, �����ϴ� �Լ� ����
    int makeId();                               //id �ڵ��ο� �Լ� ����
    vector<string> parseCSV(istream&, char);    //���� ����½� vector���
    Client* search(int);                        //å�� �߽����� client�� ���� ��������
    void displayInfo(int);

    map<int, Client*> getClientList();          //client list�� �ִ� ������ map�� ����� ��������
    map<int, Client*> setClientList();

    
private:
    map<int, Client*> ClientList;               //map�� ����ؼ� ClientList�� ������ �����ϰ� �о��
  
};

#endif			// __CLIENT_MANAGER_H__
