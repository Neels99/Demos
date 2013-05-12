#pragma once
#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;
/*

������ �����������

*/

class csasServer
{
private:	
	csasServer(void) : syncMode(false), acceptor(0), io_service(0)	{};		// ����������� ��-���������. ����������.
private:
	// ������� ��� ����������� �������
	void startSyncServer();													// ��������� ������ � ���������� ������				
	std::string processData(char* in);										// ���������� ������

private:
	// ������� ��� ������������ ������ (����������� ����� ��� ���������� ���������� �����������)
	void startAsyncServer();																									// ��������� ������ � ����������� ������	
	void acc(tcp::socket* socket, const boost::system::error_code& error);														// ���������� ������������ �����������
	void read_handler(const boost::system::error_code& error, std::size_t bytes_transferred, char* msg, tcp::socket* socket);	// ���������� ���������� ������ ������ �� �������
	void write_handler(const boost::system::error_code& error, std::size_t bytes_transferred, tcp::socket* socket);				// ���������� ���������� �������� ������ �������
	std::size_t completion_condition(const boost::system::error_code& error, std::size_t bytes_transferred, char* buf);			// �������-���������, ������������, ���������� �� ���� ������
	
public:	
	csasServer(const char* server, const char* service, bool syncmode=true);		// ������� ������, ��-��������� � ���������� ������	
	virtual ~csasServer(void);														// ���������� �������	

private:
	bool syncMode;
	boost::asio::ip::tcp::acceptor* acceptor;
	boost::asio::io_service* io_service;
};

