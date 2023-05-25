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
            return i;   //找到了则返回找到该城市的的编号
        }
    }

    //如果输入错误
    cout << "-----------------" << endl
        << "城市名字输入错误" << endl
        << "-----------------" << endl;
    exit(0);
}


void GraphMatrix::CreateMatrixGraph()
{

    //先开辟二维数组的纵列
    _Graph = new oneGraph * [size];

    for (int i = 0; i < this->size; ++i)
    {
        //新建二维数组，一边新建一边写入
        _Graph[i] = new oneGraph[size];

        for (int j = 0; j < this->size; ++j)
        {
            if (i == j)
            {
                //初始化所有自身连接为0
                _Graph[i][j].m_cost = _Graph[i][j].m_time = 0;   
            }
            else
            {
                //初始化外界连接为最大值
                _Graph[i][j].m_cost = MAX;  
                _Graph[i][j].m_time = MAX;
            }
        }
    }

    //矩阵写入(其实我感觉可以继续优化一下，把这个循环放在上面去，就可以实现时间复杂度的进一步降低)
    for (int i = 0; i < this->tempRoute.size; i++)
    {
        int begin, end;
        begin = Locate(tempRoute.routes[i].origin_city, tempCity);
        end = Locate(tempRoute.routes[i].destination_city, tempCity);   //将路线起始点和终点的序号定位
        _Graph[begin][end].m_cost = tempRoute.routes[i].m_cost;   //将路程的花费和时间赋给图的cost和time变量
        _Graph[begin][end].m_time = tempRoute.routes[i].m_time;
        _Graph[begin][end].routes = &tempRoute.routes[i];   //将路程赋给路程指针储存
    }

}


GraphMatrix::~GraphMatrix()
{
    //只需要删掉数组的索引什么的就好
    //因为我也写了其他地方的析构函数
    delete[] _Graph;
}