#include"oneRoute.h"
#include "Route.h"



//��������freopen_s
# pragma warning ( disable:4996 )

//�������Ϊ��forѭ�����Ե�����
# pragma warning ( disable:6294 )

//���freopenû�з���ֵ�����⣨�����ڸ��������ã�ֻ���۲���Ϊ����
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

    //����
    int count = 0;

    //��ȫ�ж�
    if (fp == nullptr)
    {
        cout << "�ļ���ʧ��" << endl;
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
        cout << "�޷��򿪸��ļ���" << endl;
        exit(0);
    }
    else
    {
        //���ļ���ص����Ŀ,��newһ������
        this->size = getnumber("./source/routes.csv");
        routes = new oneRoute[size];


        for (int i = 0; i < size; ++i)
        {
            //һ��ȫ����ȡ
            char ctemp[1000];
            cin.getline(ctemp, sizeof(ctemp) / sizeof(ctemp[0]), '\n');
            string stemp(ctemp);


            //�����ݴ���
            //��һ������
            routes[i].origin_city = stemp.substr(0, (stemp.find_first_of(',')));
            stemp.erase(0, stemp.find_first_of(',') + 1);

            //�ڶ�������
            routes[i].destination_city = stemp.substr(0, (stemp.find_first_of(',')));
            stemp.erase(0, stemp.find_first_of(',') + 1);

            //���䷽ʽ
            routes[i].m_transport = stemp.substr(0, (stemp.find_first_of(',')));
            stemp.erase(0, stemp.find_first_of(',') + 1);

            //����ʱ��
            routes[i].m_time = stof(stemp.substr(0, (stemp.find_first_of(','))));
            stemp.erase(0, stemp.find_first_of(',') + 1);

            //�������
            routes[i].m_cost = stof(stemp.substr(0, (stemp.find_first_of(','))));
            stemp.erase(0, stemp.find_first_of(',') + 1);


            //������Ϣ
            routes[i].other_information = stemp;
        }
    }
    
    fclose(stdin);
    freopen("CON", "r", stdin);

    //��ȡ���·�������Ŀռ临�Ӷ�
    //cout << "ReadRoutes->Use of space:" << size << endl;
}
