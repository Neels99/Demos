#pragma once
#include"cTask.h"
#include <vector>
#include <queue>
#include "boost/thread.hpp"

// ���������� � ������
struct ThreadInfo
{
	boost::thread* thread;
	cTask* task;
	ThreadInfo():thread(0),task(0){}
};

// ����� ���� �������
class cThreadPool
{
	std::queue<cTask*> tasks;
	std::vector<ThreadInfo*> threads;	
	boost::thread* serviceThread;
public:
	// ����������-����������
	cThreadPool(void);
	~cThreadPool(void);
public:
	void addTask(cTask* task);					// �������� ������ � ������ ����� � ���������, ���� ��� ����������
	bool haveTasks(){return tasks.size()>0;}	// ���������� true, ���� � ������ ���� ������
	void configThread();						// ���������������� ����� ��� ������ �� �����
};

