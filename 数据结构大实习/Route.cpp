#include"oneRoute.h"
#include "Route.h"



//解决诡异的freopen_s
# pragma warning ( disable:4996 )

//解决它认为我for循环不对的问题
# pragma warning ( disable:6294 )

//解决freopen没有返回值的问题（我现在根本不会用，只能眼不见为净）
# pragma warning ( disable:6031 )


Route::Route() :routes(nullptr), size(0) 
{
    ReadRoutes();
}

Route::~Route()
{
	delete[] routes;
}

int Route::getnumber(const char* filename)
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
        for (; fgets(buffer, sizeof(buffer) / sizeof(buffer[0]), fp) != nullptr; ++count) 
        {}
    }

    return count;
}

void Route::ReadRoutes(void)
{
    
    if (freopen("./source/routes.csv", "rt", stdin) == nullptr) 
    {
        cout << "无法打开该文件！" << endl;
        exit(0);
    }
    else
    {
        //读文件里地点的数目,并new一个数组
        this->size = getnumber("./source/routes.csv");
        routes = new oneRoute[size];


        for (int i = 0; i < size; ++i)
        {
            //一行全部读取
            char ctemp[1000];
            cin.getline(ctemp, sizeof(ctemp) / sizeof(ctemp[0]), '\n');
            string stemp(ctemp);


            //行内容处理
            //第一个地区
            routes[i].origin_city = stemp.substr(0, (stemp.find_first_of(',')));
            stemp.erase(0, stemp.find_first_of(',') + 1);

            //第二个地区
            routes[i].destination_city = stemp.substr(0, (stemp.find_first_of(',')));
            stemp.erase(0, stemp.find_first_of(',') + 1);

            //运输方式
            routes[i].m_transport = stemp.substr(0, (stemp.find_first_of(',')));
            stemp.erase(0, stemp.find_first_of(',') + 1);

            //运输时间
            routes[i].m_time = stof(stemp.substr(0, (stemp.find_first_of(','))));
            stemp.erase(0, stemp.find_first_of(',') + 1);

            //运输费用
            routes[i].m_cost = stof(stemp.substr(0, (stemp.find_first_of(','))));
            stemp.erase(0, stemp.find_first_of(',') + 1);


            //其他信息
            routes[i].other_information = stemp;
        }
    }
    
    fclose(stdin);
    freopen("CON", "r", stdin);

    //读取最短路径函数的空间复杂度
    //cout << "ReadRoutes->Use of space:" << size << endl;
}
