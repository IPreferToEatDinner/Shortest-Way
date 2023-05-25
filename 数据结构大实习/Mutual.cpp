#include "Mutual.h"
#include"City.h"
#include"Route.h"
#include"ShortestPath.h"
#include"Traverse.h"
#include"Timer.h"
#include<Windows.h>

Mutual::Mutual()
{
    //读两个文件时间
    Timer timer;
    timer.Start();

    //新建一个City类,会自动读取文件
    City _City;


    //新建一个Route类，并自动读取文件
    Route _Route;


    //新建一个GraphMatrix，自动就创建图
    GraphMatrix _GraphMatrix(_City, _Route);

    //停止然后输出时间
    timer.Stop();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    cout << "读取两个文件并构建邻接矩阵的时间为 " << timer.ElapsedTime() << " ms" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    
    //在图的遍历和最小路径的两个模式中选择
    string mode;
    cout << "请选择模式" << endl 
        << "--------------------------------------------" << endl
        << "输入  “遍历”  进行图的遍历" << endl 
        << "输入  “最短”  进行两种最短路径的检索和输出" << endl 
        << "--------------------------------------------" << endl;
    cin >> mode;
    system("cls");

    if (mode == "最短")
    {
        //新建一个shortestPath，函数内部会询问出发地和目的地，然后在选择条件（时间/距离），之后会在屏幕上打印路径
        ShortestPath _ShortestPath(_GraphMatrix);
    }
    else if(mode=="遍历")
    {
        //新建一个Traverse类，在内部会询问遍历要求和遍历初始城市
        Traverse _Traverse(_GraphMatrix);
    }
    else
    {
        cout << "模式输入错误" << endl;
        exit(0);
    }
}