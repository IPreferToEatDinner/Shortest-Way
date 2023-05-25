#pragma once
#include"oneRoute.h"
#include"City.h"
#include"Route.h"

#define MAX 99999  //����Ǿ������ֵ

class oneGraph
{
public:
    oneGraph();  //���캯��
    ~oneGraph();   //��������
public:
    oneRoute* routes;   //·��(�����һ��·�ߵ�ָ��)
    float m_cost;   //·�߻���
    float m_time;   //·�ߺ�ʱ
};


class GraphMatrix
{
public:
    GraphMatrix(City&, Route&);
    ~GraphMatrix();

    void CreateMatrixGraph();
    int Locate(string, City&);//�������ֺͳ��д���,�����ھ����е�λ��

public:
    oneGraph** _Graph;//����ָ��
    int size;
    City& tempCity;
    Route& tempRoute;
};

