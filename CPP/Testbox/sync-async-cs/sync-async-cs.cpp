// sync-async-cs.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>

#include "csasServer.h"
#include "csClient.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE,"rus");
	/*
		конфигурируем приложение. параметры
		1. клиент/сервер = с/s
		2. ip = 127.0.0.1
		3. порт = 555
		4. синхронный/асинхронный s/a
	*/

	// инициализация параметров
	if(argc < 5) exit(0x010);
	bool serverMode;
	bool syncMode;

	bool testmode = false;

	string ip_("");
	string port_("");
	try
	{
		serverMode = argv[1][0] == 'c' ? false : true;
		syncMode =  argv[4][0] == 's' ? true : false;
		ip_ = argv[2];
		port_ = argv[3];
		// режим отладки
		if(argc>5) testmode = argv[5][0]=='t'?true:false;
	}
	catch(...)
	{
		exit(0x011);
	}
	
	if(serverMode) // запустили сервер
	{
		cout<<"Сервер запущен: "<<(syncMode?"синхронный":"асинхронный")<<" режим ("<<ip_.c_str()<<":"<<port_.c_str()<<")"<<endl;
		csasServer server(ip_.c_str(),port_.c_str(),syncMode);
	}else // запустили клиента
	{
		cout<<"Клиент запущен"<<endl;
		csClient client(ip_,port_);
	}


	if(!testmode)cin.get();
	return 0;
}

