#pragma once
#include"cTask.h"
#include <vector>
#include <queue>
#include "boost/thread.hpp"

// информация о потоке
struct ThreadInfo
{
	boost::thread* thread;
	cTask* task;
	ThreadInfo():thread(0),task(0){}
};

// класс пула потоков
class cThreadPool
{
	std::queue<cTask*> tasks;
	std::vector<ThreadInfo*> threads;	
	boost::thread* serviceThread;
public:
	// конструкто-деструктор
	cThreadPool(void);
	~cThreadPool(void);
public:
	void addTask(cTask* task);					// добавить задачу в список задач и дождаться, пока она запустится
	bool haveTasks(){return tasks.size()>0;}	// возвращает true, если в списке есть задачи
	void configThread();						// сконфигурировать поток для первой из задач
};

