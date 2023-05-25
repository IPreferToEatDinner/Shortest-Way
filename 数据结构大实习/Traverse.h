#pragma once
#include"GraphMatrix.h"
#include<windows.h>
//这是一个遍历类，在函数内部询问之后，实现两种遍历，对外只提供初始化接口
class Traverse
{
public:
	Traverse(GraphMatrix&);
	~Traverse();


private:
	void BFSfunction(int i);//广度优先函数的遍历
	void BFSTraverse(int pos);//广度优先遍历(BFS)的核心函数(遍历一行)(调用的时候就用这个)

	void DFSfunction(int i);//广度优先函数递归
	void DFSTraverse(void);//广度优先递归实现



private:
	GraphMatrix& tempGraphMatrix;
	int* isTrav;//用来记录有没有被访问过
};

