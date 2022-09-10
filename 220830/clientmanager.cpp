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
extern int getBnumber();        //int���� ���ڸ� �ޱ� ���ؼ� ���

//++++++++++++++++++++++++++++++�������Է�+++++++++++++++++++++++++++++++++++++++++
void ClientManager::inputClient(bool& back, bool&flag)          //�������Է��Լ�
{
    while (1)
    {
        int p;          //�� �� ����� �߰� ������ �޴� ���� ����
        string s;       //'-'�� ���Ե� ��ȭ��ȣ�� '-'���� �����ϱ� ���� ����

        cout << "�̸� : "; cin >> clientname;
        cout << endl;
        cout << "��ȣ : "; cin >> s;
        cout << endl;
        stringstream ss(s);     
        string buffer;

        while (getline(ss, buffer, '-') ){
            clientphonenumber += buffer;            //'-'�� �ִ� buffer���� ��� ��ȣ�� ��������
        }                                           //'-'�� ���Ե� ��ȣ�� �Է¹޾����� '-'�� ���Ե��� �ʰ� ����

        cout << "�ּ� : "; cin >> clientaddress;
        cout << endl;
        cout << "E-mail : "; cin >> clientemail;
        cout << endl;                              //�̸�, ��ȣ, �ּ�, �̸��� �����

        int clientid = makeId();                   //id(key) �ڵ����� (���� �Է��ϸ� �ߺ� ����)                                                                                  //id(key) �ڵ����� (���� �Է��ϸ� �ߺ� ����)
        ClientList.insert(make_pair(clientid, new Client(clientid, clientname, clientphonenumber, clientaddress, clientemail)));    //map�� key,value�� ����
        cout << clientname << " ���� ID�� [C" << clientid << "] �Դϴ�." << endl<<endl;                                             //������ id(key)�� �� ������ �˸�
        cout << "����� �Ϸ�Ǿ����ϴ�."<<endl<<endl;
        cout << "======================================" << endl;
        cout << "1) �߰� �Է� 2) ó������ ���ư��� 3) ����"<< endl<<endl;   //�� �� ����� �߰� ������ �޴� ����
        cout << "������ �޴��� �������ּ��� : "; p = getBnumber();          //�� �� ����� �߰� ������ �޴� ���� ����
        cout << endl;
        
        if (p > 3 || p < 0)                  //p�� 1,2,3 �̿��� ���� �޾��� �� �ٽ� �Է�
        {
            cout << "�ٽ� �Է����ּ���." << endl;
            cout << "======================================" << endl<<endl;
            cout << "1) �߰� �Է� 2) �޴�ȭ������ ���ư��� 3) ����"<< endl;
            cout << "������ �޴��� �������ּ��� : "; p = getBnumber();
            cout << endl;
        }

        else if (p == 2)    //p�� 2 �ԷµǾ����� ù ȭ������ ���ư���
        {
            system("cls");  //������ ȭ�� �����
            back = false;   //ù ȭ������
            break;
        }

        else if (p == 3)    //p�� 3�� �ԷµǾ��� �� ���α׷� ���� ����
         {
             system("cls"); //������ ȭ�� �����
             cout << "=============================================" << endl;
             cout << "          ���α׷��� ����Ǿ����ϴ�." << endl;
             cout << "=============================================" << endl;
             flag= false;    //main �տ� ���ǹ��� �߰������ν� return 0�� ������ ��
             break;
         }
    }
 }

//++++++++++++++++++++++++++++++��������ȸ+++++++++++++++++++++++++++++++++++++++++

