#include "ShortestPath.h"
#include"GraphMatrix.h"
#include <fstream>


//�������Ϊ��forѭ�����Ե�����
# pragma warning ( disable:6294 )



ShortestPath::ShortestPath(GraphMatrix& inputGM) :tempGraphMatrix(inputGM), time(nullptr), cost(nullptr), pre(nullptr)
{
	//ѯ��Ҫȥ�������ط�
	cout << "������������������" << "  ʼ���� �� ��ĩ�� " << endl;
	cin >> city_from >> city_to;

	//��ʼ����������
	pre = new int[tempGraphMatrix.size];
	

	//��λ
	int begin = tempGraphMatrix.Locate(city_from, tempGraphMatrix.tempCity);
	int end = tempGraphMatrix.Locate(city_to, tempGraphMatrix.tempCity);

    //ѯ�ʹؼ���
    string searchWay;
    cout << "ѡ�����ȷ�ʽ   ʱ�䣨time��   �۸�money��" << endl;
    cin >> searchWay;


    if (searchWay == "time" || searchWay == "ʱ��")
    {
        //��������(ʱ��)
        time = new float[tempGraphMatrix.size];
        Timecost(begin);
    }
    else if (searchWay == "money" || searchWay == "�۸�")
    {
        //��������(�۸�)
        cost = new float[tempGraphMatrix.size];
        Moneycost(begin);
    }


    //��������Ϊ�ٶȵ�ͼ��׼����
    int path_ct[199];
    int num = 0;

    //��·��չʾ����
    Dispath(begin, end, path_ct, num);

    //д��ٶȵ�ͼ
    writeFile(path_ct, num);
}

void ShortestPath::Timecost(int begin)
{
    //���·����ѯ��ps:���б�׼Ϊ���ʱ��
    int i, j, k;
    float min;
    float tem;
    int* get = new int[tempGraphMatrix.size];   //ѡȡ����
    
    for (i = 0; i < tempGraphMatrix.size; ++i)
    {
        get[i] = 0;
        pre[i] = -1;   //pre���飬��¼��һ����
        time[i] = tempGraphMatrix._Graph[begin][i].m_time;   //��ʼ����ʱ�����
    }
    get[begin] = 1;
    time[begin] = 0;   //����ʼ��ĳ�ʼ��
    for (i = 0; i < tempGraphMatrix.size; i++)
    {
        if (time[i] != 0 && time[i] != 10000)   //����õ㲻�ǵ�ǰ����޷������
        {
            pre[i] = begin;   //ǰһ���㣬��·���ļ�¼
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
                k = j;   //����̰���㷨�����������ҵ����غ���ʱ����̵�·��
            }
        }
        get[k] = 1;   //ȡ�иõ�
        for (j = 0; j < tempGraphMatrix.size; j++)   //��ʣ��ĵ���и��²���
        {
            if (j != k && tempGraphMatrix._Graph[k][j].m_time < 10000)
            {
                tem = (time[k] + tempGraphMatrix._Graph[k][j].m_time);   //�õ��Ȩֵ������ʱ���Ϊԭֵ����ֵ
                if (get[j] == 0 && (tem < time[j]))
                {
                    time[j] = tem;
                    pre[j] = k;
                }
            }
        }
    }

    //���·�������Ŀռ临�Ӷ�
    //int size = tempGraphMatrix.size + tempGraphMatrix.size + tempGraphMatrix.size + tempGraphMatrix.size * tempGraphMatrix.size;
    //cout << "ShortestPath->Use of space:" << size << endl;   //���Ϊ���ÿռ��ֽ�����476016
}

