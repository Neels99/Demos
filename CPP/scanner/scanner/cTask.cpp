#include "StdAfx.h"
#include "cTask.h"

// ������� ���������� ������
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
	// ���������� �������� ������	
	params->endTask = false;
	ExecuteFunction();						// ������� �������
	params->CallBack();						// ���������� � ����������� ������	
	params->endTask = true;
}

// ��������� ������� - �����������
void cTaskParams1::CallBack()
{
	// ����������� ������ �� �����
	boost::mutex::scoped_lock lock(io_mut);
	cTaskParams::CallBack();
	cout<<returnVal<<endl;
}

void cTaskParams2::CallBack()
{
	// ����������� ������ �� �����
	boost::mutex::scoped_lock lock(io_mut);
	cTaskParams::CallBack();
	cout<<returnVal.c_str()<<endl;
}


// ������� ������ � ����� �������� �������
void cTask1::ExecuteFunction()
{
	((cTaskParams1*)params)->returnVal = (((cTaskParams1*)params)->x + ((cTaskParams1*)params)->y)*(((cTaskParams1*)params)->x * ((cTaskParams1*)params)->y);
}

void cTask2::ExecuteFunction()
{
	((cTaskParams2*)params)->returnVal = ((cTaskParams2*)params)->str1 + ((cTaskParams2*)params)->str2;
}