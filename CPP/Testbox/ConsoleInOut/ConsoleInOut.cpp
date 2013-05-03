// ConsoleInOut.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

/*
-l <login, string> -p <password, string> -to <timeout, int> -fm <mappedfile, string>
*/

/*
- неопределённые параметры игнорируются
- неизвестные параметры игнорируются
- параметры идут только парами
- параметры начинаются со знака "-"
- пропуск необязательных параметров задаёт значения по-умолчанию
- пропуск обязательных параметров возвращает ошибку - выводит в консоль
- если после ключа параметра идёт другой ключ параметра - первый аннулируется
*/

/*
- параметр проверяется на типизированность (для int)
- 
*/

// данные конфигурации
string login("");
string password("");
int timeout(100);
string mapfile("");


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale (LC_CTYPE,"rus");

	bool isKey = false;
	string keyName("");
	string keyValue("");

	// сканирование параметров
	for(int cnt = 1; cnt<argc;cnt++)
	{		
		isKey = strlen(argv[cnt])>0 && argv[cnt][0] == '-' ? true : false;		
		if(isKey) 
		{
			keyName.clear();// на случай, если ключ продублировался
			keyName.append(argv[cnt],1,strlen(argv[cnt])-1);
		} else {keyValue.append(argv[cnt]);}
		if(keyName.length()>0 && keyValue.length()>0)
		{

			if(strcmp(keyName.c_str(),"l") == 0)		{login		= keyValue;}
			if(strcmp(keyName.c_str(),"p") == 0)		{password	= keyValue;}
			if(strcmp(keyName.c_str(),"fm") == 0)		{mapfile	= keyValue;}
			if(strcmp(keyName.c_str(),"to") == 0)		{timeout	= atoi(keyValue.c_str());}

			//cout<<"Параметр="<<keyName.c_str()<<", значение="<<keyValue.c_str()<<endl;
			keyName.clear();
			keyValue.clear();
		}
						
	}

	// проверка на заполненность всеми ключевыми данными
	if(login.length()<1 || password.length()<1 || mapfile.length()<1)
	{
		cout<<"Не хватает параметров для корректной обработки запроса"<<endl;
	} else
	{
		cout<<"Обработка запроса: учётная запись "<<login.c_str()<<", пароль "<<password.c_str()<<". Файл, проецируемый в память: "<<mapfile.c_str()<<". Установленное время задержки "<<timeout<<"."<<endl;
	}

	cin.get();
	return 0;
}

