#include "csasServer.h"
#include <boost/array.hpp>
#include "windows.h"	// для того, чтобы немного притормаживать приёмник асинхронного подключения
using namespace std;
using boost::asio::ip::tcp;

csasServer::csasServer(const char* server, const char* port, bool syncmode)
{
	syncMode = syncmode;
	io_service = new boost::asio::io_service();
	// создали акцептор подключений
	acceptor = new tcp::acceptor(*io_service, tcp::endpoint(boost::asio::ip::tcp::v4(), atoi(port)));
	if(syncMode)
	{
		// синхронный сервер				
		startSyncServer();
	}
	else
	{
		// асинхронный сервер
		startAsyncServer();
	}
}

/*=========================== Обработка асинхронной работы сервера =================================*/

void csasServer::write_handler(const boost::system::error_code& error, std::size_t bytes_transferred, tcp::socket* socket)
{
	cout<<"Ответили клиенту"<<endl;
	// разрушили сокеты
	socket->close();
	delete socket;
}

void csasServer::read_handler(const boost::system::error_code& error, std::size_t bytes_transferred, char* msg, tcp::socket* socket)
{
	cout<<"Принято: "<<(error.value()==0?"":error.message())<<" "<<msg<<" Принято байт: "<<bytes_transferred<<endl;
	delete msg;
	// отсюда запускаем передачу данных
	boost::asio::async_write(*socket,boost::asio::buffer("Наш ответ Чемберлену"),boost::bind(&csasServer::write_handler, this,boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred,socket)); 
}
 
// условия завершения приёма данных
std::size_t csasServer::completion_condition(const boost::system::error_code& error, std::size_t bytes_transferred, char* buf)
{
	return bytes_transferred<128?8:0;
}

void csasServer::acc(tcp::socket* socket, const boost::system::error_code& error)
{
	const int dlen = 256;
	char* buf = new char[dlen];
	//boost::array<char, dlen> buf;
	boost::asio::async_read(*socket,boost::asio::buffer(buf,dlen),boost::bind(&csasServer::completion_condition,this,boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred,buf), boost::bind(&csasServer::read_handler,this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, buf, socket)); 				
	//cout<<"Принято "<<buf.c_array()<<endl;
}

/* =============================== Конец ================================= */

void csasServer::startSyncServer()
{
	for (;;)
    {
		boost::system::error_code error;
		string msg("");		
		// ожидаем подключение	  
		tcp::socket socket(*io_service);
		acceptor->accept(socket,error);		
		// получили данные
		const int dlen = 256;
		boost::array<char, dlen> buf;		
		size_t len = socket.read_some(boost::asio::buffer(buf),error);
		// обработали данные
		msg = processData(buf.c_array());
		// вернули результат
		boost::asio::write(socket, boost::asio::buffer(msg), error);
		// отключились
		socket.close();     
    }
}

void csasServer::startAsyncServer()
{
	// хотел сделать самоунчтожение сокетов, но при такой записи компилятор отчего-то валился: fatal error C1001: Внутренняя ошибка в файле компилятора.(файл компилятора "msc1.cpp", строка 1420)
	//std::auto_ptr<tcp::socket> socket(new tcp::socket(*io_service));
	// инициализировали сокет - будет уничтожен в обработчике		
	try
	{
		for (;;)
		{
		tcp::socket* socket = new tcp::socket(*io_service);
		// подключаем асинхронный перехват		
		// после подключения клиента - считываются информация, которую он прислал и отправляется ему встречная информация		
		//acceptor->async_accept((*socket),boost::bind(&csasServer::asyncCompleteOperationHandle,this,1,socket, (char*)"", boost::asio::placeholders::error));				

		acceptor->async_accept((*socket),boost::bind(&csasServer::acc,this,socket, boost::asio::placeholders::error));				

		// запускаем цикл прослушки
		io_service->run();
		}
	} catch(std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	cout<<"Exit"<<endl;
}

string csasServer::processData(char* in)
{
	cout<<"Клиент прислал: "<<in<<endl;	
	return syncMode?"Sync server online":"Async server online";
}

csasServer::~csasServer(void)
{
	if(acceptor)delete acceptor;
	if(io_service)delete io_service;
}


