// COM-client.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#define IMPORT

#include "stdafx.h"
#include <iostream>

#ifndef IMPORT

#include <stdio.h>
#include <conio.h>
#include "objbase.h"

#include "j:\\Programming\\Demos\\CPP\\Testbox\\COM-server\\COMserver_i.h"
#include "j:\\Programming\\Demos\\CPP\\Testbox\\COM-server\\COMserver_i.c"

#else
#pragma once
#import "..\Debug\COM-server.dll" no_implementation no_namespace  raw_interfaces_only named_guids 
#endif

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale (LC_CTYPE,"rus");
	// �������������� COM
	CoInitialize(NULL);
	IComTestServer* pIComTestServer;	
	Ifigure* pIfigure;

	// ������� ������ � IComTestServer
	HRESULT hr = CoCreateInstance(CLSID_ComTestServer, NULL, CLSCTX_SERVER,	IID_IComTestServer, (void**)&pIComTestServer);
	HRESULT hr2 = CoCreateInstance(CLSID_figure, NULL, CLSCTX_SERVER,	IID_Ifigure, (void**)&pIfigure);
	if(SUCCEEDED(hr))
	{
		// ���� ������ ������...
		long iP1 = 10, iP2 = 20, iResult = 0;
  
		// �������� ����� COM-�������...  
		hr = pIComTestServer->square(iP1, iP2, &iResult);
		// ����������� ������ �� COM-������...  
		pIComTestServer->Release();
		printf("����� ������ 'square(%d, %d)� ������ %d.\r\n", iP1, iP2, iResult);
	}
	if(SUCCEEDED(hr2))
	{
		hr2 = pIfigure->draw(10,10);
		pIfigure->Release();
	}

	std::cout<<"���� ������: "<<hr<<","<<hr2<<std::endl;

	std::cin.get();
	CoUninitialize(); // ���������������� COM

	return 0;
}

