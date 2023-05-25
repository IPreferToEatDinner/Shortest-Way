#pragma once
#include"oneRoute.h"

class Route
{
public:
	Route();
	~Route();
	void ReadRoutes(void);
	int getnumber(const char*);//在数组里面找到下标，用于和矩阵交互

public:
	oneRoute* routes;
	int size;
};

