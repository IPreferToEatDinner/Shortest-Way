#pragma once

//永远诡异
#include<iostream>
#include<string>
using namespace std;

//路线类（类型为边）
class oneRoute
{   
public:
    oneRoute();
    
public:
    string origin_city;   //路线起点
    string destination_city;     //路线终点
    string m_transport;    //交通工具
    string other_information;   //其他信息

    float m_cost;   //花费
    float m_time;   //时间
};