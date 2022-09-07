#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include "product.h"
#include "productmanager.h"


int num_1;
int productid = 0;
string productname, productprice, productstock;
map<int, Product*> ProductList;
extern int getBnumber();
//�Ҹ��� �ۼ����ֱ�

//++++++++++++++++++++++++++++++��ǰ�����Է�+++++++++++++++++++++++++++++++++++++++++
void ProductManager::inputProduct(bool& back, bool& flag)       //�������Է��Լ�
{
    while (1)
    {
        int p;                                           //�� �� ����� �߰� ������ �޴� ���� ����
        cout << "��ǰ�� : "; cin >> productname; 
        cout << endl;
        cout << "��ǰ���� : "; cin >> productprice; 
        cout << endl;
        cout << "������ : "; cin >> productstock;
        cout << endl;                                   //��ǰ��, ��ǰ����, ������ �����

        int productid = makeId();                       //id(key) �ڵ����� (���� �Է��ϸ� �ߺ� ����)
        ProductList.insert(make_pair(productid, new Product(productid, productname, productprice, productstock)));  //map�� key,value��
        cout << productname << " �� ID�� [P" << productid << "] �Դϴ�." << endl<<endl;                             //������ id(key) �˸�
        cout << "����� �Ϸ�Ǿ����ϴ�." << endl << endl;
        cout << "======================================" << endl;
        cout << "1) �߰� �Է� 2) ó������ ���ư��� 3) ����" << endl;  //�� �� ����� �߰� ������ �޴� ����
        cout << "������ �޴��� �������ּ��� : "; p = getBnumber();     //�� �� ����� �߰� ������ �޴� ���� ����
        cout << endl;
        cout << endl;

        if (p > 3 || p < 0)                  //p�� 1,2,3 �̿��� ���� �޾��� �� �ٽ� �Է�
        {
            cout << "�ٽ� �Է����ּ���." << endl;
            cout << "======================================" << endl << endl;
            cout << "1) �߰� �Է� 2) �޴�ȭ������ ���ư��� 3) ����" << endl;
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
            flag = false;    //main �տ� ���ǹ��� �߰������ν� return 0�� ������ ��
            break;
        }
    }
}
//++++++++++++++++++++++++++++++��ǰ������ȸ+++++++++++++++++++++++++++++++++++++++++

