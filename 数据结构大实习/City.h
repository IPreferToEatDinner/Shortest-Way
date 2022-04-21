
#pragma once


//为什么这句话要先放在这里，放在外面就会编译不通过
#include<iostream>
#include<string>
using namespace std;


//城市类（类型为点）
class oneCity
{
public:
    oneCity();

public:
    string m_country;   //国家
    string m_city;   //城市

    float m_latitude;   //纬度
    float m_longitude;   //经度
};

//城市整体封装类
class City
{
public:
    City();//初始化并读入文件
    ~City();

private:
    void ReadCities(void);
    int getnumber(const char*);//传入文件名计算城市大小

public:
    int size;//城市数目 
    oneCity* cities;//所有城市
};