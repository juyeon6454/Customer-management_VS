#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include<vector>
#include <ctime>
#include "order.h"
#include "ordermanager.h"
using namespace std;

int num_2;
int orderid = 0;
string purchasedate, client_name, clientphone_number,client_address, product_name;
int client_id, product_id, productcount;
map<int, Order*> OrderLIst;
//bool flag = true;
extern int getBnumber();

//++++++++++++++++++++++++++++++�ֹ������Է�+++++++++++++++++++++++++++++++++++++++++
void OrderManager::inputOrder(bool& back, bool& flag, ClientManager clientmanager, ProductManager productmanager)   
{
	//clientlist.at(i)->getID().compare(shoppinglist.at(j)->getpkclient()) == 0
    while (1)
    {
        string purchasedate = currentDateTime();
        int p;//���ż���, ����
        cout << "�ֹ���¥ : " << purchasedate<<endl;
        cout << endl; cout << "�� ID : "; client_id = getBnumber();
        cout << endl;  cout << "��ǰ ID : "; product_id = getBnumber(); cout << endl;//�̸�, ��ȣ, �ּ� �����
        cout << "���ż��� : "; productcount = getBnumber(); cout << endl;
       // cout << "���� : ";
       /* cout << "�ֹ���ȣ : "; cin >> orderid;
        cout << endl;*/
        int orderid = makeId();   //id(key) �ڵ����� (���� �Է��ϸ� �ߺ� ����)
        //string purchasedate = currentDateTime();
        OrderList.insert(make_pair (orderid, new Order(orderid,purchasedate, client_id, product_id,productcount)));//map�� key,value��
        cout << "�ֹ���ȣ�� [R" << orderid << "] �Դϴ�." << endl;//������ id(key) �˸�
        cout << "�ֹ��� �Ϸ�Ǿ����ϴ�." << endl << endl;
        cout << "======================================" << endl<<endl;
        cout << "1) �߰� �Է� 2) ó������ ���ư��� 3) ����" << endl;//�� �� ����� �߰� ������ �޴� ����
        cout << "������ �޴��� �������ּ��� : "; p = getBnumber();
       //�� �� ����� �߰� ������ �޴� ���� ����
        cout << endl;

        if (p > 3 || p < 0)//a�� 1�� �߰��Է����� ����ϵ��� �������� ��Ȳ�� ����� �ٽ� �Էµǵ��� ��
        {
            cout << "�ٽ� �Է����ּ���." << endl;
            cout << "======================================" << endl;
            cout << "1) �߰� �ֹ� 2)�޴�ȭ������ ���ư��� 3)����" << endl;
            cout << "������ �޴��� �������ּ��� : ";  p = getBnumber();
            cout << endl;
            //continue;
        }

        else if (p == 2)//a�� 3�� �ԷµǾ����� ù ȭ������ ���ư���
        {
            system("cls");//������ ȭ�� �����
            back = false;//ù ȭ������
            break;
        }

        else if (p == 3)//a�� 2�� �ԷµǾ��� �� ���α׷��� �ƿ� ��������
        {
            system("cls");//������ ȭ�� �����
            cout << "=============================================" << endl;
            cout << "          ���α׷��� ����Ǿ����ϴ�." << endl;
            cout << "=============================================" << endl;
            flag = false;
            break;
        }

    }
}

