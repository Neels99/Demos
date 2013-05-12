#include "csClient.h"
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;


csClient::csClient(std::string& server, std::string& port)
{
	try
	{
		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
		tcp::resolver::query query(server.c_str(), port.c_str());
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);

		for (;;)
		{
			boost::array<char, 128> buf;
			boost::system::error_code error;
			
			// ����� ���������
			char* str = "[������ �� �������]";
			memcpy(&buf,str,strlen(str)+1);			
			socket.write_some(boost::asio::buffer(buf), error);
			// ������ �����
			memset(&buf,0x0,128);			
			size_t len = socket.read_some(boost::asio::buffer(buf), error);			
			// ������� �����
			if(len>0)std::cout<<"�������� ����������: "<<buf.c_array()<<std::endl;
			// ����������� ������
			if (error == boost::asio::error::eof) break; // ������� �����������
			else if (error) throw boost::system::system_error(error); // �������� ������			
		}
	  }
	  catch (std::exception& e)
	  {
		std::cerr << e.what() << std::endl;
	  }

	  std::cout<<"Client well done"<<std::endl;
}


csClient::~csClient(void)
{
}
