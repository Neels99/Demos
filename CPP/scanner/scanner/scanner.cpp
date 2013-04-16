// scanner.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include "cTaskGenerator.h"

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale (LC_CTYPE,"rus");
	cout<<"Старт приложения"<<endl;
	cTaskGenerator ctg;
	ctg.GeterateTask(1000); 
	cin.get();	
	ctg.GeterateTask(4000);
	cin.get();	
	return 0;
}