//++++++++++++++++++++++++++++++�ֹ�������ȸ+++++++++++++++++++++++++++++++++++++++++
void OrderManager::searchOrder(bool& back, bool& flag, ClientManager clientmanager, ProductManager productmanager)
{
    //clientmanager.getClientList()[0]->getClientName();
    while (1)
    {
        int s, s_1, s_2, s_3,num_2;

gofirst:
        cout << "1) ��ü ��� ��ȸ 2) �˻� 3)����"<<endl;
        cout << "-> ";  num_2 = getBnumber();  cout << endl;
        switch (num_2)
        {
        case 1:
            for (map<int, Order*>::iterator itr = OrderList.begin(); itr != OrderList.end(); itr++)
            {
                Order* order = itr->second;
                int cid = order->getClientID();
                int pid = order->getProductID();
                Client* client = clientmanager.search(cid);
                Product* product = productmanager.search(pid);

                cout << "=======================================================================================================" << endl;
                cout << "�ֹ���ȣ : P" << (*itr).second->getOrderID() << " l " << "�ֹ��� :" << client->getClientName()
                <<  " l "  << "�ڵ�����ȣ : " << client->getClientNumber() << " l " << "�ּ� : " << client->getClientAddress()
                 << " l " <<"��ǰ�� : " << product->getProductName() << " l " <<"���ż��� : " << (*itr).second->getProductCount() << endl;
                cout << "=======================================================================================================" << endl << endl;
            }
            goto gofirst;
            break;

        case 2:
      
            cout << "���ϴ� ����� �����ϼ���." << endl << endl;

            cout << "1) ID�� �˻� 2) ���̸����� �˻� 3) �ڵ�����ȣ�� �˻�" << endl;
            cout << "-> : "; s = getBnumber();              //id,�̸�,��ȣ�� �����ϴ� ���� (��üif)
  
            if (s == 1)//id�� �˻�
            {
                cout << "=============================================" << endl << endl;
                cout << "�ֹ� ID�� �Է��ϼ��� : R"; //�ֹ� ��ȣ�� �޾Ƽ� ��ȸ
                orderid = getBnumber();                                                                             //id�� �Է¹���
                bool find = false;
                for (map<int, Order*>::iterator itr = OrderList.begin(); itr != OrderList.end(); itr++)//m��ü�� ���Ƽ�
                {
                    Order* order = itr->second;
                    int cid = order->getClientID();
                    int pid = order->getProductID();
                    Client* client = clientmanager.search(cid);
                    Product* product = productmanager.search(pid);

                    if (orderid == order->getOrderID())//�Է°��� �ִ� ���� �����͸� ���
                    {
                        cout << endl;
                        cout << "�ֹ���ȣ : R" << order->getOrderID() << endl;
                        clientmanager.displayInfo(cid);
                        productmanager.displayInfo(pid);
                        cout << "���ż��� : " << order->getProductCount() << endl<<endl;
                        find = true;
                    }
                }

                if (find == false)//for �ȿ��� �Էµ��� ���� ������ �˸��� ���� ǥ�����ָ� map �ȿ� ����ִ� data��ŭ ���� ������ ������ ������ ��µ�
                                   //�׷��� ������ find�� �Է°��� value �ȿ� ���� �� find=true�� ������ �ʰ� �״�� find=false�� ������ �ش� ������ ��µǰ�, value �ȿ� �Է°��� ���� �� 
                                   //find true�� ������ �������� ������ find=false�� �������� �ʾ� ��ϵ��� ���� ������� ������ ��µ��� �ʴ´�
                {
                    cout << "=============================================" << endl;
                    cout << "      ��ϵ��� ���� �����Դϴ�." << endl;
                }

                cout << "======================================" << endl << endl;
                cout << "1) �߰� ��ȸ 2) �޴�ȭ������ ���ư��� 3) ����" << endl<<endl;
                cout << "-> "; s_1 = getBnumber();
              //�� �� ��ȸ �� �߰��� �����ϴ� �޴� ���� ���� (if �� if)


                if (s_1 > 3 || s_1 < 0)//b�� 1�� �߰���ȸ�� ����ϵ��� �������� ��Ȳ�� ����� �ٽ� �Էµǵ��� ��
                {
                    cout << "�ٽ� �Է����ּ���." << endl;
                    cout << "1) �ٽ� ��ȸ�ϱ� 2) �޴�ȭ������ ���ư��� 3) ����" << endl;
                    cout << "-> "; s_1 = getBnumber();
                }

                else if (s_1 == 2)//b�� 2 �ԷµǾ����� ù ȭ������ ���ư���
                {
                    system("cls");//������ ȭ�� �����
                    back = false;//ù ȭ������
                    break;
                }

                else if (s_1 == 3)                                                  //s_1�� 3�� �ԷµǾ��� �� ���α׷��� ���� �����
                {
                    system("cls");                                                  //������ ȭ�� �����
                    cout << endl;
                    cout << "=============================================" << endl;
                    cout << "          ���α׷��� ����Ǿ����ϴ�." << endl;
                    cout << "=============================================" << endl;
                    flag = false;                                                    //Ż���ϸ鼭 main �պκп��� ���ǹ��� ���������ν� return 0�� ������ ��
                    break;
                }
                if (s_1 == 1)
                {
                    goto gofirst;
                }    
               //1�� �ԷµǾ��� �� break�� ������ �ʰ� �Լ��� �� ������ ���ư��� ���� �������� gofirst: ���̺��� ����
            }

            else if (s == 2)
            {
                cout << "=============================================" << endl;
                cout << "��ȸ�� �̸��� �Է��ϼ��� : "; cin >> client_name;
                bool find = false;
                for (map<int, Order*>::iterator itr = OrderList.begin(); itr != OrderList.end(); itr++)//m��ü�� ���Ƽ�
                {
                    Order* order = itr->second;
                    int cid = order->getClientID();
                    int pid = order->getProductID();
                    Client* client = clientmanager.search(cid);
                    Product* product = productmanager.search(pid);

                    if (client_name == client->getClientName())//�Է°��� �ִ� ���� �����͸� ���
                    {
                        cout << "=============================================" << endl << endl;
                        cout << "�ֹ���ȣ : R" << order->getOrderID() << endl;
                        clientmanager.displayInfo(cid);
                        productmanager.displayInfo(pid);
                        cout << "���ż��� : " << order->getProductCount() << endl;
                        cout << "=============================================" << endl;            //value�� �ִ� �ش� ������ ��� map���� key�� First, value�� second �ڸ��̱� ����
                        find = true;                                                                //false�� ���� find�� true�� �ٲ� if(find==false)�� ������� ���ϰ� �Ѵ�
                        // cout << "��ǰ��� : " << product->getProductStock() << endl;
                    }
                }

                if (find == false) //for �ȿ��� �Էµ��� ���� ������ �˸��� ���� ǥ�����ָ� map �ȿ� ����ִ� data��ŭ ���� ������ ������ ������ ��µ�
                                 //�׷��� ������ find�� �Է°��� value �ȿ� ���� �� find=true�� ������ �ʰ� �״�� find=false�� ������ �ش� ������ ��µǰ�, value �ȿ� �Է°��� ���� �� 
                                 //find true�� ������ �������� ������ find=false�� �������� �ʾ� ��ϵ��� ���� ������� ������ ��µ��� �ʴ´�
                {
                    cout << "=============================================" << endl;
                    cout << "      ��ϵ��� ���� �����Դϴ�." << endl;
                }

                cout << "1) �߰� ��ȸ 2) �޴�ȭ������ ���ư��� 3) ����" << endl;
                cout << "-> "; s_2 = getBnumber();//�� �� ��ȸ �� �߰��� �����ϴ� �޴� ���� ���� (if �� if)

                if (s_2 > 3 || s_2 < 0)
                    //s_2�� 1�� ����ϵ��� �������� ��Ȳ�� ����� �ٽ� �Է��� �� �ִ� �κ� 1�� if���ǵ鿡 �������� �ʾ�
                    //�� �ڷ� ���� goto gofirst;�� ������ �ȴ�.
                {
                    cout << endl;
                    cout << "=============================================" << endl;
                    cout << "          �ٽ� �Է����ּ���." << endl;
                    cout << "=============================================" << endl;
                    cout << "1) �ٽ� ��ȸ�ϱ� 2) �޴�ȭ������ ���ư��� 3) ����" << endl;
                    cout << "->"; s_2 = getBnumber();                                               //�ش��ϴ� �޴��� �����ϱ� �ٽ� �����ϵ��� ��
                }

                else if (s_2 == 2)              //s_2�� 2 �ԷµǾ����� ù ȭ������ ���ư���
                {
                    system("cls");              //������ ȭ�� �����
                    back = false;               //ù ȭ������ 
                    break;                      //Ż���ϸ鼭 back=true�� ������ ��
                }

                else if (s_2 == 3)
                    //s_2�� 3�� �ԷµǾ��� �� ���α׷��� ���� ����ǵ���(���� ���ᰡ �Ǿ�� �Ҹ��ڰ� ����� ���� ������� ����)
                    //exit(1)�� �����߾����� ���� ���ᰡ �����ν� �Ҹ��ڰ� ������� �ʾ� ���� ������� ���� �ʾ���
                {
                    system("cls");  //������ ȭ�� �����
                    cout << endl;
                    cout << "=============================================" << endl;
                    cout << "          ���α׷��� ����Ǿ����ϴ�." << endl;
                    cout << "=============================================" << endl;
                    flag = false;   //Ż���ϸ鼭 main �պκп��� ���ǹ��� ���������ν� return 0�� ������ ��
                    break;
                }
                if (s_2 == 1)         //if�� ���� �ʾƵ� ���ǿ� �ɸ��� �ʾ� ������ �����                                     
                {
                    goto gofirst;    //��ϵ��� ���� ������ �Է����� �� �ٽ� �Է��� �� �ֵ��� �� gofirst_2���̺�� ���ư��� ���ϴ� ����� �����ϰ� ��      
                }     
                break;//1�� �ԷµǾ��� ��(if���� �ƹ��͵� �ɸ��� �ʰ� ������)  break�� ������ �ʰ� �Լ��� �� ������ ���ư��� ���� �������� gofirst: ���̺��� ����
            }

            else if (s == 3)
            {
                cout << "��ȭ��ȣ�� �Է��ϼ��� * (-) ���� �Է� * : "; //-�ְ� ����Ǵ°� �������°ɷ� ����?
                bool find = false;
                cin >> clientphone_number;
                for (map<int, Order*>::iterator itr = OrderList.begin(); itr != OrderList.end(); itr++)//m��ü�� ���Ƽ�
                {
                    Order* order = itr->second;
                    int cid = order->getClientID();
                    int pid = order->getProductID();
                    Client* client = clientmanager.search(cid);
                    Product* product = productmanager.search(pid);

                    if (client_name == client->getClientName())//�Է°��� �ִ� ���� �����͸� ���
                    {
                        cout << "=============================================" << endl << endl;
                        cout << "�ֹ���ȣ : R" << order->getOrderID() << endl;
                        clientmanager.displayInfo(cid);
                        productmanager.displayInfo(pid);
                        cout << "���ż��� : " << order->getProductCount() << endl<<endl;
                        cout << "=============================================" << endl;
                        find = true;
                    }
                }

                if (find == false)  //for �ȿ��� �Էµ��� ���� ������ �˸��� ���� ǥ�����ָ� map �ȿ� ����ִ� data��ŭ ���� ������ ������ ������ ��µ�
                                  //�׷��� ������ find�� �Է°��� value �ȿ� ���� �� find=true�� ������ �ʰ� �״�� find=false�� ������ �ش� ������ ��µǰ�, value �ȿ� �Է°��� ���� �� 
                                  //find true�� ������ �������� ������ find=false�� �������� �ʾ� ��ϵ��� ���� ������� ������ ��µ��� �ʴ´�
                {
                    cout << "=============================================" << endl;
                    cout << "      ��ϵ��� ���� �����Դϴ�." << endl;

                }

                cout << "1) �߰� ��ȸ 2) ùȭ������ ���ư��� 3) ����" << endl;
                cout<< "-> "; s_3 = getBnumber();          //�� �� ��ȸ �� �߰��� �����ϴ� �޴� ���� ���� (if �� if)
                if (s_3 > 3 || s_3 < 0)                                              //s_3�� 1�� �߰���ȸ�� ����ϵ��� 3���� ũ�� 0���� ���� ���� �Էµ� �� ���� �ٽ� �Է��ϵ��� ��
                {
                    cout << endl;
                    cout << "==============================================" << endl;
                    cout << "   �߸� �Է��߽��ϴ�. �ٽ� �Է����ּ���." << endl;
                    cout << "==============================================" << endl;
                    cout << "1) �ٽ� ��ȸ�ϱ� 2) �޴�ȭ������ ���ư��� 3) ����" << endl;
                    s_3 = getBnumber();                                                           //�缱�� ����
                }

                else if (s_3 == 2)   //s_3�� 2 �ԷµǾ����� ù ȭ������ ���ư���
                {
                    system("cls");
                    back = false;   //ù��° �޴�ȭ������ ���ư��� ���� �Է�  (back=true;)     
                    break;
                }

                else if (s_3 == 3)  //s_3�� 3�� �ԷµǾ��� �� ���α׷��� ���� ����ǵ��� ��
                {
                    system("cls");  //������ ȭ�� ������ �ʰ�
                    cout << endl;
                    cout << "=============================================" << endl;
                    cout << "          ���α׷��� ����Ǿ����ϴ�." << endl;
                    cout << "=============================================" << endl;
                    flag = false;
                    break;
                }
                if (s_3 == 1)       //if�� ���� �ʾƵ� ���ǿ� �ɸ��� �ʾ� ������ �����                                     
                {
                    goto gofirst;   //��ϵ��� ���� ������ �Է����� �� �ٽ� �Է��� �� �ֵ��� �� gofirst_2���̺�� ���ư��� ���ϴ� ����� �����ϰ� ��      
                }                   //1�� �ԷµǾ��� ��(if���� �ƹ��͵� �ɸ��� �ʰ� ������)  break�� ������ �ʰ� �Լ��� �� ������ ���ư��� ���� �������� gofirst: ���̺��� ����
            }//ū if��
            case 3:             //�˻��ϱ� �� �޴����� ���α׷� �����ϴ� switch ����° ���� ����
            {
                system("cls");  //������ ȭ�� �����
                cout << endl;
                cout << "=============================================" << endl;
                cout << "          ���α׷��� ����Ǿ����ϴ�." << endl;
                cout << "=============================================" << endl;
                flag = false;    //Ż���ϸ鼭 main �պκп��� ���ǹ��� ���������ν� return 0�� ������ ��
                break;
            }
            if (s_2 == 1)
            {
                goto gofirst;   //��ϵ��� ���� ������ �Է����� �� �ٽ� �Է��� �� �ֵ��� �� gofirst_2���̺�� ���ư��� ���ϴ� ����� �����ϰ� ��      
            }                   //1�� �ԷµǾ��� ��(if���� �ƹ��͵� �ɸ��� �ʰ� ������)  break�� ������ �ʰ� �Լ��� �� ������ ���ư��� ���� �������� gofirst: ���̺��� ����
           
        }
        break;
    }
}
    //++++++++++++++++++++++++++++++�ֹ���������+++++++++++++++++++++++++++++++++++++++++



