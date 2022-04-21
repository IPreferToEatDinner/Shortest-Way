#include "ShortestPath.h"
#include"GraphMatrix.h"
#include <fstream>


//解决它认为我for循环不对的问题
# pragma warning ( disable:6294 )



ShortestPath::ShortestPath(GraphMatrix& inputGM) :tempGraphMatrix(inputGM), time(nullptr), cost(nullptr), pre(nullptr)
{
	//询问要去的两个地方
	cout << "请依次输入两个城市" << "  始发地 和 终末地 " << endl;
	cin >> city_from >> city_to;

	//初始化两个数组
	pre = new int[tempGraphMatrix.size];
	

	//定位
	int begin = tempGraphMatrix.Locate(city_from, tempGraphMatrix.tempCity);
	int end = tempGraphMatrix.Locate(city_to, tempGraphMatrix.tempCity);

    //询问关键词
    string searchWay;
    cout << "选择优先方式   时间（time）   价格（money）" << endl;
    cin >> searchWay;


    if (searchWay == "time" || searchWay == "时间")
    {
        //核心运算(时间)
        time = new float[tempGraphMatrix.size];
        Timecost(begin);
    }
    else if (searchWay == "money" || searchWay == "价格")
    {
        //核心运算(价格)
        cost = new float[tempGraphMatrix.size];
        Moneycost(begin);
    }


    //这两个是为百度地图做准备的
    int path_ct[199];
    int num = 0;

    //将路径展示出来
    Dispath(begin, end, path_ct, num);

    //写入百度地图
    writeFile(path_ct, num);
}

void ShortestPath::Timecost(int begin)
{
    //最短路径查询，ps:评判标准为最短时间
    int i, j, k;
    float min;
    float tem;
    int* get = new int[tempGraphMatrix.size];   //选取数组
    
    for (i = 0; i < tempGraphMatrix.size; ++i)
    {
        get[i] = 0;
        pre[i] = -1;   //pre数组，记录上一个点
        time[i] = tempGraphMatrix._Graph[begin][i].m_time;   //初始化和时间参数
    }
    get[begin] = 1;
    time[begin] = 0;   //对起始点的初始化
    for (i = 0; i < tempGraphMatrix.size; i++)
    {
        if (time[i] != 0 && time[i] != 10000)   //如果该点不是当前点或无法到达点
        {
            pre[i] = begin;   //前一个点，即路径的记录
        }
    }

    for (i = 0; i < tempGraphMatrix.size - 1; i++)
    {
        min = MAX;
        for (j = 0; j < tempGraphMatrix.size; j++)
        {
            if (get[j] == 0 && time[j] < min)
            {
                min = time[j];
                k = j;   //根据贪婪算法，遍历并且找到本回合中时间最短的路径
            }
        }
        get[k] = 1;   //取中该点
        for (j = 0; j < tempGraphMatrix.size; j++)   //对剩余的点进行更新操作
        {
            if (j != k && tempGraphMatrix._Graph[k][j].m_time < 10000)
            {
                tem = (time[k] + tempGraphMatrix._Graph[k][j].m_time);   //该点的权值即到达时间改为原值加新值
                if (get[j] == 0 && (tem < time[j]))
                {
                    time[j] = tem;
                    pre[j] = k;
                }
            }
        }
    }

    //最短路径函数的空间复杂度
    //int size = tempGraphMatrix.size + tempGraphMatrix.size + tempGraphMatrix.size + tempGraphMatrix.size * tempGraphMatrix.size;
    //cout << "ShortestPath->Use of space:" << size << endl;   //结果为所用空间字节数：476016
}

void ShortestPath::Moneycost(int begin)
{
    //最短路径查询，ps:评判标准为最少花费
    int i, j, k;
    float min;
    float tem;
    int* get = new int[tempGraphMatrix.size];   //选取数组
    for (i = 0; i <  tempGraphMatrix.size; i++)
    {
        get[i] = 0;
        pre[i] = -1;   //pre数组
        cost[i] = tempGraphMatrix._Graph[begin][i].m_cost;   //初始化和花费参数
    }


    get[begin] = 1;
    cost[begin] = 0;   //对起始点的初始化
    for (i = 0; i < tempGraphMatrix.size; i++)
    {
        if (cost[i] != 0 && cost[i] != 10000)   //如果该点不是当前点或无法到达点
            pre[i] = begin;   //前一个点，即路径的记录
    }

    for (i = 0; i < tempGraphMatrix.size - 1; i++)
    {
        min = MAX;
        for (j = 0; j < tempGraphMatrix.size; j++)
        {
            if (get[j] == 0 && cost[j] < min)
            {
                min = cost[j];
                k = j;   //根据贪婪算法，遍历并且找到本回合中花费最少的路径
            }
        }
        get[k] = 1;   //取中该点
        for (j = 0; j < tempGraphMatrix.size; j++)   //对剩余的点进行更新操作
        {
            if (j != k && tempGraphMatrix._Graph[k][j].m_time < 10000)
            {
                tem = (cost[k] + tempGraphMatrix._Graph[k][j].m_time);   //更新
                if (get[j] == 0 && (tem < cost[j]))
                {
                    cost[j] = tem;
                    pre[j] = k;
                }
            }
        }
    }
}

