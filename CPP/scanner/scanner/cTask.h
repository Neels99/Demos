#pragma once
#include "windows.h"
#include <iostream>
#include <string>
#include "boost/thread.hpp"

using namespace std;

// функция обратной связи
typedef void(*callback)();

// параметры произвольной задачи потока
class cTaskParams
{
protected:
	HANDLE threadHandle;	
	callback cback;
public:
	cTaskParams():threadHandle(0x0), goExit(false), endTask(false), cback(0x0){};
	void setThreadHandle(HANDLE newHandle) {
		threadHandle = newHandle;
	}
	void setCallBackFunction(callback cb){cback = cb;}
	const HANDLE getThreadHandler() {return threadHandle;}
	virtual ~cTaskParams(){};
public:
	// сигналы для работы с потоком	
	bool goExit;		 // выход их потока
	bool endTask;		 // индикатор того, что задание выполнено
public:
	// функция обратной связи
	virtual void CallBack() {if(!cback)cback();}
};

// базовая задача для потока
class cTask
{
	// главная функция исполнения
	void mainExecuteFunction();
protected:	
	cTask(void):params(NULL){}; // конструктор по-умолчанию должен быть недоступен
	cTaskParams* params;
	void Suspend();// заморозить поток задачи	
	virtual void ExecuteFunction() = 0;// некоторая функция для исполнения
public:	
	cTask(cTaskParams* p):params(p){};
	virtual ~cTask(void);
	// доступ к параметрам задачи
	cTaskParams* getTaskParams() {return params;}	
	// выполнить задачу
	void Execute() {mainExecuteFunction();}
	// установить параметры
	void setTaskParams(cTaskParams* newparams) {params = newparams;}
};

/*=======================================ФАКТИЧЕСКИЕ ЗАДАЧИ===========================================*/

/* ========== ПАРАМЕТРЫ ========== */
// параметры для задачи 1
class cTaskParams1 : public cTaskParams
{	
public:
	int x,y,returnVal;
	cTaskParams1() : x(0),y(0),returnVal(0) {}	
	void CallBack();
};

// параметры задачи 2
class cTaskParams2 : public cTaskParams
{
public:
	std::string str1,str2,returnVal;
	cTaskParams2() : str1(""),str2(""),returnVal(""){};
	void CallBack();
};

/* ========== РЕШЕНИЯ ========== */

// расчётная задача: возвращает сумму (двух чисел) x (произведение двух чисел)
class cTask1 : public cTask
{
	void ExecuteFunction();
};

// расчётная задача: возвращает сложение двух строк
class cTask2 : public cTask
{
	void ExecuteFunction();
};