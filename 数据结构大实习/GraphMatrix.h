#pragma once
#include"oneRoute.h"
#include"City.h"
#include"Route.h"

#define MAX 99999  //这个是距离最大值


class oneGraph
{
public:
    oneRoute* routes;   //路线(这就是一条路线的指针)
    float m_cost;   //路线花费
    float m_time;   //路线耗时
    oneGraph();  //构造函数
    ~oneGraph();   //析构函数
};


class GraphMatrix
{
public:
    GraphMatrix(City&, Route&);
    ~GraphMatrix();

    void CreateMatrixGraph();
    int Locate(string, City&);//传入名字和城市大类,返回在矩阵中的位置
private:

public:
    oneGraph** _Graph;//二级指针处理
    int size;
    City& tempCity;
    Route& tempRoute;
};

