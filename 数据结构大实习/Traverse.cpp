#include "Traverse.h"
#include"GraphMatrix.h"
#include<queue>
#include"Timer.h"
#include<iomanip>

Traverse::Traverse(GraphMatrix& input) :isTrav(nullptr), tempGraphMatrix(input)
{
    //��ʼ����������
    isTrav = new int[tempGraphMatrix.size];

    //ѯ��ͼ�ı�����ʽ
    int flag = 0;
    cout << "-----------------" << endl
        << "��ȱ��������� 1 " << endl
        << "��ȱ��������� 2" << endl
        << "-----------------" << endl;
    cin >> flag;
    system("cls");

    //ѯ�ʿ�ʼ�ĳ��У���Ϊ�ڵ�ʹ�ã�
    string city;
    cout << "-----------------" << endl
        << "�����������ʼ�ĳ���" << endl
        << "-----------------" << endl;
    cin >> city;
    system("cls");

    //�������
    int beginCity = tempGraphMatrix.Locate(city, tempGraphMatrix.tempCity);


    //��ʼ����ʱ��
    Timer timer;
    timer.Start();


    //ѡ�������ʽ
    switch (flag)
    {
    case 1:
        DFSTraverse();
        break;

    case 2:
        BFSTraverse(beginCity);
        break;
    default:
        cout << "-------------------------------" << endl
            << "������������ֵֹ��ַ�������һ��" << endl
            << "-------------------------------" << endl;
        break;
    }

    timer.Stop();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    cout << endl << "����ʱ���� " << timer.ElapsedTime() << " ms" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

}


//������ȱ���(BFS)�ĺ��ĺ���(����һ�У�
void Traverse::BFSfunction(int i)
{
    int j;

    //ʹ��int�Ͷ���
    queue<int>Q;

    //������¼����ĳ�ʼ��
    isTrav[i] = 1;

    cout << setw(30) << tempGraphMatrix.tempCity.cities[i].m_city
        << setw(20) << tempGraphMatrix.tempCity.cities[i].m_latitude
        << setw(20) << tempGraphMatrix.tempCity.cities[i].m_longitude << endl;

    //�ڶ���ĩβ����i
    Q.push(i);

    while (!Q.empty())
    {
        i = Q.front();

        //ɾ������ͷԪ��
        Q.pop();

        for (j = 0; j < tempGraphMatrix.size; ++j)
        {
            //���֮������ϵ����û�б�������
            if (tempGraphMatrix._Graph[i][j].m_cost != MAX && !isTrav[j])
            {
                //ֱ�����
                cout << setw(30) << tempGraphMatrix.tempCity.cities[j].m_city
                    << setw(20) << tempGraphMatrix.tempCity.cities[j].m_latitude
                    << setw(20) << tempGraphMatrix.tempCity.cities[j].m_longitude << endl;

                //���Կ����������ǿ���ѹ��ģ��������ʹ��˾Ͳ����ٷ�����
                isTrav[j] = 1;

                //�������������
                Q.push(j);
            }
        }
    }
}


//������ŵĺ���
void Traverse::BFSTraverse(int pos)
{   
    int i;

    //�Ƚ�ȫ����ʼ��Ϊ0��Ȼ���𲽱���
    for (i = 0; i < tempGraphMatrix.size; ++i)
    {
        isTrav[i] = 0;  
    }
     
    //��ͨ��������
    int count = 0;

    for (i = 0; i < tempGraphMatrix.size; ++i)
    {
        if (!isTrav[(i + pos) % tempGraphMatrix.size])
        {
            //�ݹ��㷨���·���ı���
            BFSfunction((i + pos) % tempGraphMatrix.size);

            ++count;
        }
    }

    cout << "��ͨ����Ϊ  " << count << endl;
}


//DFS������ȱ������õڶ����ַ�ʽʵ�ֱ���
void Traverse::DFSfunction(int i)
{
    //��ʼ������Ϊ1�����ʹ���
    isTrav[i] = 1;
    cout << setw(30) << tempGraphMatrix.tempCity.cities[i].m_city
        << setw(20) << tempGraphMatrix.tempCity.cities[i].m_latitude
        << setw(20) << tempGraphMatrix.tempCity.cities[i].m_longitude << endl;

    //�ӵ�0�����㿪ʼ�жϵ����һ��
    for (int j = 0; j < tempGraphMatrix.tempCity.size; j++)
    {
        //�������i������j��·������jδ���ʣ�����еݹ�
        if (tempGraphMatrix._Graph[i][j].m_cost != MAX && !isTrav[j])
        {
            DFSfunction(j);
        }
    }
}

//���ú���
void Traverse::DFSTraverse()
{
    //��ʼ���������ж��㶼�趨Ϊδ���ʹ�
    for (int i = 0; i < tempGraphMatrix.tempCity.size; i++)
    {
        isTrav[i] = 0;
    }

    //��ͨ��������
    int count = 0;

    for (int i = 0; i < tempGraphMatrix.tempCity.size; i++)
    {
        if (!isTrav[i])
        {
            //��δ�����������DFS��������ֹδ��ͨ
            DFSfunction(i);
            ++count;
        }
    }

    cout << "��ͨ����Ϊ  " << count << endl;
}

//��򵥵���������
Traverse::~Traverse()
{
    delete[] isTrav;
}