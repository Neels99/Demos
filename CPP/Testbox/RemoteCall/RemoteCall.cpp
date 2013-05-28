// RemoteCall.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <string>
#include <iostream>
#include <sstream>
#include "windows.h"

using namespace std;

/*
Сервер псевдо-удалённого вызова 

"Объект 1" отправляет запрос на выполнение удалённой процедуры (в заглушку)
"Объект 2" получает запрос на выполнение удалённой процедуры (из заглушки) и возвращает результат
*/

string stub(string& in);

/*Клиентское приложение: формирует удалённый запрос
префикс "r" в названии функции - символ "удалённого" выполнения
*/
class cClient
{
private:
	/* по-хорошему, тут надо было бы использовать что-то вроде xml-сериализации или бинарной сериализации */	
	string extTrigReq(string funcName, double param) // удалённый вызов тригонометрической функции
	{		
		stringstream ss (stringstream::in | stringstream::out);
		ss << param;

		string send("");
		send.append(funcName);
		send.append("\r\n");
		send.append(ss.str());
		send.append("\r\n");
		return stub(send);
	}

	string extCoordReq(string funcName, int param1, int param2)
	{
		stringstream ss (stringstream::in | stringstream::out);		

		string send("");
		send.append(funcName);
		send.append("\r\n");
		ss << param1;
		send.append(ss.str());
		send.append("\r\n");
		ss.clear();
		ss<<param2;
		send.append(ss.str());
		send.append("\r\n");

		return stub(send);
	}

	// обработчик ошибок
	void exceptor(string& str)
	{
		if(str.compare(0,4,"Fx01") == 0) throw new exception("Неверное название функции");
		if(str.compare(0,4,"Fx02") == 0) throw new exception("Неверные параметры");		
		// ... тут можно сделать много проверок
		if(str.compare(0,4,"FxFF") == 0) throw new exception("Ошибка во время выполнения функции");		
	}

public:
	double rSin(double x)
	{
		string a = extTrigReq("sin",x);		
		exceptor(a);// проверяем: если будет ошибка - ловите исключительную ситуацию
		return atof(a.c_str());
	}

	double rCos(double x)
	{
		string a = extTrigReq("cos",x);		
		exceptor(a);// проверяем: если будет ошибка - ловите исключительную ситуацию
		return atof(a.c_str());
	}

	// функция, которая отправляет заведомо неверный запрос
	void aprioryErrorFunc()
	{
		string a = extCoordReq("efunc",10,20);		
		exceptor(a);// проверяем: если будет ошибка - ловите исключительную ситуацию
	}
};

/*Серверное приложение: обрабатывает удалённый запрос и возвращает ответ*/
class cServer
{
private:
	double Sin(double x)
	{
		return sin(x);
	}
	double Cos(double x)
	{
		return cos(x);
	}
	// принимает пришедшие данные, выполняет их и возвращает запрос
	string AssignFunc(string& data)
	{
		/*
		1. Получаем строку
		2. Определяем и проверям функцию
		3. Определяем соответствие длины строки параметров
		4. Возвращаем ответ
		5. Или генерируем ошибку
		*/
		string answer("");
		try
		{
			string fParam("");			
			stringstream ss;
			fParam = data.substr(0,data.find("\r\n",0)); data.erase(0,data.find("\r\n",0)+2);

			if(fParam.compare(0,3,"sin") == 0)
			{
				if(fParam.length()<3) throw 2;
				fParam = data.substr(0,data.find("\r\n",0));				
				ss<<Sin(atof(fParam.data()));
				answer = ss.str();
			} else
	
			if(fParam.compare(0,3,"cos") == 0)
			{
				if(fParam.length()<3) throw 2;
				fParam = data.substr(0,data.find("\r\n",0));				
				ss<<Cos(atof(fParam.data()));
				answer = ss.str();
			} else

			if(fParam.compare(0,5,"efunc") == 0)
			{
				// тут ничего не обрабатывается - заранее неверная операция				
				throw 100;
			} else
			// неизвестная функция
			throw 1;
		}
		catch(int error)	// наши ошибки
		{
			switch(error)
			{
			case 1: answer = "Fx01";break;// неизвестная функция
			case 2: answer = "Fx02";break;// проблема с параметрами
			
			case 100: answer = "FxFF"; break;	// проблема с выполненеим функции
			}
		}
		catch(exception&) // ошибки операций
		{
			answer = "FxFF";
		}

		return answer;
	}

public:
	string Execute(string& inputData)
	{
		return AssignFunc(inputData);
	}
};


/* заглушка - преобразователь */
string stub(string& in)
{
	cServer server;
	return server.Execute(in);
}


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE,"rus");

	cClient client;
	// выполняем "правильные" функции
	cout<<client.rSin(0.5)<<endl;
	cout<<client.rCos(0.5)<<endl;

	// выполняем "неправильную" функцию
	try
	{
		client.aprioryErrorFunc();
	} catch(exception* e)
	{
		cout<<e->what()<<endl;
	}

	
	cin.get();
	return 0;
}