void OrderManager::alterOrder(bool& back, bool& flag, ClientManager clientmanager, ProductManager productmanager)
{

    int t, t_1, t_2, t_3,num_2;
   
    while(1)
    {
gofirst_2:
        cout << "���ϴ� ����� �����ϼ���." << endl << endl;
        cout << "1) �ֹ���ȣ�� �˻� 2) �� �̸����� �˻� 3) �ڵ�����ȣ�� �˻�" << endl;
        cout << "-> ";  t = getBnumber();
      
        
        switch (t)
        {

        case 1:
        {
            cout << endl;
            cout << "�ֹ���ȣ�� �Է��ϼ��� : R";  orderid = getBnumber();
            cout << endl;

            bool find = false;
            for (map<int, Order*>::iterator itr = OrderList.begin(); itr != OrderList.end(); itr++)
            {
                Order* order = itr->second;
                int cid = (*itr).second->getClientID();
                Client* client = clientmanager.getClientList()[cid];
                int pid = (*itr).second->getProductID();
                Product* product = productmanager.getProductList()[pid];
                // Product* product = productmanager.search(pid);
                if (orderid == (*itr).second->getOrderID())
                {
                    find = true;                                                                            //false�� ���� find�� true�� �ٲ� if(find==false)�� ������� ���ϰ� �Ѵ�
                    cout << "=============================================" << endl;
                    cout << "ID : R" << (*itr).second->getOrderID() << endl;
                    cout << "�̸� : " << client->getClientName() << endl;
                    cout << "�ڵ�����ȣ : " << client->getClientNumber() << endl;
                    cout << "�ּ� : " << client->getClientAddress() << endl;
                    cout << "��ǰ�� : " << product->getProductName() << endl;
                    cout << "���ż��� : " << (*itr).second->getProductCount() << endl;
                    cout << "======================================" << endl << endl;

                    cout << "������ ������ �����ϼ���" << endl << endl;
                    cout << "1) �̸� 2) �ڵ�����ȣ 3) �ּ� 4) ��ǰ�� 5) ��ǰ���� 6) ��ü����" << endl;
                    cout << "-> "; t_1 = getBnumber();

                    if (t_1 == 1)
                    {
                        cout << "=============================================" << endl;                    //�̸��� ����
                        cout << "������ �̸� : ";
                        cin >> client_name;
                        client->setClientName(client_name);
                        cout << "=============================================" << endl;
                        cout << endl;
                        cout << "********����� ����*******" << endl;

                        cout << "ID : R" << (*itr).second->getOrderID() << endl;
                        cout << "�̸� : " << client->getClientName() << endl;
                        cout << "�ڵ�����ȣ : " << client->getClientNumber() << endl;
                        cout << "�ּ� : " << client->getClientAddress() << endl;
                        cout << "��ǰ�� : " << product->getProductName() << endl;
                        cout << "���ż��� : " << (*itr).second->getProductCount() << endl;
                        cout <<  "=============================================" << endl << endl;


                    }
                    else if (t_1 == 2)
                    {
                        cout << "=============================================" << endl;                //�ڵ�����ȣ�� ����
                        cout << "������ �ڵ�����ȣ : ";
                        cin >> clientphone_number;
                        client->setClientNumber(clientphone_number);
                        cout << "=============================================" << endl;
                        cout << endl;

                    }
                    else if (t_1 == 3)
                    {
                        cout << "=============================================" << endl;
                        cout << "������ �ּ� : ";
                        cin >> client_address;
                        client->setClientAddress(client_address);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_1 == 4)
                    {
                        cout << "=============================================" << endl;
                        cout << "������ ��ǰ�� : ";
                        cin >> product_name;
                        product->setProductName(product_name);
                        cout << "=============================================" << endl;
                    }

                    else if (t_1 == 5)
                    {
                        cout << "=============================================" << endl;
                        cout << "������ ���ż��� : ";
                        cin >> productcount;
                        order->setProductCount(productcount);
                        cout << "=============================================" << endl;
                    }

                    else if (t_1 == 6)
                    {
                        cout << "=============================================" << endl;
                        cout << "������ �̸� : ";
                        cin >> client_name;
                        client->setClientName(client_name);
                        cout << "������ �ڵ�����ȣ : ";
                        cin >> clientphone_number;
                        client->setClientNumber(clientphone_number);
                        cout << "������ �ּ� : ";
                        cin >> client_address;
                        client->setClientAddress(client_address);
                        cout << "������ ��ǰ�� : ";
                        cin >> product_name;
                        product->setProductName(product_name);
                        cout << "������ ���ż��� : ";
                        cin >> productcount;
                        order->setProductCount(productcount);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }

                }

            }
            if (find == false)                                              //for �ȿ��� �Էµ��� ���� ������ �˸��� ���� ǥ�����ָ� map �ȿ� ����ִ� data��ŭ ���� ������ ������ ������ ��µ�
                                                                           //�׷��� ������ find�� �Է°��� value �ȿ� ���� �� find=true�� ������ �ʰ� �״�� find=false�� ������ �ش� ������ ��µǰ�, value �ȿ� �Է°��� ���� �� 
                                                                           //find true�� ������ �������� ������ find=false�� �������� �ʾ� ��ϵ��� ���� ������� ������ ��µ��� �ʴ´�                                                            
            {
                cout << endl;
                cout << "=============================================" << endl;
                cout << "         ��ϵ��� ���� �����Դϴ�." << endl;
                cout << "=============================================" << endl << endl;
                goto gofirst_2;                                             //��ϵ��� ���� ������ �Է����� �� �ٽ� �Է��� �� �ֵ��� �� gofirst_2���̺�� ���ư��� ���ϴ� ����� �����ϰ� ��
            }
        }
        break;

        case 2:
        {
        cout << "�� �̸��� �Է��ϼ��� : ";  cin >> client_name;
        bool find = false;
        for (map<int, Order*>::iterator itr = OrderList.begin(); itr != OrderList.end(); itr++)
        {
            Order* order = itr->second;
            int cid = (*itr).second->getClientID();
            Client* client = clientmanager.getClientList()[cid];
            int pid = (*itr).second->getProductID();
            Product* product = productmanager.getProductList()[pid];

            if (client_name == client->getClientName())
            {
                find = true;                                                                            //false�� ���� find�� true�� �ٲ� if(find==false)�� ������� ���ϰ� �Ѵ�
                cout << "=============================================" << endl;
                cout << "ID : R" << (*itr).second->getOrderID() << endl;
                cout << "�̸� : " << client->getClientName() << endl;
                cout << "�ڵ�����ȣ : " << client->getClientNumber() << endl;
                cout << "�ּ� : " << client->getClientAddress() << endl;
                cout << "��ǰ�� : " << product->getProductName() << endl;
                cout << "���ż��� : " << (*itr).second->getProductCount() << endl;
                cout << "======================================" << endl << endl;

                cout << "������ ������ �����ϼ���" << endl << endl;
                cout << "1) �̸� 2) �ڵ�����ȣ 3) �ּ� 4) ��ǰ�� 5) ��ǰ���� 6) ��ü����" << endl;
                cout << "-> "; t_2 = getBnumber();

                if (t_2 == 1)
                {
                    cout << "=============================================" << endl;                    //�̸��� ����
                    cout << "������ �̸� : ";
                    cin >> client_name;
                    client->setClientName(client_name);
                    cout << "=============================================" << endl;
                    cout << endl;
                    cout << "********����� ����*******" << endl;

                    cout << "ID : R" << (*itr).second->getOrderID() << endl;
                    cout << "�̸� : " << client->getClientName() << endl;
                    cout << "�ڵ�����ȣ : " << client->getClientNumber() << endl;
                    cout << "�ּ� : " << client->getClientAddress() << endl;
                    cout << "��ǰ�� : " << product->getProductName() << endl;
                    cout << "���ż��� : " << (*itr).second->getProductCount() << endl;
                    cout << "=============================================" << endl << endl;


                }
                else if (t_2 == 2)
                {
                    cout << "=============================================" << endl;                //�ڵ�����ȣ�� ����
                    cout << "������ �ڵ�����ȣ : ";
                    cin >> clientphone_number;
                    client->setClientNumber(clientphone_number);
                    cout << "=============================================" << endl;
                    cout << endl;

                }
                else if (t_2 == 3)
                {
                    cout << "=============================================" << endl;
                    cout << "������ �ּ� : ";
                    cin >> client_address;
                    client->setClientAddress(client_address);
                    cout << "=============================================" << endl;
                    cout << endl;
                }
                else if (t_2 == 4)
                {
                    cout << "=============================================" << endl;
                    cout << "������ ��ǰ�� : ";
                    cin >> product_name;
                    product->setProductName(product_name);
                    cout << "=============================================" << endl;
                }

                else if (t_2 == 5)
                {
                    cout << "=============================================" << endl;
                    cout << "������ ���ż��� : ";
                    cin >> productcount;
                    order->setProductCount(productcount);
                    cout << "=============================================" << endl;
                }

                else if (t_2 == 6)
                {
                    cout << "=============================================" << endl;
                    cout << "������ �̸� : ";
                    cin >> client_name;
                    client->setClientName(client_name);
                    cout << "������ �ڵ�����ȣ : ";
                    cin >> clientphone_number;
                    client->setClientNumber(clientphone_number);
                    cout << "������ �ּ� : ";
                    cin >> client_address;
                    client->setClientAddress(client_address);
                    cout << "������ ��ǰ�� : ";
                    cin >> product_name;
                    product->setProductName(product_name);
                    cout << "������ ���ż��� : ";
                    cin >> productcount;
                    order->setProductCount(productcount);
                    cout << "=============================================" << endl;
                    cout << endl;
                }

            }

        }
        if (find == false)                                              //for �ȿ��� �Էµ��� ���� ������ �˸��� ���� ǥ�����ָ� map �ȿ� ����ִ� data��ŭ ���� ������ ������ ������ ��µ�
                                                                        //�׷��� ������ find�� �Է°��� value �ȿ� ���� �� find=true�� ������ �ʰ� �״�� find=false�� ������ �ش� ������ ��µǰ�, value �ȿ� �Է°��� ���� �� 
                                                                        //find true�� ������ �������� ������ find=false�� �������� �ʾ� ��ϵ��� ���� ������� ������ ��µ��� �ʴ´�                                                            
        {
            cout << endl;
            cout << "=============================================" << endl;
            cout << "         ��ϵ��� ���� �����Դϴ�." << endl;
            cout << "=============================================" << endl << endl;
            goto gofirst_2;                                             //��ϵ��� ���� ������ �Է����� �� �ٽ� �Է��� �� �ֵ��� �� gofirst_2���̺�� ���ư��� ���ϴ� ����� �����ϰ� ��
        }
        }
        break;

        case 3:
        {
            cout << "=============================================" << endl;
            cout << "�� ��ȭ��ȣ�� �Է��ϼ��� : ";  cin >> clientphone_number;
            bool find = false;
            for (map<int, Order*>::iterator itr = OrderList.begin(); itr != OrderList.end(); itr++)
            {
                Order* order = itr->second;
                int cid = (*itr).second->getClientID();
                Client* client = clientmanager.getClientList()[cid];
                int pid = (*itr).second->getProductID();
                Product* product = productmanager.getProductList()[pid];

                if (clientphone_number == client->getClientNumber())
                   
                {
                    find = true;                                                                            //false�� ���� find�� true�� �ٲ� if(find==false)�� ������� ���ϰ� �Ѵ�
                    cout << "=============================================" << endl;
                    cout << "ID : R" << (*itr).second->getOrderID() << endl;
                    cout << "�̸� : " << client->getClientName() << endl;
                    cout << "�ڵ�����ȣ : " << client->getClientNumber() << endl;
                    cout << "�ּ� : " << client->getClientAddress() << endl;
                    cout << "��ǰ�� : " << product->getProductName() << endl;
                    cout << "���ż��� : " << (*itr).second->getProductCount() << endl;
                    cout << "======================================" << endl << endl;

                    cout << "������ ������ �����ϼ���" << endl << endl;
                    cout << "1) �̸� 2) �ڵ�����ȣ 3) �ּ� 4) ��ǰ�� 5) ��ǰ���� 6) ��ü����" << endl;
                    cout << "-> "; t_3 = getBnumber();

                    if (t_3 == 1)
                    {
                        cout << "=============================================" << endl;                    //�̸��� ����
                        cout << "������ �̸� : ";
                        cin >> client_name;
                        client->setClientName(client_name);
                        cout << "=============================================" << endl;
                        cout << endl;
                        cout << "********����� ����*******" << endl;

                        cout << "ID : R" << (*itr).second->getOrderID() << endl;
                        cout << "�̸� : " << client->getClientName() << endl;
                        cout << "�ڵ�����ȣ : " << client->getClientNumber() << endl;
                        cout << "�ּ� : " << client->getClientAddress() << endl;
                        cout << "��ǰ�� : " << product->getProductName() << endl;
                        cout << "���ż��� : " << (*itr).second->getProductCount() << endl;
                        cout << "=============================================" << endl << endl;


                    }
                    else if (t_3 == 2)
                    {
                        cout << "=============================================" << endl;                //�ڵ�����ȣ�� ����
                        cout << "������ �ڵ�����ȣ : ";
                        cin >> clientphone_number;
                        client->setClientNumber(clientphone_number);
                        cout << "=============================================" << endl;
                        cout << endl;

                    }
                    else if (t_3 == 3)
                    {
                        cout << "=============================================" << endl;
                        cout << "������ �ּ� : ";
                        cin >> client_address;
                        client->setClientAddress(client_address);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_3 == 4)
                    {
                        cout << "=============================================" << endl;
                        cout << "������ ��ǰ�� : ";
                        cin >> product_name;
                        product->setProductName(product_name);
                        cout << "=============================================" << endl;
                    }

                    else if (t_3 == 5)
                    {
                        cout << "=============================================" << endl;
                        cout << "������ ���ż��� : ";
                        cin >> productcount;
                        order->setProductCount(productcount);
                        cout << "=============================================" << endl;
                    }

                    else if (t_3 == 6)
                    {
                        cout << "=============================================" << endl;
                        cout << "������ �̸� : ";
                        cin >> client_name;
                        client->setClientName(client_name);
                        cout << "������ �ڵ�����ȣ : ";
                        cin >> clientphone_number;
                        client->setClientNumber(clientphone_number);
                        cout << "������ �ּ� : ";
                        cin >> client_address;
                        client->setClientAddress(client_address);
                        cout << "������ ��ǰ�� : ";
                        cin >> product_name;
                        product->setProductName(product_name);
                        cout << "������ ���ż��� : ";
                        cin >> productcount;
                        order->setProductCount(productcount);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }

                }

            }
            if (find == false)                                              //for �ȿ��� �Էµ��� ���� ������ �˸��� ���� ǥ�����ָ� map �ȿ� ����ִ� data��ŭ ���� ������ ������ ������ ��µ�
                                                                            //�׷��� ������ find�� �Է°��� value �ȿ� ���� �� find=true�� ������ �ʰ� �״�� find=false�� ������ �ش� ������ ��µǰ�, value �ȿ� �Է°��� ���� �� 
                                                                            //find true�� ������ �������� ������ find=false�� �������� �ʾ� ��ϵ��� ���� ������� ������ ��µ��� �ʴ´�                                                            
            {
                cout << endl;
                cout << "=============================================" << endl;
                cout << "         ��ϵ��� ���� �����Դϴ�." << endl;
                cout << "=============================================" << endl << endl;
                goto gofirst_2;                                             //��ϵ��� ���� ������ �Է����� �� �ٽ� �Է��� �� �ֵ��� �� gofirst_2���̺�� ���ư��� ���ϴ� ����� �����ϰ� ��
            }
        }//case 3 ��
        break;
        }//switch��
     

        cout << "=============================================" << endl;
        cout << "           ������ �Ϸ�Ǿ����ϴ�." << endl;
        cout << "=============================================" << endl << endl;
        cout << "1) �߰� �Է� 2) �޴�ȭ������ ���ư��� 3) ����" << endl;
        cout << "->"; t = getBnumber();

        if (t > 3 || t < 0)                                                         //t�� 1�� ���ǹ��� ����ϵ��� ���� ���� ���� ��Ȳ�� ����
        {
            cout << "=============================================" << endl;
            cout << "            �ٽ� �Է����ּ���." << endl;
            cout << "=============================================" << endl << endl;
            cout << "1) �߰� �Է� 2) �޴�ȭ������ ���ư��� 3) ����" << endl;
            t = getBnumber();;
        }

        else if (t == 2)                                                            //t�� 2 �ԷµǾ����� ù �޴� ȭ������ ���ư��� ���� ���
        {
            system("cls");                                                          //������ ȭ�� �������
            back = false;                                                           //main�� ó�� back = true�� ���� ù �޴� ȭ�� ���
            break;
        }

        else if (t == 3)                                                            //t�� 3 �ԷµǾ��� �� ���α׷� ���� ����
        {
            system("cls");                                                          //������ ȭ�� �����                              
            cout << endl;
            cout << "=============================================" << endl;
            cout << "          ���α׷��� ����Ǿ����ϴ�." << endl;
            cout << "=============================================" << endl;
            flag = false;                                                           //main�� flag = false ������ ���� reuturn 0; ���� ��ȯ�Ǿ� ���� ����
            break;
        }
        if (t == 1)                           //if�� ���� �ʾƵ� ���ǿ� �ɸ��� �ʾ� ������ �����                                     
        {
            goto gofirst_2;                  //��ϵ��� ���� ������ �Է����� �� �ٽ� �Է��� �� �ֵ��� �� gofirst_2���̺�� ���ư��� ���ϴ� ����� �����ϰ� ��      
        }
        break;
    }//while��
}


