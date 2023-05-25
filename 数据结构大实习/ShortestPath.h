#pragma once
#include<iostream>
#include<windows.h>
#include<string>
using namespace std;

#include"GraphMatrix.h"


class ShortestPath
{
public:
	ShortestPath(GraphMatrix&);
	~ShortestPath();

private:
	void Timecost(int begin, int end);
	void Moneycost(int begin, int end);
	void Dispath(int start, int end, int* path_ct, int& num);
	void restrict(void);
	void writeFile(int path_ct[], int num);

private:
	string city_from;
	string city_to;
	GraphMatrix& tempGraphMatrix;
	int* pre;//�������¼֮ǰ�ĵ�
	float* time;//�ݴ��ʱ������
	float* cost;//�ݴ�ļ۸�����
};

