#include "StdAfx.h"
#include "cThreadPool.h"

#define ThreadsPerKernel 10
#define WaitInterval 100

using namespace std;

// мьютекс дл€ синхронизации данных
boost::mutex thMutex;
boost::mutex restartMutex;


/* ============================== ‘ункции потоков ==============================*/

// функци€ работы любого рабочего потока
void ThreadFunction(ThreadInfo* ti)
{	
	while(1)
	{
		cTask* task;
		{
//			boost::mutex::scoped_lock lock(restartMutex);
			task = ti->task;// на случай замены задачи
		}
		// проверили наличие параметров
		if(!task || !(task->getTaskParams())) throw "ЌеопределЄнные параметры потока. ѕоток не сконфигурирован";
		// выполнили задачу
		task->Execute();
		// точка прерывани€ потока
		boost::this_thread::interruption_point(); // дл€ силового прерывани€ потоков
		// заморозили поток		
		SuspendThread(task->getTaskParams()->getThreadHandler());
	}
}

// функци€ работы служебного потока
void ServiceThread(cThreadPool* cpool)
{
	while(1)
	{
		// пока есть задачи - задаЄм их
		while(cpool->haveTasks())cpool->configThread();
		// ожидаем
		Sleep(WaitInterval);
		// точка принудительного завершени€ потока
		boost::this_thread::interruption_point();
	}
}

/* ============================== –еализаци€ класса ==============================*/

cThreadPool::cThreadPool(void)
{
	serviceThread = new boost::thread(boost::bind(ServiceThread,this));
}

cThreadPool::~cThreadPool(void)
{
	serviceThread->interrupt();
	delete serviceThread;
	// если остались нерешЄнные задачи в списке - уничтожаютс€
	while(haveTasks()) 
	{
		delete tasks.front();
		tasks.pop();
	}
}

void cThreadPool::configThread()
{	
	// проверка очереди
	if(tasks.size() > 0)
	{
		// получить поток из списка, если есть завершЄнный
		// если (нет завершЄнного) или (пул пустой), но есть свободное место в пуле - добавить ещЄ один
		// если нет завершЄнного и нет свободного места в пуле - подождать 100мс
		bool ok = false;
		cTask* newTask;		
		{	// установили область видимости и защищЄнно изменили содержимое			
			boost::mutex::scoped_lock lock(thMutex);
			newTask = tasks.front();
			tasks.pop();// убрали задачу из списка
		}
		while(!ok)
		{
			ok = false;
			// переконфигураци€ существующего
			if(threads.size()>0)
			{
				for(vector<ThreadInfo*>::const_iterator it=threads.begin(); it<threads.end(); it++)
					if((*it)->thread && (*it)->task->getTaskParams()->endTask) 
					{					
						// подождали немного до гарантированной остановки потока
						Sleep((UINT)(WaitInterval/10));
						// зафиксировали новую задачу потока
						cTask* oldtask = (*it)->task;
						// установили новые параметры задачи
						(*it)->task = newTask;				
						// акутализировали параметры
						newTask->getTaskParams()->setThreadHandle((*it)->thread->native_handle());
						// разрушили старую задачу потока		
						delete oldtask;
						// возобновили поток
						ResumeThread((*it)->thread->native_handle());
						ok = true;
						break;
					}
			}

			// добавление нового 
			if(!ok && threads.size()<=boost::thread::hardware_concurrency() * ThreadsPerKernel)
			{			
				// создали учЄтную информацию о потоке
				ThreadInfo* ti = new ThreadInfo();
				ti->task = newTask;	// установили задачу			

				// создали поток
				boost::thread* newthread = new boost::thread(boost::bind(ThreadFunction,ti));				
		
				// закончили конфигурацию информации о потоке
				ti->task->getTaskParams()->setThreadHandle(newthread->native_handle());// установили параметры дл€ установки "паузы" потока
				ti->thread = newthread; // установили поток
				// добавили информацию в пул
				threads.push_back(ti);
				ok = true;
			}
			else
			{
				Sleep(10);
			}

			// ожидание
			if(!ok) Sleep(WaitInterval);
		};
	}
}

void cThreadPool::addTask(cTask* task)
{
	boost::mutex::scoped_lock lock(thMutex);
	tasks.push(task);
}