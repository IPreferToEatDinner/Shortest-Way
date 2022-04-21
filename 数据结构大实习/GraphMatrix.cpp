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
            return i;   //找到了则返回找到该城市的的编号
        }
    }
    return -1;   //否则返回-1
}


void GraphMatrix::CreateMatrixGraph()
{
    //新建一个二维矩阵
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
                _Graph[i][j].m_cost = _Graph[i][j].m_time = 0;   //初始化所有自身连接为0
            }
            else
            {
                _Graph[i][j].m_cost = MAX;   //初始化外界连接为最大值
                _Graph[i][j].m_time = MAX;
            }
        }
    }

    for (int i = 0; i < this->tempRoute.size; i++)
    {
        int begin, end;
        begin = Locate(tempRoute.routes[i].origin_city, tempCity);
        end = Locate(tempRoute.routes[i].destination_city, tempCity);   //将路线起始点和终点的序号定位
        _Graph[begin][end].m_cost = tempRoute.routes[i].m_cost;   //将路程的花费和时间赋给图的cost和time变量
        _Graph[begin][end].m_time = tempRoute.routes[i].m_time;
        _Graph[begin][end].routes = &tempRoute.routes[i];   //将路程赋给路程指针储存
    }

    //图的邻接矩阵的空间复杂度
    //int totalSize = tempRoute.size + this->size + tempCity.size;
    //cout << "CreateMatrixGraph->Use of space:" << totalSize << endl;
}


GraphMatrix::~GraphMatrix()
{
    //新建一个二维指针
    for (int i = 0; i < size; i++)
    {
        delete[] _Graph[i];
    }
}