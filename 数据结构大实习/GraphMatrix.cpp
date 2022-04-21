#include "GraphMatrix.h"
#include"Route.h"

GraphMatrix::GraphMatrix(City& inputCity,Route& inputRoute) : tempCity(inputCity),tempRoute(inputRoute)
{
    this->size = inputCity.size;
    CreateMatrixGraph();
}


int GraphMatrix::Locate(string city, City& _city)
{
    for (int i = 0; i < 199; i++) {
        if (_city.cities[i].m_city == city)
        {
            return i;   //�ҵ����򷵻��ҵ��ó��еĵı��
        }
    }
    return -1;   //���򷵻�-1
}


void GraphMatrix::CreateMatrixGraph()
{
    //�½�һ����ά����
    _Graph = new oneGraph * [size];
    for (int i = 0; i < size; ++i)
    {
        _Graph[i] = new oneGraph[size];
    }



    for (int i = 0; i < this->size; i++)
    {
        for (int j = 0; j < this->size; j++)
        {
            if (i == j)
            {
                _Graph[i][j].m_cost = _Graph[i][j].m_time = 0;   //��ʼ��������������Ϊ0
            }
            else
            {
                _Graph[i][j].m_cost = MAX;   //��ʼ���������Ϊ���ֵ
                _Graph[i][j].m_time = MAX;
            }
        }
    }

    for (int i = 0; i < this->tempRoute.size; i++)
    {
        int begin, end;
        begin = Locate(tempRoute.routes[i].origin_city, tempCity);
        end = Locate(tempRoute.routes[i].destination_city, tempCity);   //��·����ʼ����յ����Ŷ�λ
        _Graph[begin][end].m_cost = tempRoute.routes[i].m_cost;   //��·�̵Ļ��Ѻ�ʱ�丳��ͼ��cost��time����
        _Graph[begin][end].m_time = tempRoute.routes[i].m_time;
        _Graph[begin][end].routes = &tempRoute.routes[i];   //��·�̸���·��ָ�봢��
    }

    //ͼ���ڽӾ���Ŀռ临�Ӷ�
    //int totalSize = tempRoute.size + this->size + tempCity.size;
    //cout << "CreateMatrixGraph->Use of space:" << totalSize << endl;
}


GraphMatrix::~GraphMatrix()
{
    //�½�һ����άָ��
    for (int i = 0; i < size; i++)
    {
        delete[] _Graph[i];
    }
}