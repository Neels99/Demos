// COM-client.cpp: определяет точку входа для консольного приложения.
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
	// Инициализируем COM
	CoInitialize(NULL);
	IComTestServer* pIComTestServer;	
	Ifigure* pIfigure;

	// Создаем объект – IComTestServer
	HRESULT hr = CoCreateInstance(CLSID_ComTestServer, NULL, CLSCTX_SERVER,	IID_IComTestServer, (void**)&pIComTestServer);
	HRESULT hr2 = CoCreateInstance(CLSID_figure, NULL, CLSCTX_SERVER,	IID_Ifigure, (void**)&pIfigure);
	if(SUCCEEDED(hr))
	{
		// Если объект создан...
		long iP1 = 10, iP2 = 20, iResult = 0;
  
		// Вызываем метод COM-объекта...  
		hr = pIComTestServer->square(iP1, iP2, &iResult);
		// Освобождаем ссылку на COM-объект...  
		pIComTestServer->Release();
		printf("Вызов метода 'square(%d, %d)’ вернул %d.\r\n", iP1, iP2, iResult);
	}
	if(SUCCEEDED(hr2))
	{
		hr2 = pIfigure->draw(10,10);
		pIfigure->Release();
	}

	std::cout<<"Коды ошибки: "<<hr<<","<<hr2<<std::endl;

	std::cin.get();
	CoUninitialize(); // Деинициализируем COM

	return 0;
}

