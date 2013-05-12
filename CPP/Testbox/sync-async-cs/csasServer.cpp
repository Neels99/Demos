#include "csasServer.h"
#include <boost/array.hpp>
#include "windows.h"	// ��� ����, ����� ������� �������������� ������� ������������ �����������
using namespace std;
using boost::asio::ip::tcp;

csasServer::csasServer(const char* server, const char* port, bool syncmode)
{
	syncMode = syncmode;
	io_service = new boost::asio::io_service();
	// ������� �������� �����������
	acceptor = new tcp::acceptor(*io_service, tcp::endpoint(boost::asio::ip::tcp::v4(), atoi(port)));
	if(syncMode)
	{
		// ���������� ������				
		startSyncServer();
	}
	else
	{
		// ����������� ������
		startAsyncServer();
	}
}

/*=========================== ��������� ����������� ������ ������� =================================*/

void csasServer::write_handler(const boost::system::error_code& error, std::size_t bytes_transferred, tcp::socket* socket)
{
	cout<<"�������� �������"<<endl;
	// ��������� ������
	socket->close();
	delete socket;
}

void csasServer::read_handler(const boost::system::error_code& error, std::size_t bytes_transferred, char* msg, tcp::socket* socket)
{
	cout<<"�������: "<<(error.value()==0?"":error.message())<<" "<<msg<<" ������� ����: "<<bytes_transferred<<endl;
	delete msg;
	// ������ ��������� �������� ������
	boost::asio::async_write(*socket,boost::asio::buffer("��� ����� ����������"),boost::bind(&csasServer::write_handler, this,boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred,socket)); 
}
 
// ������� ���������� ����� ������
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
	//cout<<"������� "<<buf.c_array()<<endl;
}

/* =============================== ����� ================================= */

void csasServer::startSyncServer()
{
	for (;;)
    {
		boost::system::error_code error;
		string msg("");		
		// ������� �����������	  
		tcp::socket socket(*io_service);
		acceptor->accept(socket,error);		
		// �������� ������
		const int dlen = 256;
		boost::array<char, dlen> buf;		
		size_t len = socket.read_some(boost::asio::buffer(buf),error);
		// ���������� ������
		msg = processData(buf.c_array());
		// ������� ���������
		boost::asio::write(socket, boost::asio::buffer(msg), error);
		// �����������
		socket.close();     
    }
}

void csasServer::startAsyncServer()
{
	// ����� ������� �������������� �������, �� ��� ����� ������ ���������� ������-�� �������: fatal error C1001: ���������� ������ � ����� �����������.(���� ����������� "msc1.cpp", ������ 1420)
	//std::auto_ptr<tcp::socket> socket(new tcp::socket(*io_service));
	// ���������������� ����� - ����� ��������� � �����������		
	try
	{
		for (;;)
		{
		tcp::socket* socket = new tcp::socket(*io_service);
		// ���������� ����������� ��������		
		// ����� ����������� ������� - ����������� ����������, ������� �� ������� � ������������ ��� ��������� ����������		
		//acceptor->async_accept((*socket),boost::bind(&csasServer::asyncCompleteOperationHandle,this,1,socket, (char*)"", boost::asio::placeholders::error));				

		acceptor->async_accept((*socket),boost::bind(&csasServer::acc,this,socket, boost::asio::placeholders::error));				

		// ��������� ���� ���������
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
	cout<<"������ �������: "<<in<<endl;	
	return syncMode?"Sync server online":"Async server online";
}

csasServer::~csasServer(void)
{
	if(acceptor)delete acceptor;
	if(io_service)delete io_service;
}


