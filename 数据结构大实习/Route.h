#pragma once
#include"oneRoute.h"

class Route
{
public:
	Route();
	~Route();
	void ReadRoutes(void);
	int getnumber(const char*);//�����������ҵ��±꣬���ں;��󽻻�

public:
	oneRoute* routes;
	int size;
};

