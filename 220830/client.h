#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <iostream>


using namespace std;

class Client {
public:
    Client(int clientID, string clientName, string clientNumber, string clientAddress, string clientEmail);
    //Client(string = "", string = "", string = "");

    int getClientID()const;             //client의 ID를 받아옴
    void setClientID(int&);             //client의 ID를 지정
    string getClientName() const;       //이름을 받아옴 (get)
    void setClientName(string&);        //이름 변경시 사용 (set)
    string getClientNumber() const;     //client의 핸드폰번호를 받아옴 (get)
    void setClientNumber(string&);      //client의 핸드폰번호를 변경시 사용 (set)
    string getClientAddress() const;    //client의 주소를 받아옴 (get)
    void setClientAddress(string&);     //client의 주소를 변경시 사용 (set)
    string getClientEmail() const;      //client의 이메일을 받아옴 (get)
    void setClientEmail(string&);       //client의 이메일을 변경시 사용 (set)

private:
    int m_clientID;
    string m_clientName;
    string m_clientNumber;
    string m_clientAddress;
    string m_clientEmail;               //변수

};
#endif          // __CLIENT_H