//++++++++++++++++++++++++++++++�ֹ���������+++++++++++++++++++++++++++++++++++++++++

void OrderManager::eraseOrder(bool& back, bool& flag, ClientManager clientmanager, ProductManager productmanager)
{
 gofirst_3:
    int e, e_1;
    bool repeat(true);
    while (repeat)
    {
        if (OrderList.size() == 0)
        {
            cout << endl;
            cout << "=============================================" << endl;
            cout << "      List�� ������ �������� �ʽ��ϴ�" << endl;
            cout << "=============================================" << endl << endl;
            cout << "1) �޴�ȭ������ ���ư��� 2) ����" << endl; e = getBnumber();

            if (e == 1)
            {
                system("cls");
                back = false;//ù ȭ������
                break;
            }

            if (e == 2)
            {
                system("cls");                                                  //������ ȭ�� �������
                cout << "=============================================" << endl;
                cout << "         ���α׷��� ����Ǿ����ϴ�." << endl;
                cout << "=============================================" << endl << endl;
                flag = false;                                                    //main�� flag = false ������ ���� reuturn 0; ���� ��ȯ�Ǿ� ���� ����
                break;
            }
            break;
        }


        else if (OrderList.size() != 0)
        {
            cout << "������ �ֹ���ȣ�� �Է��ϼ��� : R";  cin >> orderid;
            bool find = false;
            for (map<int, Order*>::iterator itr = OrderList.begin(); itr != OrderList.end(); itr++)
            {
                if (orderid == (*itr).second->getOrderID())
                {
                    // ClientList.erase(clientid = ClientList[i]->getClientID());
                    OrderList.erase(orderid);
                    cout << "=============================================" << endl;
                    cout << "                �����Ǿ����ϴ�." << endl;
                    cout << "=============================================" << endl << endl;
                    cout << "1) �߰� �ֹ� ����ϱ� 2) �޴�ȭ������ ���ư��� 3) ����" << endl;
                    e_1 = getBnumber();

                    if (e_1 == 2)
                    {
                        system("cls");
                        back = false;//ù ȭ������
                        repeat = false;
                        break;
                    }

                    else if (e_1 > 3 || e_1 < 0)//b�� 1�� �߰���ȸ�� ����ϵ��� �������� ��Ȳ�� ����� �ٽ� �Էµǵ��� ��
                    {
                        cout << endl;
                        cout << "=============================================" << endl;
                        cout << "            �ٽ� �Է����ּ���." << endl;
                        cout << "=============================================" << endl;
                        cout << "1) �߰� �ֹ� ����ϱ� 2) �޴�ȭ������ ���ư��� 3) ����" << endl;
                        cout << "->"; e_1 = getBnumber();
                    }

                    else if (e_1 == 3)
                    {
                        system("cls");//������ ȭ�� �����
                        cout << endl;
                        cout << "==========================" << endl;
                        cout << "���α׷��� ����Ǿ����ϴ�." << endl;
                        cout << "==========================" << endl;
                        flag = false;
                        break;
                    }
                    break;

                }//if

            }//for ��
            if (find == false)                                          //find�� �� ���ǹ��� ������� �������ν� true�� ���� �ʾұ� ������ false�� �����Ǿ� ���
            {
                cout << endl;
                cout << "=============================================" << endl;
                cout << "         ��ϵ��� ���� �����Դϴ�." << endl;
                cout << "=============================================" << endl << endl;
                goto gofirst_3;                                          //��ϵ��� ���� ������ �Է����� �� �ٽ� �Է��� �� �ֵ��� �� gofirst_3 ���̺�� ���ư��� ���ϴ� ����� �����ϰ� ��
            }

        }
        break;
    }//while��

}


