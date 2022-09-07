#include "client.h"

#include <iostream>

using namespace std;

Client::Client(int clientID, string clientName, string clientNumber, string clientAddress, string clientEmail)
    : m_clientID(clientID), m_clientName(clientName), m_clientNumber(clientNumber), m_clientAddress(clientAddress), m_clientEmail(clientEmail)
{
}

int Client::getClientID()const
{
    return m_clientID;
}

void Client::setClientID(int& clientID)
{
    m_clientID = clientID;
}


string Client::getClientName() const
{
    return m_clientName;
}

void Client::setClientName(string& clientName)
{
    m_clientName = clientName;
}

string Client::getClientNumber() const
{
    return m_clientNumber;
}

void Client::setClientNumber(string& clientNumber)
{
    m_clientNumber = clientNumber;
}

string Client::getClientAddress() const
{
    return m_clientAddress;
}

void Client::setClientAddress(string& clientAddress)
{
    m_clientAddress = clientAddress;
}

string Client::getClientEmail() const
{
    return m_clientEmail;
}

void Client::setClientEmail(string& clientEmail)
{
    m_clientEmail = clientEmail;
}