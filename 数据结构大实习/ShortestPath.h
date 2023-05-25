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
	int* pre;//用数组记录之前的点
	float* time;//暂存的时间数组
	float* cost;//暂存的价格数组
};

