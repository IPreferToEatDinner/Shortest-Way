#include"City.h"


//解决诡异的freopen_s
# pragma warning ( disable:4996 )

City::City() :cities(nullptr), size(0) 
{
    //读取文件
    ReadCities();
}

City::~City()
{
    delete[] cities;
}

void City::ReadCities(void)
{
    if (freopen("./source/cities.csv", "rt", stdin) == nullptr)
    {
        cout << "无法打开该文件！";   //文件无法打开
        exit(0);
    }
    else
    {
        //读文件里地点的数目,并new一个数组
        size = getnumber("./source/cities.csv");
        cities = new oneCity[size];


        for (int i = 0; i < size; ++i)  //fp没有读到文件结束并且城市没有读取完
        {
            //一行全部读取
            char ctemp[100];
            cin.getline(ctemp, 100, '\n');
            string stemp(ctemp);

            //行内容处理
            //读取国家名
            cities[i].m_country = stemp.substr(0, (stemp.find_first_of(',')));
            stemp.erase(0, stemp.find_first_of(',') + 1);

            //读取城市名
            cities[i].m_city = stemp.substr(0, (stemp.find_first_of(',')));
            stemp.erase(0, stemp.find_first_of(',') + 1);

            //读取两个参数
            cities[i].m_latitude = stof(stemp.substr(0, (stemp.find_first_of(','))));
            stemp.erase(0, stemp.find_first_of(',') + 1);

            cities[i].m_longitude = stof(stemp);
        }
    }
    fclose(stdin); //文件关闭

}

int City::getnumber(const char* filename)
{
    FILE* fp = nullptr;
    fopen_s(&fp, filename, "rt");

    //计数
    int count = 0;

    //安全判断
    if (fp == nullptr)
    {
        cout << "文件打开失败" << endl;
    }
    else
    {
        char buffer[1000];
        for (; fgets(buffer, sizeof(buffer) / sizeof(buffer[0]), fp) != nullptr; ++count) {}
    }

    return count;
}