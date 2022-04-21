#include "Mutual.h"
#include"City.h"
#include"Route.h"
#include"GraphMatrix.h"
#include"ShortestPath.h"

Mutual::Mutual()
{
    //新建一个City类,会自动读取文件
    City _City;

    //新建一个Route类，并自动读取文件
    Route _Route;

    //新建一个GraphMatrix，自动就创建图
    GraphMatrix _GraphMatrix(_City, _Route);

    //在图的遍历和最小路径的两个模式中选择
    string mode;
    cout << "请选择模式" << endl << "输入  “遍历”  进行图的遍历" << endl << "输入 “最短”  进行两种最短路径的检索和输出" << endl;
    cin >> mode;

    if (mode == "最短")
    {
        //新建一个shortestPath，函数内部会询问出发地和目的地，然后在选择条件（时间/距离），之后会在屏幕上打印路径
        ShortestPath _ShortestPath(_GraphMatrix);
    }
    else
    {

    }

}