
#pragma once


//Ϊʲô��仰Ҫ�ȷ��������������ͻ���벻ͨ��
#include<iostream>
#include<string>
using namespace std;


//�����ࣨ����Ϊ�㣩
class oneCity
{
public:
    oneCity();

public:
    string m_country;   //����
    string m_city;   //����

    float m_latitude;   //γ��
    float m_longitude;   //����
};

//���������װ��
class City
{
public:
    City();//��ʼ���������ļ�
    ~City();

private:
    void ReadCities(void);
    int getnumber(const char*);//�����ļ���������д�С

public:
    int size;//������Ŀ 
    oneCity* cities;//���г���
};