#include "StdAfx.h"
#include "cTask.h"

// мьютекс блокировки вывода
boost::mutex io_mut;

void cTask::Suspend()
{
	if(!params && !params->getThreadHandler())
	{
		SuspendThread(params->getThreadHandler());
	}
}

cTask::~cTask(void)
{
	delete params;
}

void cTask::mainExecuteFunction()
{
	// выполнение основной задачи	
	params->endTask = false;
	ExecuteFunction();						// рабочая функция
	params->CallBack();						// отчитались о проделанной работе	
	params->endTask = true;
}

// параметры функций - определение
void cTaskParams1::CallBack()
{
	// критическая секция на вывод
	boost::mutex::scoped_lock lock(io_mut);
	cTaskParams::CallBack();
	cout<<returnVal<<endl;
}

void cTaskParams2::CallBack()
{
	// критическая секция на вывод
	boost::mutex::scoped_lock lock(io_mut);
	cTaskParams::CallBack();
	cout<<returnVal.c_str()<<endl;
}


// функция работы с двумя простыми числами
void cTask1::ExecuteFunction()
{
	((cTaskParams1*)params)->returnVal = (((cTaskParams1*)params)->x + ((cTaskParams1*)params)->y)*(((cTaskParams1*)params)->x * ((cTaskParams1*)params)->y);
}

void cTask2::ExecuteFunction()
{
	((cTaskParams2*)params)->returnVal = ((cTaskParams2*)params)->str1 + ((cTaskParams2*)params)->str2;
}