void ProductManager::searchProduct(bool& back, bool& flag)  //��������ȸ
{
    while (1)
    {
        int s, s_1, s_2, s_3, num_1;

 gofirst:                                                    //break�� ������ �ʱ� ���� goto�� lable (1 �Է¹޾��� �� ���)
        cout << "1) ��ü ��� ��ȸ 2) �˻� 3)����" << endl; //��ǰ������ �� ���� ������, �˻��ؼ� ���ϴ� ������ ���� ����
        cout << "-> "; num_1 = getBnumber();   cout << endl;            //1) ��ü ��� ��ȸ 2)�˻��� ���� �Է°�
        switch (num_1)                                        //1)��ü ��� 2) �˻��� ����
        {
        case 1:                                                                                             //1)��ü ��� ��ȸ
            for (map<int, Product*>::iterator itr = ProductList.begin(); itr != ProductList.end(); itr++)  //map�� ����� ���� iterator�� ���
            {
                cout << "=======================================================================================================" << endl;
                cout << "ID : P" << (*itr).second->getProductID() << " l " << "��ǰ�� : " << (*itr).second->getProductName()
                    << " l " << "��ǰ���� : " << (*itr).second->getProductPrice() << " l " << "��ǰ��� : " << (*itr).second->getProductStock()<<endl;
                cout << "=======================================================================================================" << endl << endl;
            }                                                                                           //value�� �ִ� ������ ���� ���
            goto gofirst;                                                                               //��ü ����ϰ� �˻��� ���� �Լ��� �� ó�� ������� �ٽ� �����ϰ� ��
            break;
                    
        case 2:                                                 //�˻�

         cout << "���ϴ� ����� �����ϼ���." << endl << endl;

         cout << "1) ID�� �˻� 2) ��ǰ������ �˻�" << endl;    //���ϴ� ������� ��ȸ if�� 1,2�� �ް� ��
         cout << "-> ";  s = getBnumber();          


        if (s == 1)                                                                       //id�� �˻��ϴ� ���
        {
            cout << "=============================================" << endl << endl;
            cout << "��ǰ�� ID�� �Է��ϼ��� : P";                                                            //P�� ID���� product�� ��ȣ��� ���� �����ϱ� ���� �־��� client�� C, order�� R
            productid= getBnumber();                                                                          //id�� �Է¹���
            bool find = false;                                                                                //���� ������ �Է����� �� ��ϵ��� ���� ������� ���� �˷��ֱ� ����
            for (map<int, Product*>::iterator itr = ProductList.begin(); itr != ProductList.end(); itr++)     //map���� ���ۺ��� end()�� �ƴҶ����� map���� end�� �������� �ִ� �� ������ �ǹ��ϱ� ������
                                                                                                              //end�� �ƴҶ������� ���� ���� ���� �ǹ��Ѵ�
            {
                if (productid == (*itr).second->getProductID())                                  //id�� �Է��� ���� �ִ� value�� �����͸� ���
                {
                    cout << "ID : P" << (*itr).second->getProductID() << "]" << endl; 
                    cout << "�̸� : " << (*itr).second->getProductName() << endl;
                    cout << "�ڵ�����ȣ : " << (*itr).second->getProductPrice() << endl;
                    cout << "������ : " << (*itr).second->getProductStock() << endl << endl;
                    find = true;                                                                   //value�� �ִ� �ش� ������ ��� map���� key�� First, value�� second �ڸ��̱� ����
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
            cout << "1) �߰� ��ȸ 2) ùȭ������ ���ư��� 3) ����" << endl<<endl;
            cout << "-> ";  s_1 = getBnumber();          //�� �� ��ȸ �� �߰��� �����ϴ� �޴� ���� ���� (if �� if)


            if (s_1 > 3 || s_1 < 0)     //s_1�� 1,2,3 �̿��� ���� �޾��� �� �ٽ� �Է� 
            {
                cout << "�ٽ� �Է����ּ���." << endl;
                cout << "1) �ٽ� ��ȸ�ϱ� 2) �޴�ȭ������ ���ư��� 3) ����" << endl;
                cout << "-> ";  s_1 = getBnumber();
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
            }                       //1�� �ԷµǾ��� �� break�� ������ �ʰ� �Լ��� �� ������ ���ư��� ���� �������� gofirst: ���̺��� ����
        }

        else if (s == 2)                                                                                        //��ǰ������ ��ȸ�ϴ� �κ�
        {
            cout << "=============================================" << endl;
            cout << "��ȸ�� ��ǰ���� �Է��ϼ��� : ";  cin >> productname;
            bool find = false;                                                                                  //��ϵ��� ���� ������ �Է����� �� ����ϱ� ����
            for (map<int, Product*>::iterator itr = ProductList.begin(); itr != ProductList.end(); itr++)          //map���� ���ۺ��� end()�� �ƴҶ�����      
                                                                                                                   //map���� end�� �������� �ִ� �� ������ �ǹ��ϱ� ������ end�� �ƴҶ������� ���� ���� ���� �ǹ��Ѵ�
            {
                if (productname == (*itr).second->getProductName())                                                //id�� �Է��� ���� �ִ� value�� �����͸� ���
                {
                    cout << "=============================================" << endl << endl;
                    cout << "ID : P" << (*itr).second->getProductID() << "]" << endl;
                    cout << "��ǰ�� : " << (*itr).second->getProductName() << endl;
                    cout << "��ǰ���� : " << (*itr).second->getProductPrice() << endl;
                    cout << "������ : " << (*itr).second->getProductStock() << endl << endl;
                    cout << "=============================================" << endl;
                                                                                                //value�� �ִ� �ش� ������ ��� map���� key�� First, value�� second �ڸ��̱� ����
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
            if (s_2 == 1)                       
            {
                goto gofirst;   //��ϵ��� ���� ������ �Է����� �� �ٽ� �Է��� �� �ֵ��� �� gofirst_2���̺�� ���ư��� ���ϴ� ����� �����ϰ� ��      
            }                   //1�� �ԷµǾ��� ��(if���� �ƹ��͵� �ɸ��� �ʰ� ������)  break�� ������ �ʰ� �Լ��� �� ������ ���ư��� ���� �������� gofirst: ���̺��� ����
        }//switch��
        }//if��
        break;
    }//while��
}//�Լ�

//++++++++++++++++++++++++++++++��ǰ��������+++++++++++++++++++++++++++++++++++++++++

void ProductManager::alterProduct(bool& back, bool& flag)//��ǰ��������
{
    int t, t_1, t_2, t_3;

    while (1)
    {
gofirst_2:
        cout << "���ϴ� ����� �����ϼ���." << endl << endl;

        cout << "1) ID�� �˻� 2) ��ǰ������ �˻�" << endl;
        cout << "-> "; t = getBnumber();      //id,�̸�,��ȣ�� �����ؼ� ���� ã��, �� ������ ����


        switch (t)// ID, �̸�, �ڵ�����ȣ ���� ���� switch
        {

        case 1:
        {
            cout << endl;
            cout << "��ǰ ID�� �Է��ϼ��� : P"; productid = getBnumber();//cin>>clientid�� ����� �� int���̱� ������ ���� �Է½� ����
            cout << endl;

            bool find = false;                                                                              //bool�� fine�� false�� ����
            for (map<int, Product*>::iterator itr = ProductList.begin(); itr != ProductList.end(); itr++)
            {
                if (productid == (*itr).second->getProductID())
                {
                    find = true;                                                                            //false�� ���� find�� true�� �ٲ� if(find==false)�� ������� ���ϰ� �Ѵ�
                    cout << "=============================================" << endl;
                    cout << "ID : P" << (*itr).second->getProductID() << endl;                               //value�� �ִ� �ش� ������ ��� map���� key�� First, value�� second �ڸ��̱� ����
                    cout << "��ǰ��  : " << (*itr).second->getProductName() << endl;
                    cout << "��ǰ����  : " << (*itr).second->getProductPrice() << endl;
                    cout << "������  : " << (*itr).second->getProductStock() << endl;
                    cout << "=============================================" << endl << endl;

                    cout << "������ ������ �����ϼ���." << endl << endl;
                    cout <<  "1) ��ǰ�� 2) ��ǰ���� 3) ������ 4) ��ü����" << endl;                      //������ ������ �κ������� ���� 
                    cout << "-> "; t_1 = getBnumber();

                    if (t_1 == 1)
                    {
                        cout << "=============================================" << endl;                    //��ǰ�� ����
                        cout << "������ ��ǰ��  : ";
                        cin >> productname;
                        (*itr).second->setProductName(productname);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_1 == 2)
                    {
                        cout << "=============================================" << endl;                    //��ǰ���ݸ� ����
                        cout << "������ ��ǰ����  : ";
                        cin >> productprice;
                        (*itr).second->setProductPrice(productprice);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_1 == 3)
                    {
                        cout << "=============================================" << endl;
                        cout << "������ ������  : ";                                                       //�������� ����
                        cin >> productstock;
                        (*itr).second->setProductStock(productstock);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_1 == 4)                                                                  //������ ������ ���� ��� ��ü ������ ���� �� ���� �ٲ��ش�
                    {
                        cout << "=============================================" << endl;
                        cout << "������ ��ǰ�� : ";
                        cin >> productname;
                        (*itr).second->setProductName(productname);
                        cout << "������ ��ǰ���� : ";
                        cin >> productprice;
                        (*itr).second->setProductPrice(productprice);
                        cout << "������ ������ : ";
                        cin >> productstock;
                        (*itr).second->setProductStock(productstock);
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
            cout << "��ǰ���� �Է��ϼ��� : ";  cin >> productname;
            bool find = false;
            for (map<int, Product*>::iterator itr = ProductList.begin(); itr != ProductList.end(); itr++)
            {
                if (productname == (*itr).second->getProductName())                               //���� �̸����� �������� ã�� ���
                {
                    find = true;                                                                 //false�� ���� find�� true�� �ٲ� if(find==false)�� ������� ���ϰ� �Ѵ�
                    cout << "=============================================" << endl;
                    cout << "ID : P" << (*itr).second->getProductID() << endl;                   //value�� �ִ� �ش� ������ ��� map���� key�� First, value�� second �ڸ��̱� ����
                    cout << "��ǰ��  : " << (*itr).second->getProductName() << endl;
                    cout << "��ǰ����  : " << (*itr).second->getProductPrice() << endl;
                    cout << "������  : " << (*itr).second->getProductStock() << endl;
                    cout << "=============================================" << endl << endl;

                    cout << "������ ������ �����ϼ���." << endl << endl;
                    cout << "1) ��ǰ�� 2) ��ǰ���� 3) ������ 4) ��ü����" << endl;                 //������ ������ �κ������� ���� 
                    cout << "-> "; t_2 = getBnumber();

                    if (t_2 == 1)
                    {
                        cout << "=============================================" << endl;                //�̸��� ����
                        cout << "������ ��ǰ��  : ";
                        cin >> productname;
                        (*itr).second->setProductName(productname);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_2 == 2)
                    {
                        cout << "=============================================" << endl;                 //��ǰ���ݸ� ����
                        cout << "������ ��ǰ����  : ";
                        cin >> productprice;
                        (*itr).second->setProductPrice(productprice);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_2 == 3)
                    {
                        cout << "=============================================" << endl;
                        cout << "������ ������  : ";                                                   //�ּҸ� ����
                        cin >> productstock;
                        (*itr).second->setProductStock(productstock);
                        cout << "=============================================" << endl;
                        cout << endl;
                    }
                    else if (t_2 == 4)                                                                  //������ ������ ���� ��� ��ü ������ ���� �� ���� �ٲ��ش�
                    {
                        cout << "=============================================" << endl;
                        cout << "������ ��ǰ�� : ";
                        cin >> productname;
                        (*itr).second->setProductName(productname);
                        cout << "������ ��ǰ���� : ";
                        cin >> productprice;
                        (*itr).second->setProductPrice(productprice);
                        cout << "������ ������ : ";
                        cin >> productstock;
                        (*itr).second->setProductStock(productstock);
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

        }

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

void ProductManager::eraseProduct(bool& back, bool& flag)
{
gofirst_3:
    int e, e_1;
    bool repeat(true);
    while (repeat)
    {
        if (ProductList.size() == 0)                                                     //ClientList (map)�� �����Ͱ� �������� ���� �� �� map�� ����� 0�϶� 
        {                                                                               //������ �������� ������ �˸��� �޴�ȭ������ ���ư��ų� ���� �����ϵ��� �˸�
            cout << endl;
            cout << "=============================================" << endl;
            cout << "      List�� ������ �������� �ʽ��ϴ�" << endl;
            cout << "=============================================" << endl << endl;
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
                cout << "=============================================" << endl << endl;
                flag = false;                                                    //main�� flag = false ������ ���� reuturn 0; ���� ��ȯ�Ǿ� ���� ����
                break;
            }
            break;
        }


        else if (ProductList.size() != 0)                                                                //ClientSize�� 0�� �ƴ� �� �� �����Ͱ� ���� ���� �ǹ� eise if �� ǥ�� �� �ص� �����
        {
            cout << "������ �� ID�� �Է��ϼ��� : P"; productid = getBnumber();                         //��ǰ id�� �Է¹޾� ����
            bool find = false;
            for (map<int, Product*>::iterator itr = ProductList.begin(); itr != ProductList.end(); itr++)
            {
                if (productid == (*itr).second->getProductID())
                {
                    find = true;                                                                              //false�� ���� find�� true�� �ٲ� if(find==false)�� ������� ���ϰ� �Ѵ�
                    // ClientList.erase(clientid = ClientList[i]->getClientID());
                    ProductList.erase(productid);                                                              //ProductList�� map�� key�� ProductID�� �Է¹޾� �ش� value�� ����
                    cout << "=============================================" << endl;
                    cout << "                �����Ǿ����ϴ�." << endl;
                    cout << "=============================================" << endl << endl;
                    cout << "1) �߰� �����ϱ� 2) �޴�ȭ������ ���ư��� 3) ����" << endl; e_1 = getBnumber();   //�߰� ������ ���� �ٸ� ����� ������� ���α׷��� �������� ����

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
                        cout << "=============================================" << endl;
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


int ProductManager::makeId()        //id(key)�� �ڵ��ο��ϴ� inputClient�� ����� �Լ�
{
    auto key = ProductList.end();   //end()�� map�� �� �����ڸ��� ����Ų��
    if (ProductList.size() == 0) {  //map�� end���� size�� 0�̸� return 0;
        return 0;
    }
    else {                           //size�� 0�� �ƴ϶�� end�� ������ ������ ���� �ڸ��̱� ������ --key �ڸ�����
        int id = (--key)->first;
        return ++id;                  //id�ϳ��� +1 �ذ��鼭 �ο�
    }
}

map<int, Product*> ProductManager::getProductList()         //Ordermanger���� ����ϱ� ���� ����

{
    return ProductList;
}

map<int, Product*> ProductManager::setProductList()         //Ordermanger���� ����ϱ� ���� ����
{
    return ProductList;
}

//========================���������===========================

ProductManager::ProductManager()                                                     //�⺻ ������ : ���� �б�
{ 
    ifstream file;
    file.open("productlist.txt");                                                     //.txt�� ������ ���� open
    if (!file.fail()) {                                                               //������ ������ �۾�
        while (!file.eof()) {                                                         //������ ������ ��������
            vector<string> row = parseCSV(file, ',');                                 //���ٸ� �о�
            if (row.size()) {
                int productid = atoi(row[0].c_str());                                 //int������ �ٲ��� stoi(row[0]) ǥ�� ���� string to int / auto to int
                Product* p = new Product(productid, row[1], row[2], row[3]);
                ProductList.insert({ productid, p });                                 //���Ͽ��� �о�� �ϳ��� map�� ����
            }
        }
    }
    file.close();

}

ProductManager::~ProductManager()                                            //�⺻ �Ҹ��� : ���� ����
{
    ofstream file;
    file.open("productlist.txt");
    if (!file.fail()) {                                                      //������ �� �� ������? ���� �¸� ���� ��
        for (const auto& v : ProductList) {
            Product* p = v.second;                                           //��
            file << p->getProductID() << ", " << p->getProductName() << ", ";
            file << p->getProductPrice() << ", ";
            file << p->getProductStock()<<endl;                              //���ٿ� �޸��� �����ϸ鼭 ��

        }
    }
    file.close();                                                           //���� open������ �ݾ������
}

vector<string> ProductManager::parseCSV(istream& file, char delimiter)
{
    stringstream ss;
    vector<string> row;
    string t = " \n\r\t";

    while (!file.eof()) {                                     //������ ���� �ƴϸ� ����
        char c = file.get();                                  //�ѱ��ڸ� �о�ͼ�
        if (c == delimiter || c == '\r' || c == '\n') {       //�ĸ�, �ٹٲ�
            if (file.peek() == '\n') file.get();;             //��ũ�� ���� ���ڸ� ���� ��
            string s = ss.str();                              //str�� �̿��ؼ� stringstream���� string���� ��ȯ
            s.erase(0, s.find_first_not_of(t));               //�� �պ��� t�� �ƴ� ���ڰ� ���ö����� ����
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

Product* ProductManager::search(int id)
{
    auto it = ProductList.find(id);                                  //client�� �Է��� id�� ã�� find()        
    return (it != ProductList.end()) ? ProductList[id] : nullptr;    //map���� ������ ClientList[id] ������ nullptr
}


void ProductManager::displayInfo(int id)                                //å���߽�
{
    auto it = ProductList.find(id);                                      //product�� �Է��� id�� ã�� find()
    if(it != ProductList.end()) {                                        //productlist�� end()�� �ƴϸ� -> null�� �ƴϸ� -> �����Ͱ� ������
        Product* product = it->second;                                   //value�� ���
        cout << "��ǰ�� : " << product->getProductName() << endl;
        cout << "��ǰ���� : " << product->getProductPrice() << endl;
        cout << "��ǰ��� : " << product->getProductStock() << endl;
       
    }
}