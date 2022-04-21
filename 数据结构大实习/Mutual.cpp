#include "Mutual.h"
#include"City.h"
#include"Route.h"
#include"GraphMatrix.h"
#include"ShortestPath.h"

Mutual::Mutual()
{
    //�½�һ��City��,���Զ���ȡ�ļ�
    City _City;

    //�½�һ��Route�࣬���Զ���ȡ�ļ�
    Route _Route;

    //�½�һ��GraphMatrix���Զ��ʹ���ͼ
    GraphMatrix _GraphMatrix(_City, _Route);

    //��ͼ�ı�������С·��������ģʽ��ѡ��
    string mode;
    cout << "��ѡ��ģʽ" << endl << "����  ��������  ����ͼ�ı���" << endl << "���� ����̡�  �����������·���ļ��������" << endl;
    cin >> mode;

    if (mode == "���")
    {
        //�½�һ��shortestPath�������ڲ���ѯ�ʳ����غ�Ŀ�ĵأ�Ȼ����ѡ��������ʱ��/���룩��֮�������Ļ�ϴ�ӡ·��
        ShortestPath _ShortestPath(_GraphMatrix);
    }
    else
    {

    }

}