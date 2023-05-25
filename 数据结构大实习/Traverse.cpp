#include "Traverse.h"
#include"GraphMatrix.h"
#include<queue>
#include"Timer.h"
#include<iomanip>

Traverse::Traverse(GraphMatrix& input) :isTrav(nullptr), tempGraphMatrix(input)
{
    //初始化遍历数组
    isTrav = new int[tempGraphMatrix.size];

    //询问图的遍历方式
    int flag = 0;
    cout << "-----------------" << endl
        << "深度遍历请输入 1 " << endl
        << "广度遍历请输入 2" << endl
        << "-----------------" << endl;
    cin >> flag;
    system("cls");

    //询问开始的城市（作为节点使用）
    string city;
    cout << "-----------------" << endl
        << "请输入遍历开始的城市" << endl
        << "-----------------" << endl;
    cin >> city;
    system("cls");

    //处理城市
    int beginCity = tempGraphMatrix.Locate(city, tempGraphMatrix.tempCity);


    //开始计算时间
    Timer timer;
    timer.Start();


    //选择遍历方式
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
            << "你输入了奇奇怪怪的字符，请检查一下" << endl
            << "-------------------------------" << endl;
        break;
    }

    timer.Stop();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    cout << endl << "遍历时间是 " << timer.ElapsedTime() << " ms" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

}


//广度优先遍历(BFS)的核心函数(遍历一行）
void Traverse::BFSfunction(int i)
{
    int j;

    //使用int型队列
    queue<int>Q;

    //遍历记录数组的初始化
    isTrav[i] = 1;

    cout << setw(30) << tempGraphMatrix.tempCity.cities[i].m_city
        << setw(20) << tempGraphMatrix.tempCity.cities[i].m_latitude
        << setw(20) << tempGraphMatrix.tempCity.cities[i].m_longitude << endl;

    //在队列末尾加上i
    Q.push(i);

    while (!Q.empty())
    {
        i = Q.front();

        //删除掉队头元素
        Q.pop();

        for (j = 0; j < tempGraphMatrix.size; ++j)
        {
            //如果之间有联系并且没有被遍历过
            if (tempGraphMatrix._Graph[i][j].m_cost != MAX && !isTrav[j])
            {
                //直接输出
                cout << setw(30) << tempGraphMatrix.tempCity.cities[j].m_city
                    << setw(20) << tempGraphMatrix.tempCity.cities[j].m_latitude
                    << setw(20) << tempGraphMatrix.tempCity.cities[j].m_longitude << endl;

                //可以看到，矩阵是可以压扁的，这个点访问过了就不用再访问了
                isTrav[j] = 1;

                //把这个点加入队列
                Q.push(j);
            }
        }
    }
}


//外面包着的函数
void Traverse::BFSTraverse(int pos)
{   
    int i;

    //先将全部初始化为0，然后逐步遍历
    for (i = 0; i < tempGraphMatrix.size; ++i)
    {
        isTrav[i] = 0;  
    }
     
    //连通分量计算
    int count = 0;

    for (i = 0; i < tempGraphMatrix.size; ++i)
    {
        if (!isTrav[(i + pos) % tempGraphMatrix.size])
        {
            //递归算法完成路径的遍历
            BFSfunction((i + pos) % tempGraphMatrix.size);

            ++count;
        }
    }

    cout << "连通分量为  " << count << endl;
}


//DFS深度优先遍历，用第二种种方式实现遍历
void Traverse::DFSfunction(int i)
{
    //初始点设置为1（访问过）
    isTrav[i] = 1;
    cout << setw(30) << tempGraphMatrix.tempCity.cities[i].m_city
        << setw(20) << tempGraphMatrix.tempCity.cities[i].m_latitude
        << setw(20) << tempGraphMatrix.tempCity.cities[i].m_longitude << endl;

    //从第0个顶点开始判断到最后一个
    for (int j = 0; j < tempGraphMatrix.tempCity.size; j++)
    {
        //如果城市i到城市j有路径，且j未访问，则进行递归
        if (tempGraphMatrix._Graph[i][j].m_cost != MAX && !isTrav[j])
        {
            DFSfunction(j);
        }
    }
}

//调用函数
void Traverse::DFSTraverse()
{
    //初始化，将所有顶点都设定为未访问过
    for (int i = 0; i < tempGraphMatrix.tempCity.size; i++)
    {
        isTrav[i] = 0;
    }

    //连通分量计算
    int count = 0;

    for (int i = 0; i < tempGraphMatrix.tempCity.size; i++)
    {
        if (!isTrav[i])
        {
            //若未被访问则进行DFS遍历，防止未连通
            DFSfunction(i);
            ++count;
        }
    }

    cout << "连通分量为  " << count << endl;
}

//简简单单析构函数
Traverse::~Traverse()
{
    delete[] isTrav;
}