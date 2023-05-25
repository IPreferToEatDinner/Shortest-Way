#include "GraphMatrix.h"
#include"Route.h"

GraphMatrix::GraphMatrix(City& inputCity,Route& inputRoute) : tempCity(inputCity),tempRoute(inputRoute)
{
    this->size = inputCity.size;
    CreateMatrixGraph();
}


int GraphMatrix::Locate(string city, City& _city)
{
    for (int i = 0; i < size; i++) 
    {
        if (_city.cities[i].m_city == city)
        {
            return i;   //�ҵ����򷵻��ҵ��ó��еĵı��
        }
    }

    //����������
    cout << "-----------------" << endl
        << "���������������" << endl
        << "-----------------" << endl;
    exit(0);
}


void GraphMatrix::CreateMatrixGraph()
{

    //�ȿ��ٶ�ά���������
    _Graph = new oneGraph * [size];

    for (int i = 0; i < this->size; ++i)
    {
        //�½���ά���飬һ���½�һ��д��
        _Graph[i] = new oneGraph[size];

        for (int j = 0; j < this->size; ++j)
        {
            if (i == j)
            {
                //��ʼ��������������Ϊ0
                _Graph[i][j].m_cost = _Graph[i][j].m_time = 0;   
            }
            else
            {
                //��ʼ���������Ϊ���ֵ
                _Graph[i][j].m_cost = MAX;  
                _Graph[i][j].m_time = MAX;
            }
        }
    }

    //����д��(��ʵ�Ҹо����Լ����Ż�һ�£������ѭ����������ȥ���Ϳ���ʵ��ʱ�临�ӶȵĽ�һ������)
    for (int i = 0; i < this->tempRoute.size; i++)
    {
        int begin, end;
        begin = Locate(tempRoute.routes[i].origin_city, tempCity);
        end = Locate(tempRoute.routes[i].destination_city, tempCity);   //��·����ʼ����յ����Ŷ�λ
        _Graph[begin][end].m_cost = tempRoute.routes[i].m_cost;   //��·�̵Ļ��Ѻ�ʱ�丳��ͼ��cost��time����
        _Graph[begin][end].m_time = tempRoute.routes[i].m_time;
        _Graph[begin][end].routes = &tempRoute.routes[i];   //��·�̸���·��ָ�봢��
    }

}


GraphMatrix::~GraphMatrix()
{
    //ֻ��Ҫɾ�����������ʲô�ľͺ�
    //��Ϊ��Ҳд�������ط�����������
    delete[] _Graph;
}