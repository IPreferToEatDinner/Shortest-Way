#pragma once
#include"GraphMatrix.h"
#include<windows.h>
//����һ�������࣬�ں����ڲ�ѯ��֮��ʵ�����ֱ���������ֻ�ṩ��ʼ���ӿ�
class Traverse
{
public:
	Traverse(GraphMatrix&);
	~Traverse();


private:
	void BFSfunction(int i);//������Ⱥ����ı���
	void BFSTraverse(int pos);//������ȱ���(BFS)�ĺ��ĺ���(����һ��)(���õ�ʱ��������)

	void DFSfunction(int i);//������Ⱥ����ݹ�
	void DFSTraverse(void);//������ȵݹ�ʵ��



private:
	GraphMatrix& tempGraphMatrix;
	int* isTrav;//������¼��û�б����ʹ�
};

