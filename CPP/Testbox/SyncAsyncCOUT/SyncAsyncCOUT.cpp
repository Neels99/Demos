// SyncAsyncCOUT.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <iostream>

using namespace std;

int cnt = 10;

void print1(const char* tparam)
{
	cout<<tparam<<"->"<<(--cnt)<<endl;
}


void print2()
{
	cout<<"Sync print"<<endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale (LC_CTYPE,"rus");

	// инициализация io
	boost::asio::io_service io;
	// инициализируем "синхронизатор" доступа к разделяемому ресурсу. В нашем случае - вывод в консоль
	boost::asio::strand st(io);
	// таймеры
	boost::asio::deadline_timer t1(io, boost::posix_time::seconds(1));
	boost::asio::deadline_timer t2(io, boost::posix_time::seconds(1));
	// устанавливаем функции у вызова
	// Обратите внимание: параметры вызываемой функции связаны через boost::bind, а st.wrap обеспечивает синхронизацию данных
	t1.async_wait( st.wrap( boost::bind(&print1,"timer1") ) );
	t2.async_wait( st.wrap( boost::bind(&print1,"timer2") ) );
	/*
		таймер можно передать в виде параметров в функцию и оттуда запускать рекурсивно, но я не буду это делать :-)
	*/

	// теперь готовимся к выводу
	cout<<"Start async output"<<endl;
	// старт вывода; без этой функции таймеры не сработают
	io.run();


	// демонстрация синхронного таймера: аналог стандартной виндовой функции Sleep(), только сложней
	boost::asio::deadline_timer t3(io, boost::posix_time::seconds(3));
	boost::system::error_code ec; //необязательный параметр, добавлен ради разнообразия: в случае успеха сообщит об это через сообщение
	t3.wait(ec); 
	cout<<ec.message().c_str()<<endl; 
	print2();

	cin.get();
	return 0;
}

