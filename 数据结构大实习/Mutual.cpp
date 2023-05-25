#include "Mutual.h"
#include"City.h"
#include"Route.h"
#include"ShortestPath.h"
#include"Traverse.h"
#include"Timer.h"
#include<Windows.h>

Mutual::Mutual()
{
    //�������ļ�ʱ��
    Timer timer;
    timer.Start();

    //�½�һ��City��,���Զ���ȡ�ļ�
    City _City;


    //�½�һ��Route�࣬���Զ���ȡ�ļ�
    Route _Route;


    //�½�һ��GraphMatrix���Զ��ʹ���ͼ
    GraphMatrix _GraphMatrix(_City, _Route);

    //ֹͣȻ�����ʱ��
    timer.Stop();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    cout << "��ȡ�����ļ��������ڽӾ����ʱ��Ϊ " << timer.ElapsedTime() << " ms" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    
    //��ͼ�ı�������С·��������ģʽ��ѡ��
    string mode;
    cout << "��ѡ��ģʽ" << endl 
        << "--------------------------------------------" << endl
        << "����  ��������  ����ͼ�ı���" << endl 
        << "����  ����̡�  �����������·���ļ��������" << endl 
        << "--------------------------------------------" << endl;
    cin >> mode;
    system("cls");

    if (mode == "���")
    {
        //�½�һ��shortestPath�������ڲ���ѯ�ʳ����غ�Ŀ�ĵأ�Ȼ����ѡ��������ʱ��/���룩��֮�������Ļ�ϴ�ӡ·��
        ShortestPath _ShortestPath(_GraphMatrix);
    }
    else if(mode=="����")
    {
        //�½�һ��Traverse�࣬���ڲ���ѯ�ʱ���Ҫ��ͱ�����ʼ����
        Traverse _Traverse(_GraphMatrix);
    }
    else
    {
        cout << "ģʽ�������" << endl;
        exit(0);
    }
}