void ClientManager::searchClient(bool& back, bool& flag)    //��������ȸ
{
    while (1)
    {
        int s,s_1,s_2,s_3, num;

gofirst:                                                    //break�� ������ �ʱ� ���� goto�� lable (1 �Է¹޾��� �� ���)
        cout << "1) ��ü ��� ��ȸ 2) �˻� 3)����" << endl; //�������� �� ���� ������, �˻��ؼ� ���ϴ� ������ ���� ����
        cout << "-> "; num = getBnumber();   cout << endl;            //1) ��ü ��� ��ȸ 2)�˻��� ���� �Է°�
        switch (num)                                        //1)��ü ��� 2) �˻��� ����
        {
        case 1:                                                                                         //1)��ü ��� ��ȸ
            for (map<int, Client*>::iterator itr = ClientList.begin(); itr != ClientList.end(); itr++)  //map�� ����� ���� iterator�� ���
            {
                cout << "=======================================================================================================" << endl;
                cout << "ID : C" << (*itr).second->getClientID() << " l " << "�̸� : " << (*itr).second->getClientName()
                    << " l " << "�ڵ�����ȣ : " << (*itr).second->getClientNumber() << " l " << "�ּ� : " << (*itr).second->getClientAddress()
                    << " l " << "E-mail : " << (*itr).second->getClientEmail() << endl;
                cout << "=======================================================================================================" << endl << endl;
            }                                                                                           //value�� �ִ� ������ ���� ���
            goto gofirst;                                                                               //��ü ����ϰ� �˻��� ���� �Լ��� �� ó�� ������� �ٽ� �����ϰ� ��
            break;

        case 2:                                                                      //�˻�

            cout << "���ϴ� ����� �����ϼ���." << endl << endl;

            cout << "1) ID�� �˻� 2) �̸����� �˻� 3) �ڵ�����ȣ�� �˻�" << endl;    //���ϴ� ������� ��ȸ if�� 1,2,3�� �ް� ��
            cout << "-> ";  s = getBnumber();                                              
  

            if (s == 1)                                                                                      //id�� �˻��ϴ� ���
            {
                cout << "=============================================" << endl << endl;
                cout << "��ȸ�� �� ID�� �Է��ϼ��� : C";                                                    //C�� ID���� clinet�� ��ȣ��� ���� �����ϱ� ���� �־��� product�� P, order�� R
                clientid = getBnumber();                                                                             //id�� �Է¹���
                bool find = false;                                                                           //���� ������ �Է����� �� ��ϵ��� ���� ������� ���� �˷��ֱ� ����
                for (map<int, Client*>::iterator itr = ClientList.begin(); itr != ClientList.end(); itr++)
                                                                                                             //map���� ���ۺ��� end()�� �ƴҶ����� map���� end�� �������� �ִ� �� ������ �ǹ��ϱ� ������
                                                                                                              //end�� �ƴҶ������� ���� ���� ���� �ǹ��Ѵ�
                {
                    if (clientid == (*itr).second->getClientID())                               //id�� �Է��� ���� �ִ� value�� �����͸� ���
                    {
                        cout << endl;
                        cout << "ID : C" << (*itr).second->getClientID() << endl;
                        cout << "�̸� : " << (*itr).second->getClientName() << endl;
                        cout << "�ڵ�����ȣ : " << (*itr).second->getClientNumber() << endl;
                        cout << "�ּ� : " << (*itr).second->getClientAddress() << endl;
                        cout << "E-mail : " << (*itr).second->getClientEmail() << endl << endl;
                        find = true;
                    }                                                                           //value�� �ִ� �ش� ������ ��� map���� key�� First, value�� second �ڸ��̱� ����
                }

                if (find == false)//for �ȿ��� �Էµ��� ���� ������ �˸��� ���� ǥ�����ָ� map �ȿ� ����ִ� data��ŭ ���� ������ ������ ������ ��µ�
                                   //�׷��� ������ find�� �Է°��� value �ȿ� ���� �� find=true�� ������ �ʰ� �״�� find=false�� ������ �ش� ������ ��µǰ�, value �ȿ� �Է°��� ���� �� 
                                   //find true�� ������ �������� ������ find=false�� �������� �ʾ� ��ϵ��� ���� ������� ������ ��µ��� �ʴ´�
                {
                    cout << "=============================================" << endl;
                    cout << "      ��ϵ��� ���� �����Դϴ�." << endl;
                }
            
                cout << "=============================================" << endl << endl;
                cout << "1) �߰� ��ȸ 2) �޴�ȭ������ ���ư��� 3) ����" << endl<<endl;
                cout << "-> "; s_1 = getBnumber();      //�� �� ��ȸ �� �߰��� �����ϴ� �޴� ���� ����


                if (s_1 > 3 || s_1 < 0)   //s_1�� 1,2,3 �̿��� ���� �޾��� �� �ٽ� �Է� 
                {
                    cout << "�ٽ� �Է����ּ���." << endl;
                    cout << "1) �ٽ� ��ȸ�ϱ� 2) �޴�ȭ������ ���ư��� 3) ����" << endl;
                    cout << "-> "; s_1 = getBnumber();
                }

                else if (s_1 == 2)      //s_1�� 2 �ԷµǾ����� ù ȭ������ ���ư���
                {
                    system("cls");      //������ ȭ�� �����
                    back = false;       //ù ȭ������ 
                    break;              //Ż���ϸ鼭 back=true�� ������ ��
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
                }                                                          //1�� �ԷµǾ��� �� break�� ������ �ʰ� �Լ��� �� ������ ���ư��� ���� �������� gofirst: ���̺��� ����
            }



            else if (s == 2)                                                                                        //�̸����� ��ȸ�ϴ� �κ�
            {
                cout << "=============================================" << endl;
                cout << "��ȸ�� �̸��� �Է��ϼ��� : ";  cin >> clientname;
                bool find = false;                                                                                  //��ϵ��� ���� ������ �Է����� �� ����ϱ� ����
                for (map<int, Client*>::iterator itr = ClientList.begin(); itr != ClientList.end(); itr++)          //map���� ���ۺ��� end()�� �ƴҶ�����
                                                                                                                    //map���� end�� �������� �ִ� �� ������ �ǹ��ϱ� ������ end�� �ƴҶ������� ���� ���� ���� �ǹ��Ѵ�
                {
                    if (clientname == (*itr).second->getClientName())                                                //id�� �Է��� ���� �ִ� value�� �����͸� ���
                    {
                        cout << "=============================================" << endl << endl;
                        cout << "ID : C" << (*itr).second->getClientID() << endl;
                        cout << "�̸� : " << (*itr).second->getClientName() << endl;
                        cout << "�ڵ�����ȣ : " << (*itr).second->getClientNumber() << endl;
                        cout << "�ּ� : " << (*itr).second->getClientAddress() << endl;
                        cout << "E-mail : " << (*itr).second->getClientEmail() << endl << endl;
                        cout << "=============================================" << endl;            //value�� �ִ� �ش� ������ ��� map���� key�� First, value�� second �ڸ��̱� ����
                        find = true;                                                                //false�� ���� find�� true�� �ٲ� if(find==false)�� ������� ���ϰ� �Ѵ�
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
                cout << "-> "; s_2 = getBnumber();      //�� �� ��ȸ �� �߰��� �����ϴ� �޴� ���� ���� (if �� if)

                if (s_2 > 3 || s_2 < 0)
                                                                                        //s_2�� 1�� ����ϵ��� �������� ��Ȳ�� ����� �ٽ� �Է��� �� �ִ� �κ� 1�� if���ǵ鿡 �������� �ʾ�
                                                                                        //�� �ڷ� ���� goto gofirst;�� ������ �ȴ�.
                {
                    cout << endl;
                    cout <<"============================================="  << endl;
                    cout << "          �ٽ� �Է����ּ���." << endl;
                    cout << "============================================="  << endl;
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
                }                    //1�� �ԷµǾ��� ��(if���� �ƹ��͵� �ɸ��� �ʰ� ������)  break�� ������ �ʰ� �Լ��� �� ������ ���ư��� ���� �������� gofirst: ���̺��� ����
            }

            else if (s == 3)                                                                                //s�� 3�� �Է������� ��ȭ��ȣ�� ���� ��ȸ
            {
                cout << "��ȭ��ȣ�� �Է��ϼ��� * (-) ���� �Է� * : ";  cin >> clientphonenumber;
                bool find = false;
                for (map<int, Client*>::iterator itr = ClientList.begin(); itr != ClientList.end(); itr++)//map���� ���ۺ��� end()�� �ƴҶ�����
                                                                                                          //map���� end�� �������� �ִ� �� ������ �ǹ��ϱ� ������ end�� �ƴҶ������� ���� ���� ���� �ǹ�
                {
                    if (clientphonenumber == (*itr).second->getClientNumber())                          
                    {
                        cout << "=============================================" << endl << endl;
                        cout << "ID : C" << (*itr).second->getClientID() << endl;                        //�Է°��� �Է°��� �ִ� ���� �����Ͱ� ��ġ�� �� �� value�� ����Ѵ�
                        cout << "�̸� : " << (*itr).second->getClientName() << endl;
                        cout << "�ڵ�����ȣ : " << (*itr).second->getClientNumber() << endl;
                        cout << "�ּ� : " << (*itr).second->getClientAddress() << endl;                                                                                                               
                        cout << "E-mail : " << (*itr).second->getClientEmail() << endl << endl;
                        cout << "=============================================" << endl;
                        find = true;
                    }
                  
                    
                }
                if (find==false)  //for �ȿ��� �Էµ��� ���� ������ �˸��� ���� ǥ�����ָ� map �ȿ� ����ִ� data��ŭ ���� ������ ������ ������ ��µ�
                                   //�׷��� ������ find�� �Է°��� value �ȿ� ���� �� find=true�� ������ �ʰ� �״�� find=false�� ������ �ش� ������ ��µǰ�, value �ȿ� �Է°��� ���� �� 
                                   //find true�� ������ �������� ������ find=false�� �������� �ʾ� ��ϵ��� ���� ������� ������ ��µ��� �ʴ´�
                {
                    cout << "=============================================" << endl;
                    cout << "      ��ϵ��� ���� �����Դϴ�." << endl;
                    
                }
          
                cout << "1) �߰� ��ȸ 2) ùȭ������ ���ư��� 3) ����" << endl;
                cout << "-> "; s_3 = getBnumber();                                               //�� �� ��ȸ �� �߰��� �����ϴ� �޴� ���� ����
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
        }//switch
        break;
    }//while
 }//�Լ�

 //++++++++++++++++++++++++++++++����������+++++++++++++++++++++++++++++++++++++++++

void ClientManager::alterClient(bool& back, bool& flag)//����������
{

    int t, t_1, t_2, t_3;

    while (1)
    {
gofirst_2:
        cout << "���ϴ� ����� �����ϼ���." << endl << endl;

        cout << "1) ID�� �˻� 2) �̸����� �˻� 3) �ڵ�����ȣ�� �˻�" << endl;
        cout << "-> "; t = getBnumber();      //id,�̸�,��ȣ�� �����ؼ� ���� ã��, �� ������ ����

        switch (t)      //id,�̸�,��ȣ�� �����ؼ� ���� ã��, �� ������ ����
        {

        case 1:
        {
            cout << endl;
            cout << "�� ID�� �Է��ϼ��� : C"; clientid = getBnumber();//cin>>clientid�� ����� �� int���̱� ������ ���� �Է½� ����
            cout << endl;
          
            bool find = false;                                                                              //bool�� fine�� false�� ����
            for (map<int, Client*>::iterator itr = ClientList.begin(); itr != ClientList.end(); itr++)
            {
                if (clientid == (*itr).second->getClientID())
                {
                    find = true;                                                                            //false�� ���� find�� true�� �ٲ� if(find==false)�� ������� ���ϰ� �Ѵ�
                    cout << "=============================================" << endl;
                    cout << "ID : C" << (*itr).second->getClientID() << endl;                               //value�� �ִ� �ش� ������ ��� map���� key�� First, value�� second �ڸ��̱� ����
                    cout << "�̸� : " << (*itr).second->getClientName() << endl;
                    cout << "�ڵ�����ȣ : " << (*itr).second->getClientNumber() << endl;
                    cout << "�ּ� : " << (*itr).second->getClientAddress() << endl;
                    cout << "E-mail : " << (*itr).second->getClientEmail() <<  endl;
                    cout << "=============================================" << endl<<endl;
                
                    cout << "������ ������ �����ϼ���." << endl << endl;
                    cout << "1) �̸� 2) �ڵ�����ȣ 3) �ּ� 4) E-mail 5) ��ü����" << endl;                   //������ ������ �κ������� ���� 
                    cout << "-> "; t_1 = getBnumber();

                    if (t_1 == 1)
                    {
                        cout << "=============================================" << endl;                    //�̸��� ����
                        cout << "������ �̸� : ";
                        cin >> clientname;
                        (*itr).second->setClientName(clientname);
                        cout << "=============================================" << endl;                   
                        cout << endl;
                    }
                    else if (t_1 == 2)
                    {
                        cout << "=============================================" << endl;                //�ڵ�����ȣ�� ����
                        cout << "������ �ڵ�����ȣ : ";
                        cin >> clientphonenumber;
                        (*itr).second->setClientNumber(clientphonenumber);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_1 == 3)
                    {
                        cout << "=============================================" << endl;
                        cout << "������ �ּ� : ";                                                            //�ּҸ� ����
                        cin >> clientaddress;
                        (*itr).second->setClientAddress(clientaddress);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_1 == 4)
                    {
                        cout << "=============================================" << endl;
                        cout << "������ E-mail : ";                                                        //�̸��ϸ� ����
                        cin >> clientemail;
                        (*itr).second->setClientEmail(clientemail);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_1 == 5)                                                                  //������ ������ ���� ��� ��ü ������ ���� �� ���� �ٲ��ش�
                    {
                        cout << "=============================================" << endl;
                        cout << "������ �̸� : ";
                        cin >> clientname;
                        (*itr).second->setClientName(clientname);
                        cout << "������ �ڵ�����ȣ : ";
                        cin >> clientphonenumber;
                        (*itr).second->setClientNumber(clientphonenumber);
                        cout << "������ �ּ� : ";
                        cin >> clientaddress;
                        (*itr).second->setClientAddress(clientaddress);
                        cout << "������ E-mail : ";
                        cin >> clientemail;
                        (*itr).second->setClientEmail(clientemail);
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
        cout << "�� �̸��� �Է��ϼ��� : ";  cin >> clientname;
        bool find = false;
        for (map<int, Client*>::iterator itr = ClientList.begin(); itr != ClientList.end(); itr++)
        {
            if (clientname == (*itr).second->getClientName())                               //���� �̸����� �������� ã�� ���
            {
                find = true;                                                                 //false�� ���� find�� true�� �ٲ� if(find==false)�� ������� ���ϰ� �Ѵ�
                cout << "=============================================" << endl;
                cout << "ID : C" << (*itr).second->getClientID() << endl;                    //value�� �ִ� �ش� ������ ��� map���� key�� First, value�� second �ڸ��̱� ����
                cout << "�̸� : " << (*itr).second->getClientName() << endl;
                cout << "�ڵ�����ȣ : " << (*itr).second->getClientNumber() << endl;
                cout << "�ּ� : " << (*itr).second->getClientAddress() << endl;
                cout << "E-mail : " << (*itr).second->getClientEmail() << endl;
                cout << "=============================================" << endl << endl;

                cout << "������ ������ �����ϼ���." << endl << endl;
                cout << "1) �̸� 2) �ڵ�����ȣ 3) �ּ� 4) E-mail 5) ��ü����" << endl;        //������ ������ �κ������� ���� 
                cout << "-> "; t_2 = getBnumber();

                if (t_2 == 1)
                {
                    cout << "=============================================" << endl;          //�̸��� ����
                    cout << "������ �̸� : ";    
                    cin >> clientname;
                    (*itr).second->setClientName(clientname);
                    cout << "=============================================" << endl;
                    cout << endl;
                }
                else if (t_2 == 2)
                {
                    cout << "=============================================" << endl;           //�ڵ�����ȣ�� ����
                    cout << "������ �ڵ�����ȣ : ";
                    cin >> clientphonenumber;
                    (*itr).second->setClientNumber(clientphonenumber);
                    cout << "=============================================" << endl;
                    cout << endl;
                }
                else if (t_2 == 3)
                {
                    cout << "=============================================" << endl;           //�ּҸ� ����
                    cout << "������ �ּ� : ";
                    cin >> clientaddress;
                    (*itr).second->setClientAddress(clientaddress);
                    cout << "=============================================" << endl;
                    cout << endl;
                }
                else if (t_2 == 4)
                {
                    cout << "=============================================" << endl;
                    cout << "������ E-mail : ";                                                //�̸��ϸ� ����
                    cin >> clientemail;
                    (*itr).second->setClientEmail(clientemail);
                    cout << "=============================================" << endl;
                    cout << endl;
                }
                else if (t_2 == 5)
                {
                    cout << "=============================================" << endl;            //������ ������ ���� ��� ��ü ������ ���� �� ���� �ٲ��ش�
                    cout << "������ �̸� : ";
                    cin >> clientname;
                    (*itr).second->setClientName(clientname);
                    cout << "������ �ڵ�����ȣ : ";
                    cin >> clientphonenumber;
                    (*itr).second->setClientNumber(clientphonenumber);
                    cout << "������ �ּ� : ";
                    cin >> clientaddress;
                    (*itr).second->setClientAddress(clientaddress);
                    cout << "������ E-mail : ";
                    cin >> clientemail;
                    (*itr).second->setClientEmail(clientemail);
                    cout << "=============================================" << endl;
                    cout << endl;
                }

            }
        }

        if (find == false)                                           //for �ȿ��� �Էµ��� ���� ������ �˸��� ���� ǥ�����ָ� map �ȿ� ����ִ� data��ŭ ���� ������ ������ ������ ��µ�
                                                                    //�׷��� ������ find�� �Է°��� value �ȿ� ���� �� find=true�� ������ �ʰ� �״�� find=false�� ������ �ش� ������ ��µǰ�, value �ȿ� �Է°��� ���� �� 
                                                                    //find true�� ������ �������� ������ find=false�� �������� �ʾ� ��ϵ��� ���� ������� ������ ��µ��� �ʴ´�       
        {
            cout << endl;
            cout << "=============================================" << endl;
            cout << "         ��ϵ��� ���� �����Դϴ�." << endl;
            cout << "=============================================" << endl << endl;
            goto gofirst_2;                                          //��ϵ��� ���� ������ �Է����� �� �ٽ� �Է��� �� �ֵ��� �� gofirst_2���̺�� ���ư��� ���ϴ� ����� �����ϰ� ��
        }
        }
        break;
        case 3:
        {
            cout << "=============================================" << endl;                                
            cout << "�� ��ȭ��ȣ�� �Է��ϼ��� : ";  cin >> clientphonenumber;                              //���� ��ȭ��ȣ�� �������� ã�� ���
            bool find = false;
            for (map<int, Client*>::iterator itr = ClientList.begin(); itr != ClientList.end(); itr++)
            {
                if (clientphonenumber == (*itr).second->getClientNumber())
                {
                    find = true;                                                                            //false�� ���� find�� true�� �ٲ� if(find==false)�� ������� ���ϰ� �Ѵ�
                    cout << "=============================================" << endl;
                    cout << "ID : C" << (*itr).second->getClientID() << endl;                               //value�� �ִ� �ش� ������ ��� map���� key�� First, value�� second �ڸ��̱� ����
                    cout << "�̸� : " << (*itr).second->getClientName() << endl;
                    cout << "�ڵ�����ȣ : " << (*itr).second->getClientNumber() << endl;
                    cout << "�ּ� : " << (*itr).second->getClientAddress() << endl;
                    cout << "E-mail : " << (*itr).second->getClientEmail() << endl;
                    cout << "=============================================" << endl << endl;

                    cout << "������ ������ �����ϼ���." << endl << endl;
                    cout << "1) �̸� 2) �ڵ�����ȣ 3) �ּ� 4) E-mail 5) ��ü����" << endl;                    //������ ������ �κ������� ���� 
                    cout << "-> "; t_3 = getBnumber();

                    if (t_3 == 1)
                    {
                        cout << "=============================================" << endl;                      //�̸��� ����
                        cout << "������ �̸� : "; cin >> clientname;
                        (*itr).second->setClientName(clientname);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_3 == 2)
                    {
                        cout << "=============================================" << endl;
                        cout << "������ �ڵ�����ȣ : "; cin >> clientphonenumber;                              //�ڵ�����ȣ�� ����
                        (*itr).second->setClientNumber(clientphonenumber);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_3 == 3)
                    {
                        cout << "=============================================" << endl;        
                        cout << "������ �ּ� : "; cin >> clientaddress;                                        //�ּҸ� ����
                        (*itr).second->setClientAddress(clientaddress);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_3 == 4)
                    {
                        cout << "=============================================" << endl;
                        cout << "������ E-mail : "; cin >> clientemail;                                        //�̸��ϸ� ����
                        (*itr).second->setClientEmail(clientemail);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_3 == 5)
                    {
                        cout << "=============================================" << endl;                       //������ ������ ���� ��� ��ü ������ ���� �� ���� �ٲ��ش�
                        cout << "������ �̸� : "; cin >> clientname;
                        (*itr).second->setClientName(clientname);
                        cout << "������ �ڵ�����ȣ : ";  cin >> clientphonenumber;
                        (*itr).second->setClientNumber(clientphonenumber);
                        cout << "������ �ּ� : "; cin >> clientaddress;
                        (*itr).second->setClientAddress(clientaddress);
                        cout << "������ E-mail : "; cin >> clientemail;
                        (*itr).second->setClientEmail(clientemail);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                }
            }
            if (find == false)                                       //for �ȿ��� �Էµ��� ���� ������ �˸��� ���� ǥ�����ָ� map �ȿ� ����ִ� data��ŭ ���� ������ ������ ������ ��µ�
                                                                    //�׷��� ������ find�� �Է°��� value �ȿ� ���� �� find=true�� ������ �ʰ� �״�� find=false�� ������ �ش� ������ ��µǰ�, value �ȿ� �Է°��� ���� �� 
                                                                    //find true�� ������ �������� ������ find=false�� �������� �ʾ� ��ϵ��� ���� ������� ������ ��µ��� �ʴ´�      
            {
                cout << endl;
                cout << "=============================================" << endl;
                cout << "         ��ϵ��� ���� �����Դϴ�." << endl;
                cout << "=============================================" << endl << endl;
                goto gofirst_2;                                      //��ϵ��� ���� ������ �Է����� �� �ٽ� �Է��� �� �ֵ��� �� gofirst_2���̺�� ���ư��� ���ϴ� ����� �����ϰ� ��                       
            }   
        }
        break;
        }

        cout << "=============================================" << endl;
        cout << "           ������ �Ϸ�Ǿ����ϴ�." << endl;
        cout << "=============================================" << endl << endl;
        cout << "1) �߰� �Է� 2) �޴�ȭ������ ���ư��� 3) ����" << endl;    
        cout << "->"; t=getBnumber();

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

//++++++++++++++++++++++++++++++����������+++++++++++++++++++++++++++++++++++++++++
    
void ClientManager::eraseClient(bool& back, bool& flag)
{
    gofirst_3:
    int e,e_1;
    bool repeat(true);
    while (repeat)
    {   
        if (ClientList.size() == 0)                                                     //ClientList (map)�� �����Ͱ� �������� ���� �� �� map�� ����� 0�϶� 
        {                                                                               //������ �������� ������ �˸��� �޴�ȭ������ ���ư��ų� ���� �����ϵ��� �˸�
            cout << endl;                                                                                   
            cout << "=============================================" << endl;
            cout << "      List�� ������ �������� �ʽ��ϴ�" << endl;
            cout << "=============================================" << endl<<endl;
            cout << "1) �޴�ȭ������ ���ư��� 2) ����" << endl; e = getBnumber(); 

            if (e == 1)                                                                         
            {                                       //e�� 1�� �� �޴�ȭ������ ���ư�
                system("cls");                      //������ ȭ�� �������
                back = false;                       //main�� ó�� back = true�� ���� ù �޴� ȭ�� ���
                break;
            }

            else if (e == 2)
            {
                system("cls");                                                  //������ ȭ�� �������
                cout << "=============================================" << endl;
                cout << "         ���α׷��� ����Ǿ����ϴ�." << endl;
                cout << "=============================================" << endl<<endl;
                flag = false;                                                    //main�� flag = false ������ ���� reuturn 0; ���� ��ȯ�Ǿ� ���� ����
                break;
            }
            break;
        }
        
      
        else if (ClientList.size() != 0)                                                                //ClientSize�� 0�� �ƴ� �� �� �����Ͱ� ���� ���� �ǹ� eise if �� ǥ�� �� �ص� �����
        {
            cout << "������ �� ID�� �Է��ϼ��� : C"; clientid = getBnumber();                         //�� id�� �Է¹޾� ����
            bool find = false;
            for (map<int, Client*>::iterator itr = ClientList.begin(); itr != ClientList.end(); itr++)
            {
                if (clientid == (*itr).second->getClientID())
                {
                    find = true;                                                                              //false�� ���� find�� true�� �ٲ� if(find==false)�� ������� ���ϰ� �Ѵ�
                    // ClientList.erase(clientid = ClientList[i]->getClientID());
                    ClientList.erase(clientid);                                                              //ClientList�� map�� key�� ClientID�� �Է¹޾� �ش� value�� ����
                    cout << "=============================================" << endl;
                    cout << "                �����Ǿ����ϴ�." << endl;
                    cout << "=============================================" << endl<<endl;
                    cout << "1) �߰� �����ϱ� 2) �޴�ȭ������ ���ư��� 3) ����" << endl; e_1= getBnumber();   //�߰� ������ ���� �ٸ� ����� ������� ���α׷��� �������� ����
                    
                    if (e_1 == 2)
                    {
                        system("cls");
                        back = false;//ù ȭ������
                        repeat = false;             //break�� if�� ���������� ������ back�� ������ �޴�ùȭ������ ���ư� �� ���� 
                        break;                      // while�� ������������ repeat�� true�϶� ����Ǵ� while�� false�� �ؼ� ������������               
                    }

                    else if (e_1 > 3 || e_1 < 0)//e_1�� 1�� ���ǹ��� ����ϵ��� �������� ��Ȳ�� ����� �߰����� ��Ȳ�� ǥ��
                    {
                        cout << endl;
                        cout << "=============================================" << endl;
                        cout << "            �ٽ� �Է����ּ���." << endl;
                        cout << "=============================================" << endl;
                        cout << "1) �߰� �����ϱ� 2) �޴�ȭ������ ���ư��� 3) ����" << endl;
                        cout << "->"; e_1 = getBnumber();
                    }

                    else if (e_1 == 3)
                    {
                        system("cls");//������ ȭ�� �����
                        cout << endl;
                        cout << "=============================================" << endl;
                        cout << "       ���α׷��� ����Ǿ����ϴ�." << endl;
                        cout <<"=============================================" << endl;
                        flag = false;                                      //main�� flag = false ������ ���� reuturn 0; ���� ��ȯ�Ǿ� ���� ����
                        break;
                    }               

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


int ClientManager::makeId()             //id(key)�� �ڵ��ο��ϴ� inputClient�� ����� �Լ�
{
    auto key = ClientList.end();        //end()�� map�� �� �����ڸ��� ����Ų��
    if (ClientList.size() == 0) {       //map�� end���� size�� 0�̸� return 0;
        return 0;
    }
    else {                              //size�� 0�� �ƴ϶�� end�� ������ ������ ���� �ڸ��̱� ������ --key �ڸ�����
        int id = (--key)->first;
        return ++id;                    //id�ϳ��� +1 �ذ��鼭 �ο�
    }
}

map<int, Client*> ClientManager ::getClientList()       //Ordermanger���� ����ϱ� ���� ����
{
    return ClientList;
}

map<int, Client*> ClientManager::setClientList()        //Ordermanger���� ����ϱ� ���� ����
{
    return ClientList;
}

//========================���������===========================

ClientManager::ClientManager()                                                       //�⺻ ������ : ���� �б�

{
    ifstream file;
    file.open("clientlist.txt");                                                    //.txt�� ������ ���� open
    if (!file.fail()) {                                                             //������ ������ �۾�
        while (!file.eof()) {                                                       //������ ������ ��������
            vector<string> row = parseCSV(file, ',');                               //���ٸ� �о�
            if (row.size()) {
                int clientid = atoi(row[0].c_str());                                //int������ �ٲ��� stoi(row[0]) ǥ�� ���� string to int / auto to int
                Client* c = new Client(clientid, row[1], row[2], row[3],row[4]);
                ClientList.insert({ clientid, c });                                 //���Ͽ��� �о�� �ϳ��� map�� ����
            }
        }
    }
    file.close();                                                                   

}

ClientManager::~ClientManager()                                              //�⺻ �Ҹ��� : ���� ����
{
    ofstream file;
    file.open("clientlist.txt");
    if (!file.fail()) {                                                      //������ �� �� ������? ���� �¸� ���� ��
        for (const auto& v : ClientList) {
            Client* c = v.second;                                            //��
            file << c->getClientID() << ", " << c->getClientName() << ", ";
            file << c->getClientNumber() << ", ";
            file << c->getClientAddress() << ", ";
            file << c->getClientEmail()<<endl;                              //���ٿ� �޸��� �����ϸ鼭 ��

        }
    }
    file.close();                                                           //���� open������ �ݾ������
}
              
                                                                 //������ �о��
vector<string> ClientManager::parseCSV(istream& file, char delimiter)
                                                                //,�� �и��� ����, �޸��� �и�
{
    stringstream ss;
    vector<string> row;
    string t = " \n\r\t";

    while (!file.eof()) {                                      //������ ���� �ƴϸ� ����
        char c = file.get();                                  //�ѱ��ڸ� �о�ͼ�
        if (c == delimiter || c == '\r' || c == '\n') {       //�ĸ�, �ٹٲ�
            if (file.peek() == '\n') file.get();             //��ũ�� ���� ���ڸ� ���� ��
            string s = ss.str();                             //str�� �̿��ؼ� stringstream���� string���� ��ȯ
            s.erase(0, s.find_first_not_of(t));              //�� �պ��� t�� �ƴ� ���ڰ� ���ö����� ����
            s.erase(s.find_last_not_of(t) + 1);
            row.push_back(s);
            ss.str("");
            if (c != delimiter) break;
        }
        else {
            ss << c;                                        //�޸��� ���ö����� ��� �߰�
        }
    }
    return row;
}


Client* ClientManager::search(int id)
{
    auto it = ClientList.find(id);                                 //client�� �Է��� id�� ã�� find()               
    return (it != ClientList.end()) ? ClientList[id] : nullptr;    //map���� ������ ClientList[id] ������ nullptr
}


void ClientManager::displayInfo(int id)                                 //å���߽�
{
    auto it = ClientList.find(id);                                      //client�� �Է��� id�� ã�� find()
    if (it != ClientList.end()) {                                       //clinetlist�� end()�� �ƴϸ� -> null�� �ƴϸ� -> �����Ͱ� ������
        Client* client = it->second;                                    //value�� ���
        cout << "���̸� : " << client->getClientName() << endl;      
        cout << "����ȣ : " << client->getClientNumber() << endl;
        cout << "���ּ� : " << client->getClientAddress() << endl;
    }
}


