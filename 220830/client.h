#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <iostream>


using namespace std;

class Client {
public:
    Client(int clientID, string clientName, string clientNumber, string clientAddress, string clientEmail);
    //Client(string = "", string = "", string = "");

    int getClientID()const;             //client�� ID�� �޾ƿ�
    void setClientID(int&);             //client�� ID�� ����
    string getClientName() const;       //�̸��� �޾ƿ� (get)
    void setClientName(string&);        //�̸� ����� ��� (set)
    string getClientNumber() const;     //client�� �ڵ�����ȣ�� �޾ƿ� (get)
    void setClientNumber(string&);      //client�� �ڵ�����ȣ�� ����� ��� (set)
    string getClientAddress() const;    //client�� �ּҸ� �޾ƿ� (get)
    void setClientAddress(string&);     //client�� �ּҸ� ����� ��� (set)
    string getClientEmail() const;      //client�� �̸����� �޾ƿ� (get)
    void setClientEmail(string&);       //client�� �̸����� ����� ��� (set)

private:
    int m_clientID;
    string m_clientName;
    string m_clientNumber;
    string m_clientAddress;
    string m_clientEmail;               //����

};
#endif          // __CLIENT_H