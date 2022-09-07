#ifndef __CLIENTMANAGER_H__
#define __CLIENTMANAGER_H__

#include <map>
#include <vector>
#include "client.h"

using namespace std;

class ClientManager {
public:

    ClientManager();
    ~ClientManager();
    
    void inputClient(bool&, bool&);
    void searchClient(bool&, bool&);
    void alterClient(bool&, bool&);
    void eraseClient(bool&, bool&);
    int makeId();
    vector<string> parseCSV(istream&, char);
    Client* search(int);
    void displayInfo(int);

    map<int, Client*> getClientList();
    map<int, Client*> setClientList();

    
private:
    map<int, Client*> ClientList;
  
};

#endif			// __CLIENT_MANAGER_H__