int OrderManager::makeId()
{
    auto key = OrderList.end();
    if (OrderList.size() == 0) {
        return 0;
    }
    else {
        int id = (--key)->first;
        return ++id;
    }

    return 0;
}


//========================���������===========================
//
OrderManager::OrderManager()
{ 
    ifstream file; 
    file.open("orderlist.txt"); 
    if (!file.fail()) { 
        while (!file.eof()) { 
            vector<string> row = parseCSV(file, ',');
            if (row.size()) {
                int orderid = stoi(row[0]);
                int ordercid = stoi(row[2]);
                int orderpid = stoi(row[3]);
                int orderpcid = stoi(row[4]);

                Order* o = new Order(orderid, row[1], ordercid, orderpid, orderpcid);
                OrderList.insert({ orderid, o });
            } 
        } 
    }
    file.close();

}

OrderManager::~OrderManager()
{
    ofstream file;
    file.open("orderlist.txt");
    if (!file.fail()) {
        for (const auto& v : OrderList) {
            Order* o = v.second;
            file << o->getOrderID() << ", " << o->getPurchaseDate() << ", ";
            file << o->getClientID() << ", ";
            file << o->getProductID() << ", ";
            file << o->getProductCount() << endl;

        }
    }
    file.close();
}

vector<string> OrderManager::parseCSV(istream& file, char delimiter)
{
    stringstream ss;
    vector<string> row;
    string t = " \n\r\t";

    while (!file.eof()) {
        char c = file.get();
        if (c == delimiter || c == '\r' || c == '\n') {
            if (file.peek() == '\n') file.get();
            string s = ss.str();
            s.erase(0, s.find_first_not_of(t));
            s.erase(s.find_last_not_of(t) + 1);
            row.push_back(s);
            ss.str("");
            if (c != delimiter) break;
        }
        else {
            ss << c;
        }
    }
    return row;
}


