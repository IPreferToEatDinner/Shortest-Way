#pragma once

#include<iostream>
#include<string>
using namespace std;

#include"GraphMatrix.h"


class ShortestPath
{
public:
	ShortestPath(GraphMatrix&);
	~ShortestPath();

private:
	void Timecost(int begin);
	void Moneycost(int begin);
	void Dispath(int start, int end, int* path_ct, int& num);
	void writeFile(int path_ct[], int num);

private:
	string city_from;
	string city_to;
	GraphMatrix& tempGraphMatrix;
	int *pre;
	float *time;
	float* cost;
};

