#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <iostream>


using namespace std;

class Client {
public:
    Client(int clientID, string clientName, string clientNumber, string clientAddress, string clientEmail);
    //Client(string = "", string = "", string = "");

    int getClientID()const;
    void setClientID(int&);
    string getClientName() const;
    void setClientName(string&);
    string getClientNumber() const;
    void setClientNumber(string&);
    string getClientAddress() const;
    void setClientAddress(string&);
    string getClientEmail() const;
    void setClientEmail(string&);

private:
    int m_clientID;
    string m_clientName;
    string m_clientNumber;
    string m_clientAddress;
    string m_clientEmail;

};
#endif          // __CLIENT_H