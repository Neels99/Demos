#include "StdAfx.h"
#include "cThreadPool.h"

#define ThreadsPerKernel 10
#define WaitInterval 100

using namespace std;

// ������� ��� ������������� ������
boost::mutex thMutex;
boost::mutex restartMutex;


/* ============================== ������� ������� ==============================*/

// ������� ������ ������ �������� ������
void ThreadFunction(ThreadInfo* ti)
{	
	while(1)
	{
		cTask* task;
		{
//			boost::mutex::scoped_lock lock(restartMutex);
			task = ti->task;// �� ������ ������ ������
		}
		// ��������� ������� ����������
		if(!task || !(task->getTaskParams())) throw "������������� ��������� ������. ����� �� ���������������";
		// ��������� ������
		task->Execute();
		// ����� ���������� ������
		boost::this_thread::interruption_point(); // ��� �������� ���������� �������
		// ���������� �����		
		SuspendThread(task->getTaskParams()->getThreadHandler());
	}
}

// ������� ������ ���������� ������
void ServiceThread(cThreadPool* cpool)
{
	while(1)
	{
		// ���� ���� ������ - ����� ��
		while(cpool->haveTasks())cpool->configThread();
		// �������
		Sleep(WaitInterval);
		// ����� ��������������� ���������� ������
		boost::this_thread::interruption_point();
	}
}

/* ============================== ���������� ������ ==============================*/

cThreadPool::cThreadPool(void)
{
	serviceThread = new boost::thread(boost::bind(ServiceThread,this));
}

cThreadPool::~cThreadPool(void)
{
	serviceThread->interrupt();
	delete serviceThread;
	// ���� �������� ���������� ������ � ������ - ������������
	while(haveTasks()) 
	{
		delete tasks.front();
		tasks.pop();
	}
}

void cThreadPool::configThread()
{	
	// �������� �������
	if(tasks.size() > 0)
	{
		// �������� ����� �� ������, ���� ���� �����������
		// ���� (��� ������������) ��� (��� ������), �� ���� ��������� ����� � ���� - �������� ��� ����
		// ���� ��� ������������ � ��� ���������� ����� � ���� - ��������� 100��
		bool ok = false;
		cTask* newTask;		
		{	// ���������� ������� ��������� � ��������� �������� ����������			
			boost::mutex::scoped_lock lock(thMutex);
			newTask = tasks.front();
			tasks.pop();// ������ ������ �� ������
		}
		while(!ok)
		{
			ok = false;
			// ���������������� �������������
			if(threads.size()>0)
			{
				for(vector<ThreadInfo*>::const_iterator it=threads.begin(); it<threads.end(); it++)
					if((*it)->thread && (*it)->task->getTaskParams()->endTask) 
					{					
						// ��������� ������� �� ��������������� ��������� ������
						Sleep((UINT)(WaitInterval/10));
						// ������������� ����� ������ ������
						cTask* oldtask = (*it)->task;
						// ���������� ����� ��������� ������
						(*it)->task = newTask;				
						// ��������������� ���������
						newTask->getTaskParams()->setThreadHandle((*it)->thread->native_handle());
						// ��������� ������ ������ ������		
						delete oldtask;
						// ����������� �����
						ResumeThread((*it)->thread->native_handle());
						ok = true;
						break;
					}
			}

			// ���������� ������ 
			if(!ok && threads.size()<=boost::thread::hardware_concurrency() * ThreadsPerKernel)
			{			
				// ������� ������� ���������� � ������
				ThreadInfo* ti = new ThreadInfo();
				ti->task = newTask;	// ���������� ������			

				// ������� �����
				boost::thread* newthread = new boost::thread(boost::bind(ThreadFunction,ti));				
		
				// ��������� ������������ ���������� � ������
				ti->task->getTaskParams()->setThreadHandle(newthread->native_handle());// ���������� ��������� ��� ��������� "�����" ������
				ti->thread = newthread; // ���������� �����
				// �������� ���������� � ���
				threads.push_back(ti);
				ok = true;
			}
			else
			{
				Sleep(10);
			}

			// ��������
			if(!ok) Sleep(WaitInterval);
		};
	}
}

void cThreadPool::addTask(cTask* task)
{
	boost::mutex::scoped_lock lock(thMutex);
	tasks.push(task);
}