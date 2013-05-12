#pragma once
#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;
/*

Сервер подключений

*/

class csasServer
{
private:	
	csasServer(void) : syncMode(false), acceptor(0), io_service(0)	{};		// конструктор по-умолчанию. Недоступен.
private:
	// функции для синхронного сервера
	void startSyncServer();													// запустить сервер в синхронном режиме				
	std::string processData(char* in);										// обработать данные

private:
	// функции для асинхронного режима (асинхронный режим для небольшого количества подключений)
	void startAsyncServer();																									// запустить сервер в асинхронном режиме	
	void acc(tcp::socket* socket, const boost::system::error_code& error);														// обработчик установления подключения
	void read_handler(const boost::system::error_code& error, std::size_t bytes_transferred, char* msg, tcp::socket* socket);	// обработчик завершения чтения данных от клиента
	void write_handler(const boost::system::error_code& error, std::size_t bytes_transferred, tcp::socket* socket);				// обработчик завершения передачи данных клиенту
	std::size_t completion_condition(const boost::system::error_code& error, std::size_t bytes_transferred, char* buf);			// функция-сравнение, определяющая, закончился ли приём данных
	
public:	
	csasServer(const char* server, const char* service, bool syncmode=true);		// создать сервер, по-умолчанию в синхронном режиме	
	virtual ~csasServer(void);														// деструктор сервера	

private:
	bool syncMode;
	boost::asio::ip::tcp::acceptor* acceptor;
	boost::asio::io_service* io_service;
};

