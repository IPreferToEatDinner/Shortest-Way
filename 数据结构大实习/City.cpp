#include"City.h"


//��������freopen_s
# pragma warning ( disable:4996 )

City::City() :cities(nullptr), size(0) 
{
    //��ȡ�ļ�
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
        cout << "�޷��򿪸��ļ���";   //�ļ��޷���
        exit(0);
    }
    else
    {
        //���ļ���ص����Ŀ,��newһ������
        size = getnumber("./source/cities.csv");
        cities = new oneCity[size];


        for (int i = 0; i < size; ++i)  //fpû�ж����ļ��������ҳ���û�ж�ȡ��
        {
            //һ��ȫ����ȡ
            char ctemp[100];
            cin.getline(ctemp, 100, '\n');
            string stemp(ctemp);

            //�����ݴ���
            //��ȡ������
            cities[i].m_country = stemp.substr(0, (stemp.find_first_of(',')));
            stemp.erase(0, stemp.find_first_of(',') + 1);

            //��ȡ������
            cities[i].m_city = stemp.substr(0, (stemp.find_first_of(',')));
            stemp.erase(0, stemp.find_first_of(',') + 1);

            //��ȡ��������
            cities[i].m_latitude = stof(stemp.substr(0, (stemp.find_first_of(','))));
            stemp.erase(0, stemp.find_first_of(',') + 1);

            cities[i].m_longitude = stof(stemp);
        }
    }
    fclose(stdin); //�ļ��ر�

}

int City::getnumber(const char* filename)
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
        for (; fgets(buffer, sizeof(buffer) / sizeof(buffer[0]), fp) != nullptr; ++count) {}
    }

    return count;
}