string OrderManager::currentDateTime()      //��¥ �ڵ��Է�
{
    time_t now = time(0); //���� �ð��� time_t Ÿ������ ����
    struct tm tstruct;
    char buf[40];
    localtime_s(&tstruct, &now);
    strftime(buf, sizeof(buf), "%Y%m%d", &tstruct); //YYMMDD ������ ��Ʈ��
    string str = buf;

    return str.substr(2, str.size() - 1);
}

void OrderManager::displayInfo(int id)
{
    auto it = OrderList.find(id);
    if (it != OrderList.end()) {
        Order* order = it->second;
        cout << "�ֹ����� : " << order->getProductCount() << endl;

    }
}

Order* OrderManager::search(int id)
{
    auto it = OrderList.find(id);
    return (it != OrderList.end()) ? OrderList[id] : nullptr;
}


void OrderManager::organizeOrderList(ClientManager clientManager, ProductManager productManager)
{
    vector<int> veDeleteIDList;
    for (auto mapTmp : OrderList)
    {
        int iOrderId = mapTmp.second->getOrderID();
        int iClientId = mapTmp.second->getClientID();
        int iProductId = mapTmp.second->getProductID();
        if (clientManager.search(iClientId) == NULL || productManager.search(iProductId) == NULL) // ��ID �Ǵ� ��ǰID�� ��ġ�ϴ°� ���ٸ�...
            veDeleteIDList.push_back(iOrderId);
    }
    for (auto veTmp : veDeleteIDList)
    {
        OrderList.erase(veTmp);
    }
}