void ShortestPath::Moneycost(int begin)
{
    //���·����ѯ��ps:���б�׼Ϊ���ٻ���
    int i, j, k;
    float min;
    float tem;
    int* get = new int[tempGraphMatrix.size];   //ѡȡ����
    for (i = 0; i <  tempGraphMatrix.size; i++)
    {
        get[i] = 0;
        pre[i] = -1;   //pre����
        cost[i] = tempGraphMatrix._Graph[begin][i].m_cost;   //��ʼ���ͻ��Ѳ���
    }


    get[begin] = 1;
    cost[begin] = 0;   //����ʼ��ĳ�ʼ��
    for (i = 0; i < tempGraphMatrix.size; i++)
    {
        if (cost[i] != 0 && cost[i] != 10000)   //����õ㲻�ǵ�ǰ����޷������
            pre[i] = begin;   //ǰһ���㣬��·���ļ�¼
    }

    for (i = 0; i < tempGraphMatrix.size - 1; i++)
    {
        min = MAX;
        for (j = 0; j < tempGraphMatrix.size; j++)
        {
            if (get[j] == 0 && cost[j] < min)
            {
                min = cost[j];
                k = j;   //����̰���㷨�����������ҵ����غ��л������ٵ�·��
            }
        }
        get[k] = 1;   //ȡ�иõ�
        for (j = 0; j < tempGraphMatrix.size; j++)   //��ʣ��ĵ���и��²���
        {
            if (j != k && tempGraphMatrix._Graph[k][j].m_time < 10000)
            {
                tem = (cost[k] + tempGraphMatrix._Graph[k][j].m_time);   //����
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
    //��ʾ·������
    int i = 0, j = 0;
    int k = end;
    int* pNew = new int[tempGraphMatrix.tempRoute.size];  //����·��������
    int n = 1;
    for (i = 0; i > 0; ++i)
    {
        if (pre[end] == start) { break; }

        //ѭ����·����������pNew
        pNew[i] = pre[end];
        end = pNew[i];
        j++;
    }
    num = j + 2;
    path_ct[0] = start;   //·���ĳ�ʼ��
    cout << "·��Ϊ��" << tempGraphMatrix.tempCity.cities[start].m_city;      //���·�������->ѭ�����·��->�յ�
    for (i = j - 1; i >= 0; i--, n++) {
        cout << " " << tempGraphMatrix.tempCity.cities[pNew[i]].m_city;
        path_ct[n] = pNew[i];
    }
    path_ct[num - 1] = k;   //���յ��ǰһ�������������յ�
    cout << " " << tempGraphMatrix.tempCity.cities[k].m_city << "\n";
}

void ShortestPath::writeFile(int path_ct[], int num)
{
    //������·�����ٶȵ�ͼ�����ӻ������
    fstream ioFile;
    ioFile.open("./source/graph.html", ios::out);
    ioFile << "<!DOCTYPE html><html><head><style type='text/css'>body, html{width: 100%;height: 100%;margin:0;font-family:'΢���ź�';}#allmap{height:100%;width:100%;}#r-result{width:100%;}</style><script type='text/javascript' src='http://api.map.baidu.com/api?v=2.0&ak=nSxiPohfziUaCuONe4ViUP2N'></script><title>Shortest path from Beijing to London</title></head><body><div id='allmap'></div></div></body></html><script type='text/javascript'>var map = new BMap.Map('allmap');var point = new BMap.Point(0, 0);map.centerAndZoom(point, 2);map.enableScrollWheelZoom(true);" << "\n";
    ioFile << "var marker0 = new BMap.Marker(new BMap.Point(" << tempGraphMatrix.tempCity.cities[path_ct[0]].m_longitude << ", " << tempGraphMatrix.tempCity.cities[path_ct[0]].m_latitude << ")); map.addOverlay(marker0);" << "\n";
    ioFile << "var infoWindow0 = new BMap.InfoWindow(\"<p style = 'font-size:14px;'>country: " << tempGraphMatrix.tempCity.cities[path_ct[0]].m_country << "<br/>city: " << tempGraphMatrix.tempCity.cities[path_ct[0]].m_city << "</p>\");marker0.addEventListener(\"click\", function(){this.openInfoWindow(infoWindow0);}); " << "\n";
    for (int i = 1; i < num - 1; i++) {   //ѭ�����ÿһ����
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
    cout << "���ӻ�չʾ��������ļ�'graph.html'��" << endl;
    cout << "-------------------------------------------" << endl;
}

ShortestPath::~ShortestPath()
{
    if (pre) { delete pre; }
    if (time) { delete time; }
    if (cost) { delete cost; }
}
