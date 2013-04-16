#pragma once
#include "windows.h"
#include <iostream>
#include <string>
#include "boost/thread.hpp"

using namespace std;

// ������� �������� �����
typedef void(*callback)();

// ��������� ������������ ������ ������
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
	// ������� ��� ������ � �������	
	bool goExit;		 // ����� �� ������
	bool endTask;		 // ��������� ����, ��� ������� ���������
public:
	// ������� �������� �����
	virtual void CallBack() {if(!cback)cback();}
};

// ������� ������ ��� ������
class cTask
{
	// ������� ������� ����������
	void mainExecuteFunction();
protected:	
	cTask(void):params(NULL){}; // ����������� ��-��������� ������ ���� ����������
	cTaskParams* params;
	void Suspend();// ���������� ����� ������	
	virtual void ExecuteFunction() = 0;// ��������� ������� ��� ����������
public:	
	cTask(cTaskParams* p):params(p){};
	virtual ~cTask(void);
	// ������ � ���������� ������
	cTaskParams* getTaskParams() {return params;}	
	// ��������� ������
	void Execute() {mainExecuteFunction();}
	// ���������� ���������
	void setTaskParams(cTaskParams* newparams) {params = newparams;}
};

/*=======================================����������� ������===========================================*/

/* ========== ��������� ========== */
// ��������� ��� ������ 1
class cTaskParams1 : public cTaskParams
{	
public:
	int x,y,returnVal;
	cTaskParams1() : x(0),y(0),returnVal(0) {}	
	void CallBack();
};

// ��������� ������ 2
class cTaskParams2 : public cTaskParams
{
public:
	std::string str1,str2,returnVal;
	cTaskParams2() : str1(""),str2(""),returnVal(""){};
	void CallBack();
};

/* ========== ������� ========== */

// ��������� ������: ���������� ����� (���� �����) x (������������ ���� �����)
class cTask1 : public cTask
{
	void ExecuteFunction();
};

// ��������� ������: ���������� �������� ���� �����
class cTask2 : public cTask
{
	void ExecuteFunction();
};