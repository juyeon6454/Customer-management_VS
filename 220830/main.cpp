#include "client.h"         //""���� ������� ����
#include "product.h"
#include "order.h"
#include "ordermanager.h"
#include "clientmanager.h"
#include "productmanager.h"
#include <algorithm>
#include <map>
#include <string>
#include <conio.h>

using namespace std;
extern int getBnumber();    //int ������ ���ڿ��� ������ ���� ������ ����

int main()
{
    int num;            //ù �޴� ���� ���� ����
    int a, b, c;        //�޴� ���� ���� ����
    int id = 0;         //id�� 0���� �ʱ�ȭ
    bool back = true;   //ù ȭ������ �̵��� ���� ���
    bool flag = true;   //���α׷� ���� ���Ḧ ���� ���

    ClientManager clientmanager;        //Clientmanger �Լ��� ���
    ProductManager productmanager;      //Productmanger �Լ��� ���
    OrderManager ordermanager;          //Ordermanger �Լ��� ���

    back = true;        //ù �޴� ȭ������ ���ƿ��� ���� ����� bool

input:
    if (flag == false)  //���α׷� ���� ���Ḧ ���� flag�� false�϶� return //back�� ��쿡�� while�� �ٽ� ���ƾ� �ϱ� ������ if�� ����
        return 0;

        cout << endl;
        cout << "******* ��ǰ���� ���α׷� *******" << endl << endl;
        cout << "       1. �� ���� ����" << endl;
        cout << "       2. ��ǰ ���� ����" << endl;
        cout << "       3. ���� ���� ����" << endl;
        cout << "       4. ���α׷� ����" << endl << endl;
        cout << "*********************************" << endl << endl;
        cout << "���Ͻô� ���񽺸� �������ּ��� :  ";  num = getBnumber();
        system("cls");

        switch (num)    //��ǰ���� ���α׷� ù ȭ�� �޴� ���� case 1,2,3 num
        {
           
        case 1:
aa:
            cout << endl;
            cout << "******** �� ���� ���� ********" << endl << endl;
            cout << "      1) �� ���� �Է�" << endl;
            cout << "      2) �� ���� ��ȸ" << endl;
            cout << "      3) �� ���� ����" << endl;
            cout << "      4) �� ���� ����" << endl << endl;
            cout << "********************************" << endl << endl;
            cout << "���Ͻô� ��ȣ�� �������ּ��� : ";  a = getBnumber();;
            system("cls");


            switch (a)
            {
            case 1:
                cout << endl;
                cout << "============�� ���� �Է�============" << endl<<endl;
                clientmanager.inputClient(back, flag);                          //Clientmanager�� ����� inputClient �Լ� ���
                break;
            case 2:
                cout << endl;
                cout << "============�� ���� ��ȸ============" << endl<<endl;
                clientmanager.searchClient(back, flag);                          //Clientmanager�� ����� searchClient �Լ� ���
                break;
            case 3:
                cout << endl;
                cout << "============�� ���� ����============" << endl<<endl;
                clientmanager.alterClient(back, flag);                          //Clientmanager�� ����� alterClient �Լ� ���
                break;
            case 4:
                cout << endl;
                cout << "============�� ���� ����============" << endl<< endl;
                clientmanager.eraseClient(back, flag);                          //Clientmanager�� ����� eraseClient �Լ� ���
                break;
            default:
                if (cin.fail())                                                      //���� ���� �Է°��� ���� �� �Է°��� ���õǰ� �ٽ� �Է��ϵ��� ��
                {
                    cout << endl;
                    cout << "�� ��ȣ�� �ٽ� �������ּ��� ��" << endl << endl;
                    cin.clear();
                    cin.ignore(1024, '\n');
                    goto aa;                                                    
                }
                if (num > 4)
                {
                    cout << endl;                                                       //4���� ū ���ڵ��� �� �� ��ǰ���� ���� ȭ�� ������ goto ��� aa: ���̺�� �̵�
                    cout << "�� ��ȣ�� �ٽ� �������ּ��� ��" << endl << endl;
                    goto aa;
                }

                break;
            }
            //break;
            goto input;
            //+++++++++++++++++�� switch�� �� / product ���� ++++++++++++++++++++++++++++++++++++++++++++++++++++
        case 2:
bb:
            cout << endl;
            cout << "******* ��ǰ ���� ���� ******" << endl << endl;
            cout << "      1)��ǰ ���� �Է�" << endl;
            cout << "      2)��ǰ ���� ��ȸ" << endl;
            cout << "      3)��ǰ ���� ����" << endl;
            cout << "      4)��ǰ ���� ����" << endl << endl;
            cout << "********************************" << endl << endl;
            cout << "���Ͻô� ��ȣ�� �������ּ��� : ";  b = getBnumber();;
            system("cls");
            switch (b)
            {
            case 1:
                cout << endl;
                cout << "============��ǰ ���� �Է�============" << endl;
                productmanager.inputProduct(back, flag);                          //Productmanager�� ����� inputProduct �Լ� ���
                break;
            case 2:
                cout << endl;
                cout << "============��ǰ ���� ��ȸ============" << endl;
                productmanager.searchProduct(back, flag);                          //Productmanager�� ����� searchProduct �Լ� ���
                break;
            case 3:
                cout << endl;
                cout << "============��ǰ ���� ����============" << endl;
                productmanager.alterProduct(back, flag);                          //Productmanager�� ����� alterProduct �Լ� ���
                break;
            case 4:
                cout << endl;
                cout << "============��ǰ ���� ����============" << endl;
                productmanager.eraseProduct(back, flag);                          //Productmanager�� ����� eraseProduct �Լ� ���
                break;
            default:
                if (cin.fail())                                                 //���� ���� �Է°��� ���� �� �Է°��� ���õǰ� �ٽ� �Է��ϵ��� ��
                {
                    cout << endl;
                    cout << "�� ��ȣ�� �ٽ� �������ּ��� ��" << endl << endl;
                    cin.clear();
                    cin.ignore(1024, '\n');
                    goto bb;
                }
                if (num > 4)                                                    //4���� ū ���ڵ��� �� �� ��ǰ���� ���� ȭ�� ������ goto ��� bb: ���̺�� �̵�
                {
                    cout << endl;
                    cout << "�� ��ȣ�� �ٽ� �������ּ��� ��" << endl << endl;
                    goto bb;                                                    //bb���̺�� �̵�
                }

                break;                                                          //switch�� ��������
            }
            goto input;                                                         //input���̺�� �̵� ù �޴� ȭ������ �̵�

            //+++++++++++++++++��ǰ switch �� / order ���� +++++++++++++++++++++++++++++++++++++++++++++
        case 3:
 cc:
            cout << endl;
            ordermanager.organizeOrderList(clientmanager, productmanager);
            cout << "******* ���� ���� ���� *******" << endl << endl;
            cout << "      1)��ǰ �ֹ�" << endl;
            //��������, �� ����(��ȭ��ȣ), ��ǰ����(ID)
            cout << "      2)�ֹ� ��ȸ" << endl;
            cout << "      3)�ֹ� ����" << endl;
            cout << "      4)�ֹ� ���" << endl << endl;
            cout << "********************************" << endl << endl;
            cout << "���Ͻô� ��ȣ�� �������ּ��� : ";  c = getBnumber();;
            system("cls");
            switch (c)
            {
            case 1:
                cout << endl;
                cout << "============��ǰ �ֹ�============" << endl;
                ordermanager.inputOrder(back,flag, clientmanager, productmanager);                          //Ordermanager�� ����� inputOrder �Լ� ���
                break;
            case 2:
                cout << endl;
                cout << "============�ֹ� ��ȸ============" << endl;
                ordermanager.searchOrder(back, flag, clientmanager, productmanager);                         //Ordermanager�� ����� searchOrder �Լ� ���
                break;
            case 3:
                cout << endl;
                cout << "============�ֹ� ����============" << endl;
                ordermanager.alterOrder(back, flag, clientmanager, productmanager);                          //Ordermanager�� ����� alterOrder �Լ� ���
                break;
            case 4:
                cout << endl;
                cout << "============�ֹ� ���============" << endl;
                ordermanager.eraseOrder(back, flag, clientmanager, productmanager);                          //Ordermanager�� ����� eraseOrder �Լ� ���
                break;
            default:
                if (cin.fail())                                            
                {
                    cout << endl;
                    cout << "�� ��ȣ�� �ٽ� �������ּ��� ��" << endl << endl;
                    cin.clear();                                                //���� ���� �Է°��� ���� �� �Է°��� ���õǰ� �ٽ� �Է��ϵ��� ��
                    cin.ignore(1024, '\n');
                    goto cc;
                }
                if (num > 4)
                {
                    cout << endl;
                    cout << "�� ��ȣ�� �ٽ� �������ּ��� ��" << endl << endl;   //4���� ū ���ڵ��� �� �� ��ǰ���� ���� ȭ�� ������ goto ��� cc: ���̺�� �̵�
                    goto cc;
                }

                break;
            }

           // break;
            goto input;

        case 4://���α׷� ����
            cout << endl;
            cout << "==========================" << endl;
            cout << "���α׷��� ����Ǿ����ϴ�." << endl;
            cout << "==========================" << endl;
            return 0;

        default://5�̻��� ���� ������ ó������ ���ư�
            if (cin.fail())//���� ���� �Է°��� ���� �� �ٽ� �Է��϶�� �˸�
            {
                cout << endl;
                cout << "�� ��ȣ�� �ٽ� �������ּ��� ��" << endl << endl;     //���� ���� �Է°��� ���� �� �Է°��� ���õǰ� �ٽ� �Է��ϵ��� ��
                cin.clear();
                cin.ignore(1024, '\n');
                goto input;
            }
            if (num > 4)                                                     //4���� ū ���ڵ��� �� �� ��ǰ���� ���� ȭ�� ������ goto ��� cc: ���̺�� �̵�
            {
                cout << endl;
                cout << "�� ��ȣ�� �ٽ� �������ּ��� ��" << endl << endl;
                goto input;
            }
        
            break;
        }
 

    return 0;
}


int getBnumber()                                //int ������ ���ڿ��� ������ ���� ������ ���� ���ڸ� ���� �� �ֵ�����
{
    int n, i = 0;
    char ch, str[128];                          //���ڿ� �迭 �ڸ�
    while (1) {
        do {                                    
            ch = _getch();                      //�ѱ��ھ� �Է� �޴� �Լ�
            if (ch == '\r')                     //�ٹٲ� ������ ���ڰ�
            {
                cout << endl;
                goto END;
            }
            else if (ch == '\b' && i > 0)        //���ڰ� ������ �ϳ��� ����
            {
                cout << "\b \b";
                i--;
            }
            //else if (ch < '0' || ch > '9')     //���ڸ� ���� ���� ���� ������ �߸��� �Է��̶�� ��µ�
            //{
            //    cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���." << endl;
            //    i = 0;
            //}
        } while (ch < '0' || ch > '9');
        cout << ch;
        str[i++] = ch;
    }
END:
    str[i++] = '\0';
    n = atoi(str);
    return n;

   
}
    