#pragma once

//��Զ����
#include<iostream>
#include<string>
using namespace std;

//·���ࣨ����Ϊ�ߣ�
class oneRoute
{   
public:
    oneRoute();
    
public:
    string origin_city;   //·�����
    string destination_city;     //·���յ�
    string m_transport;    //��ͨ����
    string other_information;   //������Ϣ

    float m_cost;   //����
    float m_time;   //ʱ��
};