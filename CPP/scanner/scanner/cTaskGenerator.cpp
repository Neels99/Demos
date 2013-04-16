#include "StdAfx.h"
#include "cTaskGenerator.h"
#include "cThreadPool.h"
#include "cTask.h"

void callbackFunction()
{
	std::cout<<"Функция обратного вызова: ";
}

/* CLASS */

cTaskGenerator::cTaskGenerator(void)
{
	ctpool = new cThreadPool();
}

cTaskGenerator::~cTaskGenerator(void)
{
	delete ctpool;
}

void cTaskGenerator::GeterateTask(int count)
{
	srand ((unsigned int)time(NULL));
	//boost::mutex::scoped_lock lock(cThreadPool::thMutex);
	cTask* task;
	cTaskParams* params;

	for(int i=0;i<count;i++)
	{
		int seed = rand(), subseed = rand(); // сравниваем 2 неизвестных :-)
		// выбор типа задачи
		if(seed>subseed)
		{
			// число
			task = new cTask1();
			params = new cTaskParams1();
			params->setCallBackFunction(&callbackFunction);			
			((cTaskParams1*)params)->x = rand();
			((cTaskParams1*)params)->y = rand();
		}else
		{
			char* x = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};
			// строка
			task = new cTask2();
			params = new cTaskParams2();
			params->setCallBackFunction(&callbackFunction);			
			for(int j=0;j<10;j++)
			{
				int ndx1 = rand(), ndx2 = rand();
				while(ndx1>(int)strlen(x)) ndx1 = (int)(ndx1 /10);
				while(ndx2>(int)strlen(x)) ndx2 = (int)(ndx2 /10);
				((cTaskParams2*)params)->str1+=x[ndx1];
				((cTaskParams2*)params)->str2+=x[ndx1];
			}
		}
		// добавили задачу в список
		task->setTaskParams(params);
		ctpool->addTask(task);
	}
}