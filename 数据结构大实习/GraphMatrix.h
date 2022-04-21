#pragma once
#include"oneRoute.h"
#include"City.h"
#include"Route.h"

#define MAX 99999  //����Ǿ������ֵ


class oneGraph
{
public:
    oneRoute* routes;   //·��(�����һ��·�ߵ�ָ��)
    float m_cost;   //·�߻���
    float m_time;   //·�ߺ�ʱ
    oneGraph();  //���캯��
    ~oneGraph();   //��������
};


class GraphMatrix
{
public:
    GraphMatrix(City&, Route&);
    ~GraphMatrix();

    void CreateMatrixGraph();
    int Locate(string, City&);//�������ֺͳ��д���,�����ھ����е�λ��
private:

public:
    oneGraph** _Graph;//����ָ�봦��
    int size;
    City& tempCity;
    Route& tempRoute;
};