void ShortestPath::Dispath(int start, int end, int* path_ct, int& num)
{
    //显示路径函数
    int i = 0, j = 0;
    int k = end;
    int* pNew = new int[tempGraphMatrix.tempRoute.size];  //储存路径的数组
    int n = 1;
    for (i = 0; i > 0; ++i)
    {
        if (pre[end] == start) { break; }

        //循环将路径存入数组pNew
        pNew[i] = pre[end];
        end = pNew[i];
        j++;
    }
    num = j + 2;
    path_ct[0] = start;   //路径的初始化
    cout << "路线为：" << tempGraphMatrix.tempCity.cities[start].m_city;      //输出路径，起点->循环输出路径->终点
    for (i = j - 1; i >= 0; i--, n++) {
        cout << " " << tempGraphMatrix.tempCity.cities[pNew[i]].m_city;
        path_ct[n] = pNew[i];
    }
    path_ct[num - 1] = k;   //在终点的前一个点结束并输出终点
    cout << " " << tempGraphMatrix.tempCity.cities[k].m_city << "\n";
}

void ShortestPath::writeFile(int path_ct[], int num)
{
    //输出最短路径到百度地图，可视化的完成
    fstream ioFile;
    ioFile.open("./source/graph.html", ios::out);
    ioFile << "<!DOCTYPE html><html><head><style type='text/css'>body, html{width: 100%;height: 100%;margin:0;font-family:'微软雅黑';}#allmap{height:100%;width:100%;}#r-result{width:100%;}</style><script type='text/javascript' src='http://api.map.baidu.com/api?v=2.0&ak=nSxiPohfziUaCuONe4ViUP2N'></script><title>Shortest path from Beijing to London</title></head><body><div id='allmap'></div></div></body></html><script type='text/javascript'>var map = new BMap.Map('allmap');var point = new BMap.Point(0, 0);map.centerAndZoom(point, 2);map.enableScrollWheelZoom(true);" << "\n";
    ioFile << "var marker0 = new BMap.Marker(new BMap.Point(" << tempGraphMatrix.tempCity.cities[path_ct[0]].m_longitude << ", " << tempGraphMatrix.tempCity.cities[path_ct[0]].m_latitude << ")); map.addOverlay(marker0);" << "\n";
    ioFile << "var infoWindow0 = new BMap.InfoWindow(\"<p style = 'font-size:14px;'>country: " << tempGraphMatrix.tempCity.cities[path_ct[0]].m_country << "<br/>city: " << tempGraphMatrix.tempCity.cities[path_ct[0]].m_city << "</p>\");marker0.addEventListener(\"click\", function(){this.openInfoWindow(infoWindow0);}); " << "\n";
    for (int i = 1; i < num - 1; i++) {   //循环输出每一个点
        ioFile << "var marker" << i << " = new BMap.Marker(new BMap.Point(" << tempGraphMatrix.tempCity.cities[path_ct[i]].m_longitude << ", " << tempGraphMatrix.tempCity.cities[path_ct[i]].m_latitude << ")); map.addOverlay(marker" << i << ");" << "\n";
        ioFile << "var infoWindow" << i << " = new BMap.InfoWindow(\"<p style = 'font-size:14px;'>country: " << tempGraphMatrix.tempCity.cities[path_ct[i]].m_country << "<br/>city: " << tempGraphMatrix.tempCity.cities[path_ct[i]].m_city << "</p>\");marker" << i << ".addEventListener(\"click\", function(){this.openInfoWindow(infoWindow" << i << ");}); " << "\n";
        ioFile << "var contentString0" << i << " = '" << tempGraphMatrix.tempCity.cities[path_ct[i - 1]].m_city << ", " << tempGraphMatrix.tempCity.cities[path_ct[i - 1]].m_country << " --> " << tempGraphMatrix.tempCity.cities[path_ct[i]].m_city << "," << tempGraphMatrix.tempCity.cities[path_ct[i]].m_country << " (" << tempGraphMatrix._Graph[path_ct[i - 1]][path_ct[i]].routes->m_transport << " - " << tempGraphMatrix._Graph[path_ct[i - 1]][path_ct[i]].m_time << " - " << tempGraphMatrix._Graph[path_ct[i - 1]][path_ct[i]].m_cost << " - \"" << tempGraphMatrix._Graph[path_ct[i - 1]][path_ct[i]].routes->other_information << "\")';var path" << i << " = new BMap.Polyline([new BMap.Point(" << tempGraphMatrix.tempCity.cities[path_ct[i - 1]].m_longitude << ", " << tempGraphMatrix.tempCity.cities[path_ct[i - 1]].m_latitude << "),new BMap.Point(" << tempGraphMatrix.tempCity.cities[path_ct[i]].m_longitude << ", " << tempGraphMatrix.tempCity.cities[path_ct[i]].m_latitude << ")], {strokeColor:'#18a45b', strokeWeight:8, strokeOpacity:0.8});map.addOverlay(path" << i << ");path" << i << ".addEventListener(\"click\", function(){alert(contentString0" << i << ");});var marker" << i << " = new BMap.Marker(new BMap.Point(" << tempGraphMatrix.tempCity.cities[path_ct[i]].m_longitude << ", " << tempGraphMatrix.tempCity.cities[path_ct[i]].m_latitude << "));map.addOverlay(marker" << i << ");" << "\n";
        ioFile << "var infoWindow" << i << " = new BMap.InfoWindow(\"<p style = 'font-size:14px;'>country: " << tempGraphMatrix.tempCity.cities[path_ct[i]].m_country << "<br/>city: " << tempGraphMatrix.tempCity.cities[path_ct[i]].m_city << "</p>\");marker" << i << ".addEventListener(\"click\", function(){this.openInfoWindow(infoWindow" << i << ");}); " << "\n";
    }
    ioFile << "var marker" << num - 1 << " = new BMap.Marker(new BMap.Point(" << tempGraphMatrix.tempCity.cities[path_ct[num - 1]].m_longitude << ", " << tempGraphMatrix.tempCity.cities[path_ct[num - 1]].m_latitude << ")); map.addOverlay(marker" << num - 1 << ");" << "\n";
    ioFile << "var infoWindow" << num - 1 << " = new BMap.InfoWindow(\"<p style = 'font-size:14px;'>country: " << tempGraphMatrix.tempCity.cities[path_ct[num - 1]].m_country << "<br/>city: " << tempGraphMatrix.tempCity.cities[path_ct[num - 1]].m_city << "</p>\");marker" << num - 1 << ".addEventListener(\"click\", function(){this.openInfoWindow(infoWindow" << num - 1 << ");}); " << "\n";
    ioFile << "var contentString0" << num - 1 << " = '" << tempGraphMatrix.tempCity.cities[path_ct[num - 2]].m_city << ", " << tempGraphMatrix.tempCity.cities[path_ct[num - 2]].m_country << " --> " << tempGraphMatrix.tempCity.cities[path_ct[num - 1]].m_city << "," << tempGraphMatrix.tempCity.cities[path_ct[num - 1]].m_country << " (" << tempGraphMatrix._Graph[path_ct[num - 2]][path_ct[num - 1]].routes->m_transport << " - " << tempGraphMatrix._Graph[path_ct[num - 2]][path_ct[num - 1]].m_time << " - " << tempGraphMatrix._Graph[path_ct[num - 2]][path_ct[num - 1]].m_cost << " - \"" << tempGraphMatrix._Graph[path_ct[num - 2]][path_ct[num - 1]].routes->other_information << "\")';var path" << num - 1 << " = new BMap.Polyline([new BMap.Point(" << tempGraphMatrix.tempCity.cities[path_ct[num - 2]].m_longitude << ", " << tempGraphMatrix.tempCity.cities[path_ct[num - 2]].m_latitude << "),new BMap.Point(" << tempGraphMatrix.tempCity.cities[path_ct[num - 1]].m_longitude << ", " << tempGraphMatrix.tempCity.cities[path_ct[num - 1]].m_latitude << ")], {strokeColor:'#18a45b', strokeWeight:8, strokeOpacity:0.8});map.addOverlay(path" << num - 1 << ");path" << num - 1 << ".addEventListener(\"click\", function(){alert(contentString0" << num - 1 << ");});var marker" << num - 1 << " = new BMap.Marker(new BMap.Point(" << tempGraphMatrix.tempCity.cities[path_ct[num - 1]].m_longitude << ", " << tempGraphMatrix.tempCity.cities[path_ct[num - 1]].m_latitude << "));map.addOverlay(marker" << num - 1 << ");" << "\n";
    ioFile << "</script>";
    ioFile.close();

    cout << "-------------------------------------------" << endl;
    cout << "可视化展示已输出在文件'graph.html'中" << endl;
    cout << "-------------------------------------------" << endl;
}

ShortestPath::~ShortestPath()
{
    if (pre) { delete pre; }
    if (time) { delete time; }
    if (cost) { delete cost; }
}
